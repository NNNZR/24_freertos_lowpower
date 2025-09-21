#include "key.h"

#define KB1  HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2)
#define KB2  HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)
#define KB3  HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)
#define KB4  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)
#define KB5  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)
#define KB6  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
#define KB7  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)

// ��ÿ������״̬��λ��ϳ�һ���ֽڣ�7λ��Ч�������͵�ƽ��Ч��
#define KEYPORT  (KB1 | (KB2 << 1) | (KB3 << 2) | (KB4 << 3) | (KB5 << 4) | (KB6 << 5) | (KB7 << 6))

uint8_t Trg;   // ���ΰ���������ֻ�ڰ���˲��Ϊ1��
uint8_t Cont;  // ��������״̬������ʱ����Ϊ1��

void Key_Read(void)
{
    uint8_t ReadData = (KEYPORT) ^ 0x7F;   // ȡ�����͵�ƽ��Ч�����뱣�� 7 λ
    Trg = ReadData & (ReadData ^ Cont);    // ȡ�����أ��°��£�
    Cont = ReadData;                       // ���浱ǰ����״̬
}



