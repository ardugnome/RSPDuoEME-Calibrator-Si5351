#include "si5351.h"
#include "Wire.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h> 

Si5351 si5351;

unsigned long long freq  = 14414950000ULL; // 211.600000MHz x 49 = 10368.4Mhz

void setup() {
//  si5351.set_correction(+900000, SI5351_PLL_INPUT_XO);
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);            
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_4MA);  
  si5351.set_freq(freq, SI5351_CLK0);                    
  delay(3000);
  si5351.output_enable(SI5351_CLK0, 0); // Disable the output
  delay(1000);
  i2c_switch_off();
  Manual_LowPower_Mode(1);   
 set_sleep_mode (SLEEP_MODE_PWR_DOWN);
 Deep_Sleep_Manual();
  
}

void loop() {
    

  // Power down the specific clock output using a register command
  // The command below sets the CLK0_PDN bit in the appropriate register
  // Consult the Si5351 datasheet or library source code for exact register/bit values
  // A common method with libraries is:

 
}
void i2c_switch_off(){

  // turn off I2C

  TWCR &= ~(bit(TWEN) | bit(TWIE) | bit(TWEA));


  // turn off I2C pull-ups

  digitalWrite (A4, LOW);

  digitalWrite (A5, LOW);

}
void Deep_Sleep_Manual(){

  // CORE State

  set_sleep_mode (SLEEP_MODE_PWR_DOWN);

  ADCSRA = 0;            // turn off ADC

  power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface


  // Interrupts are not counted as ADXL require

  noInterrupts ();       // timed sequence coming up

  sleep_enable ();       // ready to sleep

  interrupts ();         // interrupts are required now

  sleep_cpu ();          // sleep                

  sleep_disable ();      // precaution

  power_all_enable ();   // power everything back on

  

}  // end of goToSleep 

void Manual_LowPower_Mode(uint8_t multiplier){

  delay(70);                                              // Requires at least 68ms of buffer head time for module booting time

  for(int i = 0; i <= multiplier; i++){                   // Multiplier for Power Down Tick

    Deep_Sleep_Manual();

  }

}
