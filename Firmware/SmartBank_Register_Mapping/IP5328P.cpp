#include "i2c.h"
#include "ip5328p.h"
 
 //Write register (8bit)
 //reg: register address
 //data: data to be written
void IP5328P_Write(unsigned char reg,unsigned char data)
{
   I2CStart(); //Start signal
   I2CSendByte(0xEA); //Write slave address
   I2CWaitAck(); //Waiting for response
   I2CSendByte(reg); //Data register address to be written
   I2CWaitAck(); //Waiting for response
   I2CSendByte(data); //Write data
   I2CWaitAck(); //Waiting for response
   I2CStop(); //Stop signal
}
 
 //Read register (8bit)
 //reg: register address
 //data: data to be written
unsigned char IP5328P_Read(unsigned char reg)
{
  unsigned char R_dat;
   I2CStart(); //Start signal
   I2CSendByte(0xEA); //Write slave address
   I2CWaitAck(); //Waiting for a response (you can add it yourself if you don't process it when the response is not received)
 
   I2CSendByte(reg); //Data register address to be written
   I2CWaitAck(); //Waiting for a response (you can add it yourself if you don't process it when the response is not received)
 
   I2CStart(); //As a restart signal  
 
   I2CSendByte(0xEB); //Write the slave address and start the read operation
   I2CWaitAck(); //Waiting for the response (you can add it if you don't process it when the response is not received)
   R_dat=I2CReceiveByte(); //Receive 8bit data
   I2CSendNotAck(); //Send mNACK signal to stop receiving
   I2CStop(); //Stop signal
  return R_dat;
}
 
 
 //Read the battery power display level (only the number of LEDs corresponding to the power can be read)
 //Return: 0001 1111: Lesson 4 lights on 0000 1111: Lesson 3 lights on 0000 0111: Lesson 2 lights on 0000 0011:1 Lesson lights on
 // 0000 0001: low flashing light during discharge 0000 0000: shutdown
unsigned char IP5328P_Electricity(void)
{
  int dat;
   dat=IP5328P_Read(0xDB); //Get the battery indicator level
  return dat;
}
 
 /************************************************* *Reading chip parameter function******************************************* *************/
 
 //Read the true voltage value at both ends of the battery
 //Return the voltage value of float type (decimal)
float IP5328P_BatVoltage(void)
{
  int dat;
  float BatVoltage=0.0f;
   dat=IP5328P_Read(0x64); //Get the lower 8 bits of battery voltage
  BatVoltage += dat;
   dat=IP5328P_Read(0x65); //Get the high 8 bits of battery voltage
   BatVoltage = (dat<<8)+BatVoltage; //Merge high and low bits
   if(BatVoltage==0xffff) return 0; //If 0xffff is read, the chip is not activated at this time, the read value is wrong
   BatVoltage = BatVoltage*0.00026855+2.6; //Calculated as the actual voltage value
  return BatVoltage;
}
 
 //Read battery input or output current
 //Return the current value of float type (decimal) unit ma
float IP5328P_BatCurrent(void)
{
  int dat;
  float Current=0.0f;
   dat=IP5328P_Read(0x66); //Get the lower 8 bits of battery current
  Current += dat;
   dat=IP5328P_Read(0x67); //Get the high 8 bits of battery current
  Current = (dat<<8)+Current; //Merge high and low bits
   if(Current>32767)Current=65535-Current; //Convert negative current to positive
   Current = Current*0.00127883; //Calculated as the actual current value
  return Current;
}
 
 //Read the battery voltage after compensating the internal resistance of the cell and the cell current
 //Return the voltage value of float type (decimal)
float IP5328P_BatOCV(void)
{
  int dat;
  float BatVoltage=0.0f;
   dat=IP5328P_Read(0x7A); //Get the lower 8 bits of battery voltage
  BatVoltage += dat;
   dat=IP5328P_Read(0x7B); //Get the high 8 bits of battery voltage
   BatVoltage = (dat<<8)+BatVoltage; //Merge high and low bits
   if(BatVoltage==0xffff) return 0; //If 0xffff is read, the chip is not activated at this time, the read value is wrong
   BatVoltage = BatVoltage*0.00026855+2.6; //Calculated as the actual voltage value
  return BatVoltage;
}
 
 //Get Type-C interface connection status
 //Return: 0x00 not connected
 // 0x01 connect to mobile phones and other devices that require power supply (the power bank is discharging)
 // 0x02 connect the power adapter (the power bank is charging)
