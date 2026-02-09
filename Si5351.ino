/*
Calibration routine for RSPDuoEME using Si5351 and Arduino (Nano) 
Connections SDA-A4 SCL-A5
Choose corresponding Arduino COM port in the RSPDuoEME menu and tick "Auto Calibration" box.
Hit Start and wait 5 seconds, if necessary repeat above and click "Set"
Si5351 shuts down after 5 seconds
Nov 2025
*/

#include "si5351.h"
#include "Wire.h"
#include "avr/wdt.h"
#define SI5351_REF 25002650UL
Si5351 si5351;
unsigned long long freq  = 0ULL; 
unsigned long input = 0UL;
unsigned long bytesRead = 0;


void setup() {
si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_2MA); 
si5351.init(SI5351_CRYSTAL_LOAD_8PF, SI5351_REF, 0);        
Serial.begin(9600,SERIAL_8N2);
}

void loop() {
    if (Serial.available()) {
         Serial.flush();
         input=Serial.parseInt(); 
         freq=bytesRead*1000;
         freq = input*1000;
         freq = freq*100;
         
  si5351.set_freq(freq, SI5351_CLK0);     
  si5351.output_enable(SI5351_CLK0, 1);        
  delay(5000);
  si5351.output_enable(SI5351_CLK0, 0); // Disable the output
    }
}

 
