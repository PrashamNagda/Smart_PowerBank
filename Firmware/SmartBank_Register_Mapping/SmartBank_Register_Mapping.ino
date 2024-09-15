#include "ip5328p.h"
#include "i2c.h"
 
void main(void)
{
    i2c_init();
    while(1)
    {
        read_Parameters(); //Get parameters
 
 /*-----------------------------------Get battery voltage and current--------- -------------------------*/
   Serial.println("BAT:%1.2fV %1.2fA", IP5328P_BatVoltage(),IP5328P_BatCurrent()); //The voltage and current at both ends of the battery
 /*-----------------------------------Interface status----------- ---------------------------*/   
  Serial.println("  %1d      %1d        %1d      %1d  ",mos_state.OUT2,mos_state.TypeC,mos_state.VIN,mos_state.OUT1);   
 /*-----------------------------------Get interface voltage---------- ------------------------*/
  Serial.println(" %2dV    %2dV      %2dV    %2dV",voltage.OUT2,voltage.TypeC,voltage.VIN,voltage.OUT1);
 /*-----------------------------------Get battery voltage and current--------- -------------------------*/
  Serial.println(" %1.2fA  %1.2fA    %1.2fA  %1.2fA",current.OUT2,current.TypeC,current.VIN,current.OUT1);
 /*-----------------------------------Get power supply---------- ------------------------*/
  Serial.println("Power:%2.1fW   ",power);
      
  delay(100);
    }
}