unsigned char IP5328P_TypeC_Flag(void)
{
  unsigned char flag=0,dat=0;
    dat=IP5328P_Read(0xB8);
   if(dat==0xff)return 0; //If 0xff is read, the chip is not activated
  if(dat>>1&0x01)flag=0x01;
  if(dat>>5&0x01)flag=0x02;
  return flag;
}
 
 //Get the output capacity of the adapter connected by Type-C
 //Return: 0x00 chip is not activated
 // 0x01 standard USB
 // 0x02 output capacity 1.5A
 // 0x03 output capacity 3.0A
unsigned char IP5328P_TypeC_Ability(void)
{
  unsigned char flag=0,dat=0;
    dat=IP5328P_Read(0xFF);
   if(dat==0xff)return 0; //If 0xff is read, the chip is not activated
  if(dat>>5&0x01)flag=0x01;
  if(dat>>6&0x01)flag=0x02;
  if(dat>>7&0x01)flag=0x03;
  return flag;
}
 
 
 /********************The following current reading has conditional restrictions ********************* ***********/
 /*********It can be roughly understood that it can be read only when there are multiple interfaces open at the same time********************/
 /*************** Among them, VBUS is TYPE-C port, VIN is Android port********************* ******/
 
 //Read Type-C input or output current
 //Return the current value of float type (decimal) unit ma
 //Condition: when VINOK and VBUSOK are valid at the same time in the charging state and VBUS MOS is turned on;
 // Or when VBUS MOS is turned on and other MOS is also turned on, the ADC will start
 // (The above symbol status can be read by register)
float IP5328P_TypeC_Current(void)
{
  int dat;
  float Current=0.0f;
   dat=IP5328P_Read(0x6E); //Get the low 8 bits of current
  Current += dat;
   dat=IP5328P_Read(0x6F); //Get the high 8 bits of the current
   Current = (dat<<8)+Current; //Merge high and low bits
   if(Current>32767)Current=65535-Current; //Convert negative current to positive
   Current = Current*0.0006394; //Calculated as the actual current value
  return Current;
}
 
 //Read the input current of the Android port
 //Return the current value of float type (decimal) unit ma
 //Condition: The ADC will only start when the charging state VINOK and VBUSOK are valid at the same time and VIN MOS is turned on
 // (The above symbol status can be read by register)
float IP5328P_VIN_Current(void)
{
  int dat;
  float Current=0.0f;
   dat=IP5328P_Read(0x6D); //Get the low 8 bits of current
  Current += dat;
   dat=IP5328P_Read(0x6C); //Get the high 8 bits of the current
   Current = (dat<<8)+Current; //Merge high and low bits
   if(Current>32767)Current=65535-Current; //Convert negative current to positive
   Current = Current*0.0006394; //Calculated as the actual current value
  return Current;
}
 
 //Read OUT1 output current
 //Return the current value of float type (decimal) unit ma
 //Condition: The ADC will only start when the OUT1 MOS is turned on and other MOSs are also turned on;
 // (The above symbol status can be read by register)
float IP5328P_OUT1_Current(void)
{
  int dat;
  float Current=0.0f;
   dat=IP5328P_Read(0x70); //Get the low 8 bits of the current
  Current += dat;
   dat=IP5328P_Read(0x71); //Get the high 8 bits of the current
   Current = (dat<<8)+Current; //Merge high and low bits
   if(Current>32767)Current=65535-Current; //Convert negative current to positive
   Current = Current*0.0006394; //Calculated as the actual current value
  return Current;
}
 
//Read OUT2 output current
 //Return the current value of float type (decimal) unit ma
 //Condition: The ADC will only start when the OUT1 MOS is turned on and other MOSs are also turned on;
 // (The above symbol status can be read by register)
