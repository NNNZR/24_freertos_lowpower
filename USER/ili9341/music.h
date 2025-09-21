#ifndef __MUSIC_H
#define __MUSIC_H

#include "main.h"
#include "fatfs.h"
#include <stdint.h>
#include <stddef.h>




// ---------------- 配置 ----------------
#define AUDIO_HALF_SAMPLES 1024*2  // 每半缓冲样本数（16-bit）
#define SAMPLE_BYTES       2         // 每个样本字节数
#define AUDIO_CHANNELS_MAX 2         // 支持最大声道数

typedef struct {
    uint16_t numChannels;
    uint32_t sampleRate;
    uint16_t bitsPerSample;
    uint32_t dataSize;
    uint32_t dataStartPos;
} WAV_Header_t;

// 接口
int WAV_PlayFile(const char *filename, I2S_HandleTypeDef *hi2s);
void WAV_Stop(void);
void WAV_SetVolume(float vol);
void WAV_HalfTransferCallback(void);
void WAV_TransferCompleteCallback(void);

void wav_proc(void);
void update_volume(void);




#endif

