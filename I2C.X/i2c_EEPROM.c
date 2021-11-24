#include <xc.h>
#include "i2c_EEPROM.h"

#define _XTAL_FREQ 16000000
#define EEPROM_Address_R 0xA1
#define EEPROM_Address_W 0xA0
    
//---------------[ I2C Routines ]-------------------
//--------------------------------------------------
void I2C_Master_Init(const unsigned long baud)
{
  SSP1CON1 = 0b00101000;
  SSP1CON2 = 0;
  SSP1ADD = (unsigned char)(_XTAL_FREQ/(4*baud))-1;
  SSP1STAT = 0;
 DIO_init (&Dio_configutation_C);
// DIO_Write(GPIOC,BIT3|BIT4,LOW);
}
void I2C_Master_Wait()
{
  while ((SSP1STAT & 0x04) || (SSP1CON2 & 0x1F));
}
void I2C_Master_Start()
{
  I2C_Master_Wait();
  SSP1CON2|=_SSP1CON2_SEN1_MASK ;
}
void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  SSP1CON2 |=_SSP1CON2_RSEN1_MASK ;
}
void I2C_Master_Stop()
{
  I2C_Master_Wait();
  SSP1CON2|=_SSP1CON2_PEN_MASK ;
}

unsigned char I2C_Master_Write(unsigned char data)
{
  I2C_Master_Wait();
  SSP1BUF = data;
  while(!SSPIF); // Wait Until Completion
  SSPIF=1;
  return READBIT(SSP1CON2,ACKSTAT);
}
unsigned char I2C_Read_Byte(void)
{
  //---[ Receive & Return A Byte ]---
  I2C_Master_Wait();
  RCEN1=1; // Enable & Start Reception
  while(!SSPIF); // Wait Until Completion
  SSPIF=0 ; // Clear The Interrupt Flag Bit
  I2C_Master_Wait();
  return SSPBUF; // Return The Received Byte
}
void I2C_ACK(void)
{
  CLEAR_BIT(SSP1CON2,_SSP1CON2_ACKDT1_POSITION); // 0 -> ACK
  I2C_Master_Wait();
  SET_BIT(SSP1CON2,_SSP1CON2_ACKEN1_POSITION); // Send ACK
}
void I2C_NACK(void)
{
  SET_BIT (SSP1CON2,_SSP1CON2_ACKDT1_POSITION) ; // 1 -> NACK
  I2C_Master_Wait();
  SET_BIT( SSP1CON2,_SSP1CON2_ACKEN1_POSITION) ; // Send NACK
}
//======================================================
//---------------[ I2C EEPROM Routines ]----------------
//------------------------------------------------------
//-----[ Write Operations ]-----
// EEPROM Write Byte
void EEPROM_Write(unsigned int add, unsigned char data)
{
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  if(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_Write(data);
  I2C_Master_Stop();
}
// EEPROM Write Page
void EEPROM_Write_Page(unsigned int add, unsigned char* data, unsigned char len)
{
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  for(unsigned int i=0; i<len; i++)
    I2C_Master_Write(data[i]);
  I2C_Master_Stop();
}
//-----------------------------
//-----[ Read Operations ]-----
//---[ Byte Read ]---
unsigned char EEPROM_Read(unsigned int add)
{
  unsigned char Data;
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  //while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_RepeatedStart();
  I2C_Master_Write(EEPROM_Address_R);
  Data = I2C_Read_Byte();
  I2C_NACK();
  I2C_Master_Stop();
  return Data;
}
//---[ Sequential Read ]---
void EEPROM_Read_Page(unsigned int add, unsigned char* data, unsigned int len)
{
  I2C_Master_Start();
  // Wait Until EEPROM Is IDLE
  while(I2C_Master_Write(EEPROM_Address_W))
    I2C_Master_RepeatedStart();
  I2C_Master_Write(add>>8);
  I2C_Master_Write((unsigned char)add);
  I2C_Master_RepeatedStart();
  I2C_Master_Write(EEPROM_Address_R);
  for(unsigned int i=0; i<len; i++)
  {
    data[i] = I2C_Read_Byte();
    I2C_ACK();
  }
  I2C_Master_Stop();
}

