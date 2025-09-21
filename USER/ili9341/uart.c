/**
 ****************************************************************************************************
 * @file        usart.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       ���ڳ�ʼ������(һ���Ǵ���1)��֧��printf
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ������ F429������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20220420
 * ��һ�η���
 *
 ****************************************************************************************************
 */


#include "uart.h"
#include "cmsis_os.h"
#include "string.h"
#include "w25qxx.h"
/******************************************************************************************/
/* �������´���, ֧��printf����, ������Ҫѡ��use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");          /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE �� stdio.h���涨��. */
FILE __stdout;

/* �ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{
    while ((USART_UX->SR & 0X40) == 0);               /* �ȴ���һ���ַ�������� */

    USART_UX->DR = (uint8_t)ch;                       /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}
#endif
/***********************************************END*******************************************/
    
#if USART_EN_RX                                     /* ���ʹ���˽��� */

/* ���ջ���, ���USART_REC_LEN���ֽ�. */
uint8_t g_usart_rx_buf[USART_REC_LEN];

/*  ����״̬
 *  bit15��      ������ɱ�־
 *  bit14��      ���յ�0x0d
 *  bit13~0��    ���յ�����Ч�ֽ���Ŀ
*/
uint16_t g_usart_rx_sta = 0;

uint8_t g_rx_buffer[RXBUFFERSIZE];                  /* HAL��ʹ�õĴ��ڽ��ջ��� */

UART_HandleTypeDef g_uart1_handle;                  /* UART��� */


/**
 * @brief       ����X��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @retval      ��
 */
void usart_init(uint32_t baudrate)
{
    g_uart1_handle.Instance = USART_UX;                         /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                    /* ������ */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
    HAL_UART_Init(&g_uart1_handle);                             /* HAL_UART_Init()��ʹ��UART1 */
    
    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
}

/**
 * @brief       UART�ײ��ʼ������
 * @param       huart: UART�������ָ��
 * @note        �˺����ᱻHAL_UART_Init()����
 *              ���ʱ��ʹ�ܣ��������ã��ж�����
 * @retval      ��
 */
//void HAL_UART_MspInit(UART_HandleTypeDef *huart)
//{
//    GPIO_InitTypeDef gpio_init_struct;
//    if(huart->Instance == USART_UX)                             /* ����Ǵ���1�����д���1 MSP��ʼ�� */
//    {
//        USART_UX_CLK_ENABLE();                                  /* USART1 ʱ��ʹ�� */
//        USART_TX_GPIO_CLK_ENABLE();                             /* ��������ʱ��ʹ�� */
//        USART_RX_GPIO_CLK_ENABLE();                             /* ��������ʱ��ʹ�� */

//        gpio_init_struct.Pin = USART_TX_GPIO_PIN;               /* TX���� */
//        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
//        gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
//        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
//        gpio_init_struct.Alternate = USART_TX_GPIO_AF;          /* ����ΪUSART1 */
//        HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);   /* ��ʼ���������� */

//        gpio_init_struct.Pin = USART_RX_GPIO_PIN;               /* RX���� */
//        gpio_init_struct.Alternate = USART_RX_GPIO_AF;          /* ����ΪUSART1 */
//        HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);   /* ��ʼ���������� */

//#if USART_EN_RX
//        HAL_NVIC_EnableIRQ(USART_UX_IRQn);                      /* ʹ��USART1�ж�ͨ�� */
//        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);              /* ��ռ���ȼ�3�������ȼ�3 */
//#endif
//    }
//}
extern int home_digital_clock_1_hour_value;
extern int home_digital_clock_1_min_value;
extern int home_digital_clock_1_sec_value;
extern char home_digital_clock_1_meridiem[];


uint8_t rx1_ch;           // ���ֽڽ���
char rx1_buf[20]; // ���ջ���
static uint8_t rx1_index = 0;

uint8_t rx2_ch;           // ���ֽڽ���
static char rx2_buf[10]; // ���ջ���
static uint8_t rx2_index = 0;

uint8_t rx3_ch;           // ���ֽڽ���
static char rx3_buf[10]; // ���ջ���
static uint8_t rx3_index = 0;

uint8_t rx6_ch;           // ���ֽڽ���
static char rx6_buf[10]; // ���ջ���
static uint8_t rx6_index = 0;

extern QueueHandle_t uartCmdQueueHandle;
extern QueueHandle_t mouseCmdQueueHandle;

extern volatile BaseType_t mouseCmdNew;
/**
 * @brief       Rx����ص�����
 * @param       huart: UART�������ָ��
 * @retval      ��
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) {
		if (rx1_index < 20 - 1) {
			rx1_buf[rx1_index++] = rx1_ch;
			if (rx1_ch == '\n') {
				rx1_buf[rx1_index] = '\0';
				if (strncmp(rx1_buf, "PD:", 3) == 0) {
                    // �ҵ�ð�ź��������
                    char *p = strchr(rx1_buf, ':');
                    if (p != NULL) {
                        p++; // ����ð��
                        // ȥ�� \r\n
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
        if (rx6_ch == '\n') {   // ���յ����У�˵��һ֡����
            rx6_buf[rx6_index] = '\0';  // ������
            rx6_index = 0;

            int hour, min, sec;
            if (sscanf(rx6_buf, "%d:%d:%d", &hour, &min, &sec) == 3) {
                // ֱ���޸�ȫ�ֱ�����lvgl ��ʱ��������ˢ��
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

        // �ٴδ��жϽ�����һ���ֽ�
        HAL_UART_Receive_IT(&huart6, &rx6_ch, 1);
    }
	
}

/**
 * @brief       ����1�жϷ�����
 * @param       ��
 * @retval      ��
 */
void USART_UX_IRQHandler(void)
{ 
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;
    
    HAL_UART_IRQHandler(&g_uart1_handle);       /* ����HAL���жϴ����ú��� */

    timeout = 0;
    while (HAL_UART_GetState(&g_uart1_handle) != HAL_UART_STATE_READY) /* �ȴ����� */
    {
        timeout++;                              /* ��ʱ���� */
        if(timeout > maxDelay)
        {
            break;
        }
    }
     
    timeout=0;
    
    /* һ�δ������֮�����¿����жϲ�����RxXferCountΪ1 */
    while (HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE) != HAL_OK)
    {
        timeout++;                              /* ��ʱ���� */
        if (timeout > maxDelay)
        {
            break;
        }
    }

}

#endif


 

 