float IP5328P_OUT2_Current(void)
{
  int dat;
  float Current=0.0f;
   dat=IP5328P_Read(0x72); //Get the lower 8 bits of the current
  Current += dat;
   dat=IP5328P_Read(0x73); //Get the high 8 bits of the current
   Current = (dat<<8)+Current; //Merge high and low bits
   if(Current>32767)Current=65535-Current; //Convert negative current to positive
   Current = Current*0.0006394; //Calculated as the actual current value
  return Current;
}
 
 /******************** The above current reading has conditional restrictions ********************* ***********/
 
 //Get the current power
 //Return the power value of float type (decimal)
float IP5328P_Power(void)
{
  int dat;
  float Power=0.0f;
   dat=IP5328P_Read(0x7C); //Get the lower 8 bits of power
  Power += dat;
   dat=IP5328P_Read(0x7D); //Get the high 8 bits of power
   Power = (dat<<8)+Power; //Merge high and low bits
   if(Power==0xffff) return 0; //If 0xffff is read, the chip is not activated at this time, the read value is wrong
   Power = Power*0.00844; //calculated as the actual power value
  return Power;
}
 
 //Get the current power state of the chip
 //Fourth place: 0: discharge 1: charge
 //2:0 bit: 000: standby 001: 5V charging 010: single port with charging and discharging at the same time 011: multiple ports with charging and discharging at the same time
 // 100: high-voltage fast charge and charge 101: 5V discharge 110: multi-port 5V discharge 111: high-voltage fast charge and discharge
 //Other bits: invalid bits
unsigned char IP5328P_SYS_Status(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0xD1);
  if(flag==0xff)return 0;
  return flag;
}
 
 
 //Get the valid status of the input voltage and whether the button is pressed
 //Return: 7:6 invalid digits
 // 5 VBUSOK: 1 TYPE-C interface voltage is valid (both charging and discharging will be valid) 0 interface voltage is invalid
 // 4 VINOK: 1 Android interface voltage is valid 0 Android interface voltage is invalid
 // 3:1 invalid bit
 // 0 key_in: 0 button is pressed 1 button is not pressed
unsigned char IP5328P_KEY_IN(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0xD2);
  if(flag==0xff)return 0;
  return flag;
}
 
 
 //Get the input voltage of Android port and TYPE-C
 //Return: 7:6 invalid digits
//    5:3  TYPE-C_STATE:000-5V,001-7V,011-9V,111-12V 
//    2:0  VIN_STATE   :000-5V,001-7V,011-9V,111-12V
unsigned char IP5328P_VinTypeC_State(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0xD5);
  if(flag==0xff)return 0;
  return flag;
}
 
 //Get charging status
 //Return: 7: 0 It may happen to be stopped charging, it may be full, or it may be abnormally protected. 1 Charging
 // 6: 0 not full 1 full 
 // 5: 0 No timeout when totaling constant voltage and constant current 1 Timeout when totaling constant voltage and constant current
 // 4: 0 Constant voltage timer has not timed out 1 Constant voltage timer has timed out
 // 3: 0 trickle timer has not timed out 1 trickle timer has timed out
 // 2:0 000 idle 001 trickle charge 010 constant current charge 011 constant voltage charge 100 stop charge detection 101 battery full end 110 timeout
unsigned char IP5328P_GHG_State(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0xD7);
  return flag;
}
 
 
 //Get MOS status
 //Returns: 7: 0 The current Android port is charging 1 The current TYPE-C is charging
 // 6: 0 Android port voltage is invalid 1 Android port voltage is valid  
 // 5: 0 TYPE-C voltage is invalid 1 TYPE-C voltage is valid 
 // 4: 0VIN MOS (Android) is not turned on 1VIN MOS (Android) is turned on
 // 3: invalid bit
 // 2: 0VBUS MOS (TYPE-C) is not turned on 1VBUS MOS (TYPE-C) is turned on
 // 1: 0VOUT2 MOS is not turned on 1VOUT2 MOS is turned on
 // 0: 0VOUT1 MOS is not turned on 1VOUT1 MOS is turned on
unsigned char IP5328P_MOS_ON(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0xE5);
  if(flag==0xff)return 0;
  return flag;
}
 
 
 //Get the boost output voltage value range
 //Return: 7:4 invalid bits 
 // 3: 0 is invalid 1 output voltage 10-12V
 // 2: 0 is invalid 1 output voltage 8-10V
 // 1: 0 is invalid 1 output voltage 6-8V
 // 0: 0 non-fast charge 1 fast charge
