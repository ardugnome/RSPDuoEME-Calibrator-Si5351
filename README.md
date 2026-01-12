# RSPDuoEME-Calibrator-Si5351
Original RSPduoEME software calibrator for the SDR Play RSPDuo by Dave Warwick G4EEV (https://www.qsl.net/g4eev/calibrator.html), calls for ADF 4351 Wideband Synthesizer by F1CJN (http://f6kbf.free.fr/html/ADF4351%20and%20Arduino_Fr_Gb.htm). 
This sketch provides for use of Skyworks Si5351 I2C programmable CMOS clock generator. Here is the Skyworks description:
"The Si5351 is an I2C configurable clock generator that is ideally suited for replacing crystals, crystal oscillators, VCXOs, phase-locked loops (PLLs), and fanout buffers in cost-sensitive applications. Based on a PLL/VCXO + high resolution MultiSynth fractional divider architecture, the Si5351 can generate any frequency up to 200 MHz on each of its outputs with 0 ppm error."

Items user needs to ensure are correct:

  #1 Checking and adjusting the frequency error using the Si5351 libraries and input the crystal correction data in the sketch on this line  #define SI5351_REF 25002650UL
	
  #2 Connect Si5351 to the 5V Arduino using the following pinout SDA-A4 and SCL-A5, GND and +5v
	
  #3 Connect the Clk 0 output of the Si5351 module to the RSPDuo through a capacitor.
	
  #4 In the RSPduoEME choose the serial port associated with the Arduino connected to the Si5351 module and check "Auto Calibration"
	
The RSPduoEME program outputs the frequency which is processed by the Arduino. The Si5351 module is turned on and the correct tuning frequency is generated for five (5) seconds after which the Arduino turns off the Si5351 module.
In that time, you need to click on the "Set" button of the software so that the staring phase between the two receivers is aligned properly.
Assumptions:
RSPDuoEME-Calibrator-Si5351 is turned on every time there is a need for calibration of the SDR Play unit, which is essentially every time you start it.
More information here: https://www.qsl.net/g4eev/index.html

Nov 2025, Relu Jianu NJ9R
