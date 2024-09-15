#ifndef  __IP5328P_H__
#define  __IP5328P_H__
 
 
 extern float power; //Total power
 
typedef struct{
   unsigned char OUT1; //OUT1 interface
   unsigned char OUT2; //OUT2 interface
   unsigned char TypeC; //TypeC interface
   unsigned char VIN; //VIN (Android port)
}Interface;
 
 extern Interface mos_state; //The open state structure of each interface
 extern Interface current; //Each interface current structure
 extern Interface voltage; //Each interface voltage structure
 
 
 
 
 //Basic operation function
 void IP5328P_Write(unsigned char reg,unsigned char data); //Write IP5328P register data
 unsigned char IP5328P_Read(unsigned char reg); //Read IP5328P register data
 
 //Function function
 /**************************************Read parameters********* ************************************************** ******/
 float IP5328P_BatVoltage(void); //Read the voltage value at both ends of the battery
 float IP5328P_BatOCV(void); //The battery voltage is compensated by the internal resistance of the cell and the cell current
 float IP5328P_BatCurrent(void); //Read battery current
 float IP5328P_TypeC_Current(void); //Read TYPE-C input and output current
 float IP5328P_VIN_Current(void); //Read the input current of the Android port
 float IP5328P_OUT1_Current(void); //Read OUT1 output current
 float IP5328P_OUT2_Current(void); //Read OUT2 output current
 float IP5328P_Power(void); //Get power
 unsigned char IP5328P_TypeC_Flag(void); //Get Type-C interface connection status
unsigned char IP5328P_TypeC_Ability(void); //Get the output capacity of the adapter connected to Type-C
 unsigned char IP5328P_Electricity(void); //Get power indicator level
 unsigned char IP5328P_SYS_Status(void); //Get power status
 unsigned char IP5328P_VinTypeC_State(void); //Get the input voltage of Android port and TYPE-C
 unsigned char IP5328P_GHG_State(void); //Get charging status
 unsigned char IP5328P_MOS_ON(void); //Get MOS on status
 unsigned char IP5328P_BOOST(void); //Get the boost output voltage range
 unsigned char IP5328P_QC_State(void); //Get whether QC fast charge is enabled (not whether it is being used, but whether this function is available)
 unsigned char IP5328P_DCP_DIG(void); //Get whether fast charging is enabled (not whether it is being used, but whether this function is available)
 
 /**************************************Write parameters********* ************************************************** ******/
 void IP5328P_BAT_LOW(unsigned char dat); //Set the battery low power shutdown voltage
 void IP5328P_SYS_CTL14(unsigned char chg2bst,unsigned char swclk2,unsigned char swclk1);//Set SYS4
 
 /***********************************Get common parameters ********** ************************************************** **/
void read_Parameters(void);                              
 
#endif
 
 
 
 
 
 