unsigned char IP5328P_BOOST(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0xFB);
  if(flag==0xff)return 0;
  return flag;
}
 
 //Get whether QC fast charge is enabled (not whether it is being used, but that this function can be used)
 //Return: 7:4 invalid bits 
 // 3: 0 Non-fast charge 1 TYPE-C fast charge enable
 // 2: 0 Non-fast charge 1 Android port fast charge enable
 // 1: 0 non-fast charge 1OUT2 fast charge enable
 // 0: 0 non-fast charge 1OUT1 fast charge enable
unsigned char IP5328P_QC_State(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0x3E);
  if(flag==0xff)return 0;
  return flag;
}
 
 //Get whether fast charge can be used (not whether it is being used, but that this function can be used)
//Returns: 7: Maximum voltage setting supported by MTK PE 1.1 RX 0 12V 1 9V
 // 6: MTK PE2.0 RX enable 0 disable 1 enable 
 // 5: MTK PE1.1 RX enable 0 disable 1 enable 
 // 4: SFCP SRC (Spreadtrum) enable 0 disable 1 enable
 // 3: AFC SRC (Samsung) enable 0 disable 1 enable
 // 2: FCP SRC (Huawei) enable 0 disable 1 enable
 // 1: QC3.0 SRC enable 0 disable 1 enable
 // 0: QC2.0 SRC enable 0 disable 1 enable
unsigned char IP5328P_DCP_DIG(void)
{
  unsigned char flag=0;
  flag=IP5328P_Read(0xA2);
  if(flag==0xff)return 0;
  return flag;
}
 
 /*----------------------------------------------Read Chip parameter function -end-------------------------------------------- ---------*/
 
 /************************************************* *Write chip parameter function******************************************** ************/
 
 //Set the battery low power shutdown voltage (you need to recharge after shutdown to start)
 //Input: 0x30 3.00V-3.10V
//      0x20 2.90V-3.00V
//      0x10 2.81V-2.89V
//      0x00 2.73V-2.81V
void IP5328P_BAT_LOW(unsigned char dat)
{
   if(dat==0x30||dat==0x20||dat==0x10||dat==0x00)//To ensure that the device is not error-free, write after confirming that the command is correct
  IP5328P_Write(0x10,dat);
}
 
 //Set SYS4
 //Input: chg2bst: unplug the charging and automatically turn on the boost output 0 not turn on 1 turn on
 // swclk2: enable I2C2 standby clock (read data in standby after enabling) 0 not open 1 open
 // swclk1: enable I2C1 standby clock (read data in standby after enabling) 0 not open 1 open
void IP5328P_SYS_CTL14(unsigned char chg2bst,unsigned char swclk2,unsigned char swclk1)
{
  unsigned char dat=0x00;
  if(chg2bst)dat|=0x40;
  if(swclk2)dat|=0x08;
  if(swclk1)dat|=0x04;
  IP5328P_Write(0x0E,dat);
}
 
 
 
 
 /*------------------------------------------------ Write chip parameter function -end------------------------------------------- ---------*/
 
 /*------------------------------------------------ ---Get common parameters-------------------------------------------- ---------------*/
 
 float power; //Total power
 Interface mos_state; //The open state structure of each interface
 Interface current; //Each interface current structure
 Interface voltage; //Each interface voltage structure
 
 //Get common parameters
 //Include: total power, voltage of each interface, current of each interface, open status of each interface
