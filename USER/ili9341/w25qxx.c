#include "w25qxx.h" 
#include "spi.h"
#include "delay.h"	   
#include "uart.h"	


//////////////////////////////////////////////////////////////////////////////////	 

//STM32F407������
//W25QXX ��������	   
							  
////////////////////////////////////////////////////////////////////////////////// 	
 
u16 W25QXX_TYPE=W25Q16;	//Ĭ����W25Q16

													 
//��ʼ��SPI FLASH��IO��
void W25QXX_Init(void)
{ 
//  GPIO_InitTypeDef  GPIO_InitStructure;
//  
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
//  

//	  //PA15 ��ʼ��
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//PA15
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��


	
	
//	W25QXX_CS=1;			//SPI FLASH��ѡ��
//	SPI1_Init();		   			//��ʼ��SPI
//	SPI1_SetSpeed(SPI_BaudRatePrescaler_4);		//����Ϊ21Mʱ��,����ģʽ 
	
	
	W25QXX_CS_Clr();
	W25QXX_TYPE=W25QXX_ReadID();	//��ȡFLASH ID.
}  


uint8_t SPI3_ReadWriteByte(uint8_t TxData)
{
    uint8_t RxData;
    HAL_SPI_TransmitReceive(&hspi3, &TxData, &RxData, 1, HAL_MAX_DELAY);
    return RxData;
}
// ��ȡW25QXX��״̬�Ĵ���
// BIT7  6   5   4   3   2   1   0
// SPR   RV  TB  BP2 BP1 BP0 WEL BUSY
uint8_t W25QXX_ReadSR(void)
{
    uint8_t byte = 0;

    W25QXX_CS_Clr();                                // CS���ͣ�ѡ������
    SPI3_ReadWriteByte(W25X_ReadStatusReg);         // ���Ͷ�ȡ״̬�Ĵ�������
    byte = SPI3_ReadWriteByte(0xFF);                // ��ȡһ���ֽ�
    W25QXX_CS_Set();                                // CS���ߣ�ȡ��ѡ��

    return byte;
}

// дW25QXX״̬�Ĵ���
// ֻ�� SPR,TB,BP2,BP1,BP0 (bit7,5,4,3,2) ����д
void W25QXX_Write_SR(uint8_t sr)
{
    W25QXX_CS_Clr();                                // CS����
    SPI3_ReadWriteByte(W25X_WriteStatusReg);        // ����д״̬�Ĵ�������
    SPI3_ReadWriteByte(sr);                         // д��һ���ֽ�
    W25QXX_CS_Set();                                // CS����
}

// W25QXXдʹ�ܣ���WEL��λ
void W25QXX_Write_Enable(void)
{
    W25QXX_CS_Clr();                                // CS����
    SPI3_ReadWriteByte(W25X_WriteEnable);           // ����дʹ������
    W25QXX_CS_Set();                                // CS����
}

// W25QXXд��ֹ����WEL����
void W25QXX_Write_Disable(void)
{
    W25QXX_CS_Clr();                                // CS����
    SPI3_ReadWriteByte(W25X_WriteDisable);          // ����д��ֹ����
    W25QXX_CS_Set();                                // CS����
}


