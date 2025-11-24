//The calibrator is based upon the Analogue Devices ADF 4351 Wideband Synthesizer and the Arduino project by F1CJN. 
//The RSPduoEME software has been written by G4EEV
// Conversion to use the Si5351 Module by NJ9R

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <SPI.h>
#include <SI5351.h>

#define ADF4351_LE 3  // This can be removed; it's not used with SI5351

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
SI5351 si5351;

byte poscursor = 0; // Current cursor position, 0 to 15
byte line = 0; // Current LCD line, 0 or 1
byte memoire, WEE = 0; // EEPROM memory number

uint32_t RFint; // Set frequency variable
double RFoutMin = 35, RFoutMax = 4400;

// Define button values
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void setup() {
  lcd.begin(16, 2); // Initialize a 16x2 LCD
  lcd.display();
  analogWrite(10, 64); // LCD brightness

  Serial.begin(9600);  // Serial to the PC
  Serial.setTimeout(250);
  lcd.print("   GENERATEUR   ");
  lcd.setCursor(0, 1);
  lcd.print("     SI5351     ");
  delay(1000);

  si5351.init();  // Initialize SI5351

  // Load frequency from EEPROM
  if (EEPROM.read(100) == 55) {
    RFint = EEPROM.read(20 * 4); // Load saved frequency if it exists
  } else {
    RFint = 7000; // Default frequency
  }

  printAll();  // Display the initial frequency
}

void loop() {
  if (RFint > RFoutMax) RFint = RFoutMax;
  
  if (RFint < RFoutMin) RFint = RFoutMin;

  // Set the SI5351 frequency
  si5351.set_freq(RFint * 10000, SI5351_CLK0); // Set frequency in Hz

  // Read button inputs
  static int lcd_key = read_LCD_buttons(); 

  switch (lcd_key) {
    case btnRIGHT:
      poscursor++;
      if (line == 0) {
        if (poscursor == 9 || poscursor == 12) {
          poscursor = 0; line = 1;  // Wrap around cursor
        }
      }
      lcd.setCursor(poscursor, line);
      break;

    case btnLEFT:
      poscursor--;
      if (line == 1 && poscursor < 4) {
        poscursor = 15; line = 0; // Wrap around cursor
      }
      lcd.setCursor(poscursor, line);
      break;

    case btnUP:
      // Adjust frequency
      if (line == 0) {
        if (poscursor == 5) RFint += 100000; // Increase by 100 kHz
        if (RFint > RFoutMax) RFint = RFoutMax; // Limit frequency
      }
      printAll();
      break;

    case btnDOWN:
      // Adjust frequency
      if (line == 0) {
        if (poscursor == 5) RFint -= 100000; // Decrease by 100 kHz
        if (RFint < RFoutMin) RFint = RFoutMin; // Limit frequency
      }
      printAll();
      break;

    case btnSELECT:
      // Memory storage functionality
      if (WEE == 1 || poscursor == 15) {
        EEPROMWritelong(memoire * 4, RFint); // Save frequency
        EEPROM.write(101, 55); // Acknowledge save
        lcd.setCursor(0, 1);
        lcd.print("  MEMORIZED     ");
      }
      delay(500);
      printAll();
      break;

    case btnNONE:
      break;
  }

  // Release button debounce
  do { 
    adc_key_in = analogRead(0); 
    delay(1); 
  } while (adc_key_in < 900); 
  delay(10);
}

void printAll() {
  lcd.setCursor(0, 0);
  lcd.print("RF = ");
  lcd.print(RFint / 100);
  lcd.print(".");
  lcd.print(RFint % 100);
  lcd.print(" MHz");
  lcd.set

