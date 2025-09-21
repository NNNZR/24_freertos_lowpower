#include "w25qxx.h" 
#include "spi.h"
#include "delay.h"	   
#include "uart.h"	


//////////////////////////////////////////////////////////////////////////////////	 

//STM32F407开发板
//W25QXX 驱动代码	   
							  
////////////////////////////////////////////////////////////////////////////////// 	
 
u16 W25QXX_TYPE=W25Q16;	//默认是W25Q16

													 
//初始化SPI FLASH的IO口
void W25QXX_Init(void)
{ 
//  GPIO_InitTypeDef  GPIO_InitStructure;
//  
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
//  

//	  //PA15 初始化
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//PA15
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化


	
	
//	W25QXX_CS=1;			//SPI FLASH不选中
//	SPI1_Init();		   			//初始化SPI
//	SPI1_SetSpeed(SPI_BaudRatePrescaler_4);		//设置为21M时钟,高速模式 
	
	
	W25QXX_CS_Clr();
	W25QXX_TYPE=W25QXX_ReadID();	//读取FLASH ID.
}  


uint8_t SPI3_ReadWriteByte(uint8_t TxData)
{
    uint8_t RxData;
    HAL_SPI_TransmitReceive(&hspi3, &TxData, &RxData, 1, HAL_MAX_DELAY);
    return RxData;
}
// 读取W25QXX的状态寄存器
// BIT7  6   5   4   3   2   1   0
// SPR   RV  TB  BP2 BP1 BP0 WEL BUSY
uint8_t W25QXX_ReadSR(void)
{
    uint8_t byte = 0;

    W25QXX_CS_Clr();                                // CS拉低，选中器件
    SPI3_ReadWriteByte(W25X_ReadStatusReg);         // 发送读取状态寄存器命令
    byte = SPI3_ReadWriteByte(0xFF);                // 读取一个字节
    W25QXX_CS_Set();                                // CS拉高，取消选中

    return byte;
}

// 写W25QXX状态寄存器
// 只有 SPR,TB,BP2,BP1,BP0 (bit7,5,4,3,2) 可以写
void W25QXX_Write_SR(uint8_t sr)
{
    W25QXX_CS_Clr();                                // CS拉低
    SPI3_ReadWriteByte(W25X_WriteStatusReg);        // 发送写状态寄存器命令
    SPI3_ReadWriteByte(sr);                         // 写入一个字节
    W25QXX_CS_Set();                                // CS拉高
}

// W25QXX写使能，将WEL置位
void W25QXX_Write_Enable(void)
{
    W25QXX_CS_Clr();                                // CS拉低
    SPI3_ReadWriteByte(W25X_WriteEnable);           // 发送写使能命令
    W25QXX_CS_Set();                                // CS拉高
}

// W25QXX写禁止，将WEL清零
void W25QXX_Write_Disable(void)
{
    W25QXX_CS_Clr();                                // CS拉低
    SPI3_ReadWriteByte(W25X_WriteDisable);          // 发送写禁止命令
    W25QXX_CS_Set();                                // CS拉高
}


//读取芯片ID
//返回值如下:				   
//0XEF13,表示芯片型号为W25Q80  
//0XEF14,表示芯片型号为W25Q16    
//0XEF15,表示芯片型号为W25Q32  
//0XEF16,表示芯片型号为W25Q64 
//0XEF17,表示芯片型号为W25Q128 	  
uint16_t W25QXX_ReadID(void)
{
    uint16_t Temp = 0;

    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(0x90);                  // 发送读取ID命令
    SPI3_ReadWriteByte(0x00);                  
    SPI3_ReadWriteByte(0x00);                  
    SPI3_ReadWriteByte(0x00);                  
    Temp |= SPI3_ReadWriteByte(0xFF) << 8;     // 厂商ID
    Temp |= SPI3_ReadWriteByte(0xFF);          // 设备ID
    W25QXX_CS_Set();                            

    return Temp;
} 		    
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void W25QXX_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)   
{ 
    uint16_t i;

    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_ReadData);         // 发送读取命令
    SPI3_ReadWriteByte((uint8_t)(ReadAddr >> 16));
    SPI3_ReadWriteByte((uint8_t)(ReadAddr >> 8));
    SPI3_ReadWriteByte((uint8_t)ReadAddr);
    for(i = 0; i < NumByteToRead; i++)
    {
        pBuffer[i] = SPI3_ReadWriteByte(0xFF); // 循环读取
    }
    W25QXX_CS_Set();                            
}
//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
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
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
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
//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)						
//NumByteToWrite:要写入的字节数(最大65535)   
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
        if(i < secremain) // 需要擦除
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
//擦除整个芯片		  
//等待时间超长...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();                  
    W25QXX_Wait_Busy();   
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_ChipErase);     
    W25QXX_CS_Set();                            
    W25QXX_Wait_Busy();                       
} 
//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个山区的最少时间:150ms
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
//等待空闲
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  
//进入掉电模式
void W25QXX_PowerDown(void)   
{ 
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_PowerDown);     
    W25QXX_CS_Set();                             //取消片选     	      
    delay_us(3);                               //等待TPD  
}   
//唤醒
void W25QXX_WAKEUP(void)   
{  
    W25QXX_CS_Clr();                            
    SPI3_ReadWriteByte(W25X_ReleasePowerDown);  
    W25QXX_CS_Set();                              //取消片选     	      
    delay_us(3);                               //等待TRES1
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



















