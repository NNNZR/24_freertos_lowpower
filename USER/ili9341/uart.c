/**
 ****************************************************************************************************
 * @file        usart.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       串口初始化代码(一般是串口1)，支持printf
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 阿波罗 F429开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20220420
 * 第一次发布
 *
 ****************************************************************************************************
 */


#include "uart.h"
#include "cmsis_os.h"
#include "string.h"
#include "w25qxx.h"
/******************************************************************************************/
/* 加入以下代码, 支持printf函数, 而不需要选择use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t");          /* 声明不使用半主机模式 */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */

#else
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式 */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
int fputc(int ch, FILE *f)
{
    while ((USART_UX->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */

    USART_UX->DR = (uint8_t)ch;                       /* 将要发送的字符 ch 写入到DR寄存器 */
    return ch;
}
#endif
/***********************************************END*******************************************/
    
#if USART_EN_RX                                     /* 如果使能了接收 */

/* 接收缓冲, 最大USART_REC_LEN个字节. */
uint8_t g_usart_rx_buf[USART_REC_LEN];

/*  接收状态
 *  bit15，      接收完成标志
 *  bit14，      接收到0x0d
 *  bit13~0，    接收到的有效字节数目
*/
uint16_t g_usart_rx_sta = 0;

uint8_t g_rx_buffer[RXBUFFERSIZE];                  /* HAL库使用的串口接收缓冲 */

UART_HandleTypeDef g_uart1_handle;                  /* UART句柄 */


/**
 * @brief       串口X初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @retval      无
 */
void usart_init(uint32_t baudrate)
{
    g_uart1_handle.Instance = USART_UX;                         /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                    /* 波特率 */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
    HAL_UART_Init(&g_uart1_handle);                             /* HAL_UART_Init()会使能UART1 */
    
    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
}

/**
 * @brief       UART底层初始化函数
 * @param       huart: UART句柄类型指针
 * @note        此函数会被HAL_UART_Init()调用
 *              完成时钟使能，引脚配置，中断配置
 * @retval      无
 */
//void HAL_UART_MspInit(UART_HandleTypeDef *huart)
//{
//    GPIO_InitTypeDef gpio_init_struct;
//    if(huart->Instance == USART_UX)                             /* 如果是串口1，进行串口1 MSP初始化 */
//    {
//        USART_UX_CLK_ENABLE();                                  /* USART1 时钟使能 */
//        USART_TX_GPIO_CLK_ENABLE();                             /* 发送引脚时钟使能 */
//        USART_RX_GPIO_CLK_ENABLE();                             /* 接收引脚时钟使能 */

//        gpio_init_struct.Pin = USART_TX_GPIO_PIN;               /* TX引脚 */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
//        gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
//        gpio_init_struct.Alternate = USART_TX_GPIO_AF;          /* 复用为USART1 */
//        HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);   /* 初始化发送引脚 */

//        gpio_init_struct.Pin = USART_RX_GPIO_PIN;               /* RX引脚 */
//        gpio_init_struct.Alternate = USART_RX_GPIO_AF;          /* 复用为USART1 */
//        HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);   /* 初始化接收引脚 */

//#if USART_EN_RX
//        HAL_NVIC_EnableIRQ(USART_UX_IRQn);                      /* 使能USART1中断通道 */
//        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);              /* 抢占优先级3，子优先级3 */
//#endif
//    }
//}
extern int home_digital_clock_1_hour_value;
extern int home_digital_clock_1_min_value;
extern int home_digital_clock_1_sec_value;
extern char home_digital_clock_1_meridiem[];


uint8_t rx1_ch;           // 单字节接收
char rx1_buf[20]; // 接收缓存
static uint8_t rx1_index = 0;

uint8_t rx2_ch;           // 单字节接收
static char rx2_buf[10]; // 接收缓存
static uint8_t rx2_index = 0;

uint8_t rx3_ch;           // 单字节接收
static char rx3_buf[10]; // 接收缓存
static uint8_t rx3_index = 0;

uint8_t rx6_ch;           // 单字节接收
static char rx6_buf[10]; // 接收缓存
static uint8_t rx6_index = 0;

extern QueueHandle_t uartCmdQueueHandle;
extern QueueHandle_t mouseCmdQueueHandle;

extern volatile BaseType_t mouseCmdNew;
/**
 * @brief       Rx传输回调函数
 * @param       huart: UART句柄类型指针
 * @retval      无
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) {
		if (rx1_index < 20 - 1) {
			rx1_buf[rx1_index++] = rx1_ch;
			if (rx1_ch == '\n') {
				rx1_buf[rx1_index] = '\0';
				if (strncmp(rx1_buf, "PD:", 3) == 0) {
                    // 找到冒号后面的内容
                    char *p = strchr(rx1_buf, ':');
                    if (p != NULL) {
                        p++; // 跳过冒号
                        // 去掉 \r\n
                        char *end = strpbrk(p, "\r\n");
                        if (end) *end = '\0';
						W25QXX_RTOSISR(WRITE, 0x001000, (uint8_t*)p, strlen(p)+1);
                    }
                }
				rx1_index = 0;
			}
		} else {
			rx1_index = 0;
		}
			HAL_UART_Receive_IT(&huart1, &rx1_ch, 1);
	}
	if (huart->Instance == USART2) {
		if (rx2_index < 10 - 1) {
			rx2_buf[rx2_index++] = rx2_ch;
			if (rx2_ch == '\n') {
				rx2_buf[rx2_index] = '\0';
				xQueueSendFromISR(uartCmdQueueHandle, rx2_buf, NULL);
				xQueueSendFromISR(mouseCmdQueueHandle, rx2_buf, NULL);
				rx2_index = 0;
				mouseCmdNew = pdTRUE;
			}
		} else {
			rx2_index = 0;
		}
			HAL_UART_Receive_IT(&huart2, &rx2_ch, 1);
}
    if (huart->Instance == USART3) {
    if (rx3_index < 10 - 1) {
        rx3_buf[rx3_index++] = rx3_ch;
        if (rx3_ch == '\n') {
            rx3_buf[rx3_index] = '\0';
			xQueueSendFromISR(mouseCmdQueueHandle, rx3_buf, NULL);
            rx3_index = 0;
			mouseCmdNew = pdTRUE;
        }
    } else {
        rx3_index = 0;
    }
     HAL_UART_Receive_IT(&huart3, &rx3_ch, 1);
	}
    if (huart->Instance == USART6) {
        if (rx6_ch == '\n') {   // 接收到换行，说明一帧结束
            rx6_buf[rx6_index] = '\0';  // 结束符
            rx6_index = 0;

            int hour, min, sec;
            if (sscanf(rx6_buf, "%d:%d:%d", &hour, &min, &sec) == 3) {
                // 直接修改全局变量，lvgl 定时器会用它刷新
                home_digital_clock_1_hour_value = hour;
                home_digital_clock_1_min_value  = min;
                home_digital_clock_1_sec_value  = sec;

                if (hour >= 12) {
                    strcpy(home_digital_clock_1_meridiem, "PM");
                    if (hour > 12) home_digital_clock_1_hour_value -= 12;
                } else {
                    strcpy(home_digital_clock_1_meridiem, "AM");
                    if (hour == 0) home_digital_clock_1_hour_value = 12;
                }
            }
        } 
        else {
            if (rx6_index < sizeof(rx6_buf) - 1) {
                rx6_buf[rx6_index++] = rx6_ch;
            }
        }

        // 再次打开中断接收下一个字节
        HAL_UART_Receive_IT(&huart6, &rx6_ch, 1);
    }
	
}

/**
 * @brief       串口1中断服务函数
 * @param       无
 * @retval      无
 */
void USART_UX_IRQHandler(void)
{ 
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;
    
    HAL_UART_IRQHandler(&g_uart1_handle);       /* 调用HAL库中断处理公用函数 */

    timeout = 0;
    while (HAL_UART_GetState(&g_uart1_handle) != HAL_UART_STATE_READY) /* 等待就绪 */
    {
        timeout++;                              /* 超时处理 */
        if(timeout > maxDelay)
        {
            break;
        }
    }
     
    timeout=0;
    
    /* 一次处理完成之后，重新开启中断并设置RxXferCount为1 */
    while (HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE) != HAL_OK)
    {
        timeout++;                              /* 超时处理 */
        if (timeout > maxDelay)
        {
            break;
        }
    }

}

#endif


 

 