//��ȡоƬID
//����ֵ����:				   
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80  
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16    
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32  
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64 
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128 	  
uint16_t W25QXX_ReadID(void)
{
    uint16_t Temp = 0;

    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(0x90);                  // ���Ͷ�ȡID����
    SPI3_ReadWriteByte(0x00);                  
    SPI3_ReadWriteByte(0x00);                  
    SPI3_ReadWriteByte(0x00);                  
    Temp |= SPI3_ReadWriteByte(0xFF) << 8;     // ����ID
    Temp |= SPI3_ReadWriteByte(0xFF);          // �豸ID
    W25QXX_CS_Set();                            

    return Temp;
} 		    
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void W25QXX_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)   
{ 
    uint16_t i;

    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_ReadData);         // ���Ͷ�ȡ����
    SPI3_ReadWriteByte((uint8_t)(ReadAddr >> 16));
    SPI3_ReadWriteByte((uint8_t)(ReadAddr >> 8));
    SPI3_ReadWriteByte((uint8_t)ReadAddr);
    for(i = 0; i < NumByteToRead; i++)
    {
        pBuffer[i] = SPI3_ReadWriteByte(0xFF); // ѭ����ȡ
    }
    W25QXX_CS_Set();                            
}
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!	 
void W25QXX_Write_Page(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t i;

    W25QXX_Write_Enable();                     
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_PageProgram);      
    SPI3_ReadWriteByte((uint8_t)(WriteAddr >> 16));
    SPI3_ReadWriteByte((uint8_t)(WriteAddr >> 8));
    SPI3_ReadWriteByte((uint8_t)WriteAddr);
    for(i = 0; i < NumByteToWrite; i++) 
        SPI3_ReadWriteByte(pBuffer[i]);
    W25QXX_CS_Set();                            
    W25QXX_Wait_Busy();                        
}
//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void W25QXX_Write_NoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)   
{                       
    uint16_t pageremain;      
    pageremain = 256 - WriteAddr % 256;        
    if(NumByteToWrite <= pageremain) pageremain = NumByteToWrite;
    while(1)
    {      
        W25QXX_Write_Page(pBuffer, WriteAddr, pageremain);
        if(NumByteToWrite == pageremain) break;
        else 
        {
            pBuffer += pageremain;
            WriteAddr += pageremain; 
            NumByteToWrite -= pageremain;
            if(NumByteToWrite > 256) pageremain = 256;
            else pageremain = NumByteToWrite;
        }
    };      
}
//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)						
//NumByteToWrite:Ҫд����ֽ���(���65535)   
uint8_t W25QXX_BUFFER[4096];        
void W25QXX_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)   
{ 
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;       
    uint16_t i;    
    uint8_t * W25QXX_BUF;     
    W25QXX_BUF = W25QXX_BUFFER;        

    secpos = WriteAddr / 4096;      
    secoff = WriteAddr % 4096;      
    secremain = 4096 - secoff;      

    if(NumByteToWrite <= secremain) secremain = NumByteToWrite;
    while(1) 
    {   
        W25QXX_Read(W25QXX_BUF, secpos * 4096, 4096);    
        for(i = 0; i < secremain; i++) 
        {
            if(W25QXX_BUF[secoff + i] != 0xFF) break;     
        }
        if(i < secremain) // ��Ҫ����
        {
            W25QXX_Erase_Sector(secpos);
            for(i = 0; i < secremain; i++) 
                W25QXX_BUF[i + secoff] = pBuffer[i];
            W25QXX_Write_NoCheck(W25QXX_BUF, secpos * 4096, 4096);
        } 
        else 
        {
            W25QXX_Write_NoCheck(pBuffer, WriteAddr, secremain);
        }

        if(NumByteToWrite == secremain) break;
        else 
        {
            secpos++;
            secoff = 0;
            pBuffer += secremain;
            WriteAddr += secremain; 
            NumByteToWrite -= secremain;
            if(NumByteToWrite > 4096) secremain = 4096;
            else secremain = NumByteToWrite;
        }  
    };  
}
//��������оƬ		  
//�ȴ�ʱ�䳬��...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();                  
    W25QXX_Wait_Busy();   
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_ChipErase);     
    W25QXX_CS_Set();                            
    W25QXX_Wait_Busy();                       
} 
//����һ������
//Dst_Addr:������ַ ����ʵ����������
//����һ��ɽ��������ʱ��:150ms
void W25QXX_Erase_Sector(uint32_t Dst_Addr)   
{  
//    printf("fe:%lx\r\n", Dst_Addr);        
    Dst_Addr *= 4096;
    W25QXX_Write_Enable();                  
    W25QXX_Wait_Busy();   
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_SectorErase);   
    SPI3_ReadWriteByte((uint8_t)(Dst_Addr >> 16));
    SPI3_ReadWriteByte((uint8_t)(Dst_Addr >> 8));
    SPI3_ReadWriteByte((uint8_t)Dst_Addr);
    W25QXX_CS_Set();                            
    W25QXX_Wait_Busy();                       
}
//�ȴ�����
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  
//�������ģʽ
void W25QXX_PowerDown(void)   
{ 
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_PowerDown);     
    W25QXX_CS_Set();                             //ȡ��Ƭѡ     	      
    delay_us(3);                               //�ȴ�TPD  
}   
//����
void W25QXX_WAKEUP(void)   
{  
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_ReleasePowerDown);  
    W25QXX_CS_Set();                              //ȡ��Ƭѡ     	      
    delay_us(3);                               //�ȴ�TRES1
}   


QueueHandle_t w25qxxQueue;
void W25QXX_RTOS(W25QXX_OpType type, uint32_t addr, uint8_t* buf, uint32_t len)
{
    W25QXX_Request req = { type, addr, buf, len };
    xQueueSendToBack(w25qxxQueue, &req, portMAX_DELAY);
}

void W25QXX_RTOSISR(W25QXX_OpType type, uint32_t addr, uint8_t* buf, uint32_t len)
{
    W25QXX_Request req = { type, addr, buf, len };
    xQueueSendToBackFromISR(w25qxxQueue, &req, NULL);
}



















