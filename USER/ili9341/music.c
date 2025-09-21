  #include "music.h"
#include "string.h"
#include "stdio.h"
#include "i2s.h"
#include "tim.h"
#include "stdlib.h"

// ---------------- 全局变量 ----------------
static __ALIGN_BEGIN uint16_t AudioBuf[2 * AUDIO_HALF_SAMPLES] __ALIGN_END;
static volatile uint32_t audio_size_bytes  = 0;
static volatile uint32_t audio_offset      = 0;
static volatile uint8_t playing            = 0;
static float volume = 0.5f;

static FIL wav_file;
static uint32_t wav_data_start = 0;
static uint16_t wav_num_channels = 0;
static I2S_HandleTypeDef *i2sHandle = NULL;
static FATFS fs;
static uint8_t fs_mounted = 0;


// 标志位，标记哪半缓冲需要填充
volatile uint8_t buf0_need_fill = 0;
volatile uint8_t buf1_need_fill = 0;

// ---------------- SD 卡挂载 ----------------
static int WAV_InitSD(void)
{
    if(!fs_mounted)
    {
        if(f_mount(&fs, "", 1) != FR_OK)
        {
            printf("SD mount failed\n");
            return -1;
        }
        fs_mounted = 1;
        printf("SD mounted successfully\n");
    }
    return 0;
}

// ---------------- 内部函数：填充半缓冲 ----------------
static void FillHalfBufferLoop(uint8_t halfIndex)
{
    uint8_t *dst = (uint8_t*)&AudioBuf[halfIndex * AUDIO_HALF_SAMPLES];
    uint32_t bytesToFill = AUDIO_HALF_SAMPLES * SAMPLE_BYTES;
    uint32_t filled = 0;
    UINT br;

    while(filled < bytesToFill)
    {
        uint32_t remain = audio_size_bytes - audio_offset;
        uint32_t chunk = (remain >= (bytesToFill - filled)) ? (bytesToFill - filled) : remain;
        if(wav_num_channels == 2) chunk &= ~3; else chunk &= ~1;
//			printf("audio_offset:%d\r\n",audio_offset);
        if(chunk > 0)
        {
            if(f_read(&wav_file, dst + filled, chunk, &br) != FR_OK || br == 0)
            {
                memset(dst + filled, 0, bytesToFill - filled);
                break;
            }

            // 音量缩放
            int16_t *samples = (int16_t*)(dst + filled);
            for(uint32_t i = 0; i < br/2; i++)
            {
                int32_t s = (int32_t)(samples[i] * volume);
                if(s > 32767) s = 32767;
                if(s < -32768) s = -32768;
                samples[i] = (int16_t)s;
            }

            audio_offset += br;
            filled += br;
        }

        // 如果文件末尾不足半缓冲，补头部继续填充
        if(filled < bytesToFill && audio_offset >= audio_size_bytes)
        {
            f_lseek(&wav_file, wav_data_start);
            audio_offset = 0;
        }
    }
}
// ---------------- WAV 文件打开 ----------------
static int WAV_OpenFile(const char *filename)
{
    if(f_open(&wav_file, filename, FA_READ) != FR_OK)
    {
        printf("f_open failed: %s\n", filename);
        return -1;
    }

    UINT br;
    uint8_t buf[4];

    // RIFF header
    if(f_read(&wav_file, buf, 4, &br)!=FR_OK || br!=4) return -1;
    if(memcmp(buf,"RIFF",4)!=0) { printf("Not RIFF\n"); return -1; }
    f_read(&wav_file, buf,4,&br); // ChunkSize
    f_read(&wav_file, buf,4,&br); // WAVE
    if(memcmp(buf,"WAVE",4)!=0) { printf("Not WAVE\n"); return -1; }

    // 解析 chunk
    while(f_tell(&wav_file) < f_size(&wav_file))
    {
        char chunkID[5] = {0};
        if(f_read(&wav_file, buf,4,&br)!=FR_OK) return -1;
        memcpy(chunkID, buf,4);
        if(f_read(&wav_file, buf,4,&br)!=FR_OK) return -1;
        uint32_t chunkSize = buf[0]|(buf[1]<<8)|(buf[2]<<16)|(buf[3]<<24);

        if(memcmp(chunkID,"fmt ",4)==0)
        {
            uint8_t fmt[16];
            if(f_read(&wav_file, fmt,16,&br)!=FR_OK) return -1;
            uint16_t audioFormat = fmt[0]|(fmt[1]<<8);
            wav_num_channels = fmt[2]|(fmt[3]<<8);
            uint16_t bitsPerSample = fmt[14]|(fmt[15]<<8);

            if(audioFormat!=1 || bitsPerSample!=16 || wav_num_channels>2) {
                printf("Unsupported WAV\n");
                return -1;
            }
            f_lseek(&wav_file, f_tell(&wav_file) + (chunkSize-16));
        }
        else if(memcmp(chunkID,"data",4)==0)
        {
            wav_data_start = f_tell(&wav_file);
            audio_size_bytes = chunkSize;
            f_lseek(&wav_file, wav_data_start);
            printf("WAV: %dch 16bit, %lu bytes, dataPos=%lu\n",
                   wav_num_channels, audio_size_bytes, wav_data_start);
            return 0;
        }
        else
        {
            f_lseek(&wav_file, f_tell(&wav_file) + chunkSize);
        }
    }

    printf("No data chunk\n");
    return -1;
}

