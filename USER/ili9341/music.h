#ifndef __MUSIC_H
#define __MUSIC_H

#include "main.h"
#include "fatfs.h"
#include <stdint.h>
#include <stddef.h>




// ---------------- ���� ----------------
#define AUDIO_HALF_SAMPLES 1024*2  // ÿ�뻺����������16-bit��
#define SAMPLE_BYTES       2         // ÿ�������ֽ���
#define AUDIO_CHANNELS_MAX 2         // ֧�����������

typedef struct {
    uint16_t numChannels;
    uint32_t sampleRate;
    uint16_t bitsPerSample;
    uint32_t dataSize;
    uint32_t dataStartPos;
} WAV_Header_t;

// �ӿ�
int WAV_PlayFile(const char *filename, I2S_HandleTypeDef *hi2s);
void WAV_Stop(void);
void WAV_SetVolume(float vol);
void WAV_HalfTransferCallback(void);
void WAV_TransferCompleteCallback(void);

void wav_proc(void);
void update_volume(void);




#endif