void read_Parameters(void)
{
  unsigned char mos,Sys_status,Bat_Grade,GHG_State,TypeC_VIN_voltage,boost; 
 /*----------------------------------------------Get parameters -------------------------------------------------- --------*/ 
   mos=IP5328P_MOS_ON(); //Get interface status
   power=IP5328P_Power(); //Get power
   TypeC_VIN_voltage=IP5328P_VinTypeC_State(); //Get Android port and TYPE-C voltage
   current.TypeC=IP5328P_TypeC_Current(); //Get Type-C current value
   current.VIN=IP5328P_VIN_Current(); //Get VIN current value
   current.OUT1=IP5328P_OUT1_Current(); //Get VOUT1 current value
  current.OUT2=IP5328P_OUT2_Current(); //Get VOUT2 current value
   boost=IP5328P_BOOST(); //Get boost value
 // Sys_status=IP5328P_SYS_Status(); //Get system status
 // Bat_Grade=IP5328P_Electricity(); //Get battery level
 // GHG_State=IP5328P_GHG_State(); //Get charging status
 /*--------------------------------------------Handle interface status- -------------------------------------------------- -----*/
   mos_state.OUT1=mos&0x01; //Get OUT1 on state [because when the button is pressed to activate, OUT1 will turn on the output, but it may not be connected]
   mos_state.OUT2=mos>>1&0x01; //Get OUT2 on state
   mos_state.TypeC=mos>>2&0x01; //Get TypeC open state
   mos_state.VIN=mos>>4&0x01; //Get VIN on state
   if(mos_state.OUT1) //correct the OUT1 on state [because when the button is activated, OUT1 will turn on the output, but it may not be connected]
  {
     if(power<=0.2)mos_state.OUT1=0; //If the power is 0, it is not connected
     if(power>0) //If power>0
       if(mos_state.OUT2||mos_state.TypeC||mos_state.VIN) //and there are other interfaces open
         if(current.OUT1==0)mos_state.OUT1=0; //If the OUT1 current is still 0, it proves that the OUT1 interface is not actually turned on
  }
 /*--------------------------------------------Processing interface voltage- -------------------------------------------------- -----*/
   if(mos_state.VIN){ //If the VIN interface is open
     switch(TypeC_VIN_voltage&0x07) //VIN voltage
    {
      case 0x07:voltage.VIN=12;break;                 //12V
      case 0x03:voltage.VIN=9;break;                  //9V
      case 0x01:voltage.VIN=7;break;                  //7V
      case 0x00:voltage.VIN=5;break;                  //5V
    }                                 
   }else voltage.VIN=0; //other
   if(mos_state.TypeC){ //If the TYPE-C interface is open
     switch(TypeC_VIN_voltage>>3&0x07) //TYPE-C voltage
    {
      case 0x07:voltage.TypeC=12;break;               //12V
      case 0x03:voltage.TypeC=9;break;                //9V
      case 0x01:voltage.TypeC=7;break;                //7V
      case 0x00:voltage.TypeC=5;break;                //5V
    }
   }else voltage.TypeC=0; //other
   if(mos_state.OUT1){ //If the interface is on
     if(current.OUT1)voltage.OUT1=5; //If the interface has current
     else{ //If the interface has no current
        if(boost>1&0x01)voltage.OUT1=5; //The voltage value is the boost value
        if(boost>2&0x01)voltage.OUT1=9; //The voltage value is the boost value
        if(boost>3&0x01)voltage.OUT1=12; //The voltage value is the boost value
    }                                 
   }else voltage.OUT1=0; //If the interface is not open
   if(mos_state.OUT2){ //If the interface is on
     if(current.OUT2)voltage.OUT2=5; //If the interface has current
     else{ //If the interface has no current
        if(boost>1&0x01)voltage.OUT2=5; //The voltage value is the boost value
        if(boost>2&0x01)voltage.OUT2=9; //The voltage value is the boost value
       if(boost>3&0x01)voltage.OUT2=12; //The voltage value is the boost value
    }                                 
   }else voltage.OUT2=0; //If the interface is not open
 /*--------------------------------------------Processing interface current- -------------------------------------------------- -----*/
   if(current.OUT1==0&&mos_state.OUT1)current.OUT1=power/voltage.OUT1; //If the current is 0, only one interface may be inserted, and the current needs to be converted by power
   if(current.OUT2==0&&mos_state.OUT2)current.OUT2=power/voltage.OUT2; //If the current is 0, only one interface may be inserted, and the current needs to be converted by power
   if(current.TypeC==0&&mos_state.TypeC)current.TypeC=power/voltage.TypeC; //If the current is 0, only one interface may be inserted, and the current needs to be converted by power
   if(current.VIN==0&&mos_state.VIN)current.VIN=power/voltage.VIN; //If the current is 0, only one interface may be inserted, and the current needs to be converted by power
 /*--------------------------------------------Process xxxx-- -------------------------------------------------- ----*/
 
}
 
 /*------------------------------------------------ ---Get common parameters-------------------------------------------- ---------------*/
 
 
 
 
 
 
 
 
 
 
 
