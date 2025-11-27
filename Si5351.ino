/*
Calibration routine for RSPDuoEME using Si5351 and Arduino (Nano) 
Connections SDA-A4 SCL-A5
Choose COM port in the RSPDuoEME and choose Auto Claibration
Hit Start and wait 5 seconds, if necessary repeat and click Set
Si5351 shuts down after 5 seconds
Nov 2025
*/

#include "si5351.h"
#include "Wire.h"
#define SI5351_REF 25002650UL

Si5351 si5351;

unsigned long long freq  = 14414500000ULL; 

void setup() {
  Serial.begin(9600);
si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_2MA); 
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, SI5351_REF, 0);          
}

void loop() {
    if (Serial.available()) {
  unsigned long input=Serial.parseInt();  // Read until newline
 freq = input*1000;
     freq=freq*100;
     si5351.set_freq(freq, SI5351_CLK0);     
  si5351.output_enable(SI5351_CLK0, 1);           
  delay(5000);
  si5351.output_enable(SI5351_CLK0, 0); // Disable the output
  //delay(1000);

    input = "";
    freq="";

  }
 
}