// ---------------- 播放接口 ----------------
int WAV_PlayFile(const char *filename, I2S_HandleTypeDef *hi2s)
{
    if(WAV_InitSD() != 0) return -1;
    if(WAV_OpenFile(filename) != 0) return -1;

    i2sHandle = hi2s;
    audio_offset = 0;
    playing = 1;

    // 预填充双缓冲
    FillHalfBufferLoop(0);
    FillHalfBufferLoop(1);
     printf("Start DMA with %d samples\n", AUDIO_HALF_SAMPLES);
    // 启动 I2S DMA
    if(HAL_I2S_Transmit_DMA(i2sHandle, (uint16_t*)AudioBuf, 2*AUDIO_HALF_SAMPLES) != HAL_OK) {
			
        printf("I2S DMA start failed\n");
        return -1;
    }

    printf("WAV playback started\n");
    return 0;
}

void WAV_Stop(void)
{
    if(!playing) return;
    HAL_I2S_DMAStop(i2sHandle);
    f_close(&wav_file);
    playing = 0;
    printf("WAV stopped\n");
}

void WAV_SetVolume(float vol)
{
    if(vol < 0) vol = 0;
    if(vol > 1) vol = 1;
    volume = vol;
//    printf("Volume set: %.2f\n", volume);
}

// ---------------- DMA 回调 ----------------
//void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
//{
//    if(hi2s->Instance != i2sHandle->Instance) return;
//	  buf0_need_fill = 1;   // 前半缓冲需要填充
//}

//void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
//{
//    if(hi2s->Instance != i2sHandle->Instance) return;
//    buf1_need_fill = 1;   // 前半缓冲需要填充
//}
extern SemaphoreHandle_t xI2SSemaphore;

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if(hi2s->Instance != i2sHandle->Instance) return;
    buf0_need_fill = 1;   // 前半缓冲需要填充
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xI2SSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if(hi2s->Instance != i2sHandle->Instance) return;
    buf1_need_fill = 1;   // 后半缓冲需要填充
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xI2SSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void wav_proc(void)
{
	

      if(buf0_need_fill)
    {
        FillHalfBufferLoop(0);
        buf0_need_fill = 0;
    }

    if(buf1_need_fill)
    {
        FillHalfBufferLoop(1);
        buf1_need_fill = 0;
    }
}


void update_volume(void)
{
    int16_t diff = __HAL_TIM_GET_COUNTER(&htim4); // 读取当前脉冲数
    __HAL_TIM_SET_COUNTER(&htim4, 0);            // 读取完清零

    if(diff != 0)
    {
        if(diff < 0 || __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4))
        {
            volume += 0.01f * abs(diff);  // 逆时针 -> 减小音量
        }
        else
        {
            volume -= 0.01f * abs(diff);  // 顺时针 -> 增大音量
        } 

        // 限制音量在 0~1 之间
        if(volume > 1.0f) volume = 1.0f;
        if(volume < 0.0f) volume = 0.0f;

        WAV_SetVolume(volume);
    }
}

