#include "i2c.h"
 
/** I2C bus interface */
#define I2C_PORT GPIOB                //Change
#define SDA_Pin  GPIO_Pin_9           //Change
#define SCL_Pin GPIO_Pin_8           //Change
 
#define FAILURE 0
#define SUCCESS 1
 
 //Configure the SDA signal line as input mode
void SDA_Input_Mode()                   //Change
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  GPIO_InitStructure.GPIO_Pin = SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
 
    GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}
 
 //Configure the SDA signal line as output mode
void SDA_Output_Mode()                   //Change
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  GPIO_InitStructure.GPIO_Pin = SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 
    GPIO_Init(I2C_PORT, &GPIO_InitStructure);
}
 
//
void SDA_Output(uint16_t val)            //Change
{
  if (val) {
    GPIO_SetBits(I2C_PORT,SDA_Pin);
  } else {
    GPIO_ResetBits(I2C_PORT,SDA_Pin);
  }
}
 
//
void SCL_Output(uint16_t val)            //Change
{
  if (val) {
    GPIO_SetBits(I2C_PORT,SCL_Pin);
  } else {
    GPIO_ResetBits(I2C_PORT,SCL_Pin);
  }
}
 
//
uint8_t SDA_Input()                   //Change
{
  return GPIO_ReadInputDataBit(I2C_PORT, SDA_Pin);
}
 
 //Delay program
void delay1(unsigned int n)
{
  unsigned int i;
  for (i=0;i<n;++i);
}
 
 //I2C bus start
void I2CStart(void)
{
  SCL_Output(0);delay1(500);
  SDA_Output(1);delay1(500);
  SCL_Output(1);delay1(500);
  SDA_Output(0);delay1(500);
  SCL_Output(0);delay1(500);
}
 
 //I2C bus stop
void I2CStop(void)
{
  SCL_Output(0); delay1(500);
  SDA_Output(0); delay1(500);
  SCL_Output(1); delay1(500);
  SDA_Output(1); delay1(500);
 
}
 
 //Waiting for response
unsigned char I2CWaitAck(void)
{
  unsigned short cErrTime = 5;
  SDA_Input_Mode(); 
  delay1(500);
  SCL_Output(1);delay1(500);
  while(SDA_Input())
  {
    cErrTime--;
    delay1(500);
    if (0 == cErrTime)
    {
      SDA_Output_Mode();
//      I2CStop();
      return FAILURE;
    }
  }
  SDA_Output_Mode();
  SCL_Output(0);delay1(500); 
  return SUCCESS;
}
 
 //Send response bit
void I2CSendAck(void)
{
  SDA_Output(0);delay1(500);
  delay1(500);
  SCL_Output(1); delay1(500);
  SCL_Output(0); delay1(500);
 
}
 
//
void I2CSendNotAck(void)
{
  SDA_Output(1);
  delay1(500);
  SCL_Output(1); delay1(500);
  SCL_Output(0); delay1(500);
 
}
 
 //Send a byte of data through the I2C bus
void I2CSendByte(unsigned char cSendByte)
{
  unsigned char  i = 8;
  while (i--)
  {
    SCL_Output(0);delay1(500); 
    SDA_Output(cSendByte & 0x80); delay1(500);
    cSendByte += cSendByte;
    delay1(500); 
    SCL_Output(1);delay1(500); 
  }
  SCL_Output(0);delay1(500); 
}
 
 //Receive a byte of data from the I2C bus
unsigned char I2CReceiveByte(void)
{
  unsigned char i = 8;
  unsigned char cR_Byte = 0;
  SDA_Input_Mode(); 
  while (i--)
  {
    cR_Byte += cR_Byte;
    SCL_Output(0);delay1(500); 
    delay1(500); 
    SCL_Output(1);delay1(500); 
    cR_Byte |=  SDA_Input(); 
  }
  SCL_Output(0);delay1(500); 
  SDA_Output_Mode();
  return cR_Byte;
}
 
 //I2C bus initialization
void i2c_init()                   //Change
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = SDA_Pin | SCL_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // **
 
    GPIO_Init(I2C_PORT, &GPIO_InitStructure);
 
}
