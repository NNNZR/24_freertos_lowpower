#include "key.h"

#define KB1  HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2)
#define KB2  HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)
#define KB3  HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)
#define KB4  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)
#define KB5  HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)
#define KB6  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
#define KB7  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)

// 将每个按键状态移位组合成一个字节（7位有效按键，低电平有效）
#define KEYPORT  (KB1 | (KB2 << 1) | (KB3 << 2) | (KB4 << 3) | (KB5 << 4) | (KB6 << 5) | (KB7 << 6))

uint8_t Trg;   // 单次按键触发（只在按下瞬间为1）
uint8_t Cont;  // 持续按键状态（按下时保持为1）

void Key_Read(void)
{
    uint8_t ReadData = (KEYPORT) ^ 0x7F;   // 取反，低电平有效，掩码保留 7 位
    Trg = ReadData & (ReadData ^ Cont);    // 取上升沿（新按下）
    Cont = ReadData;                       // 保存当前按键状态
}



