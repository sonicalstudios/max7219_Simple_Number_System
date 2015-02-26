//************************************//
// Original script for Max7219 //
// re-written by Jeremy Atkinson From Sonical Studios //
// for basin number test //

// Inital Relations 
#include "LedControl.h"

// Arduino Pin 7 to DIN, 6 to Clk, 5 to CS, no.of devices
LedControl max7219A = LedControl(7, 6, 5, 1);
LedControl max7219B = LedControl(11, 10, 9, 1);

// Initial Values
int ones = 0;
int tens = 0;
int hundreds = 0;
int thousands = 0;
int tenThousands = 0;
int hundredThousands = 0;
int millions = 0;

// Setup
void setup()
{
  Serial.begin(9600);

  // Initialize the MAX7219 device
  max7219A.shutdown(0, false);  // Enable display
  max7219A.setIntensity(0, 15);  // Set brightness level (0 is min, 15 is max)
  max7219A.clearDisplay(0); // Clear display register

}

// Runtime Loop
void loop() {

  runTimer();
}

// Extra Commands

void resetAll()  // Reset all to 0
{
  ones = 0;
  tens = 0;
  hundreds = 0;
  thousands = 0;
  tenThousands = 0;
  hundredThousands = 0;
  millions = 0;
}

// Run timer till 10 Million
void runTimer()
{

  for (ones = 0; ones <= 11; ones++) {

    if ((ones >= 0) && (ones <= 10))
    {
      max7219A.setDigit( 0, 0, ones , false);
    }

    if (ones == 10) {
      ones = 0;
      tens ++;
      max7219A.setDigit( 0, 0, 0 , false);
      max7219A.setDigit( 0, 1, tens , false);

      if (tens == 10) {
        tens = 0;
        hundreds ++;
        max7219A.setDigit( 0, 1, 0 , false);
        max7219A.setDigit( 0, 2, hundreds , false);

        if (hundreds == 10) {
          hundreds = 0;
          thousands ++;
          max7219A.setDigit( 0, 2, 0 , false);
          max7219A.setDigit( 0, 3, thousands , false);

          if (thousands == 10) {
            thousands = 0;
            tenThousands ++;
            max7219A.setDigit( 0, 3, 0 , false);
            max7219A.setDigit( 0, 4, tenThousands , false);

            if (tenThousands == 10) {
              tenThousands = 0;
              hundredThousands ++;
              max7219A.setDigit( 0, 4, 0 , false);
              max7219A.setDigit( 0, 5, hundredThousands , false);

              if (hundredThousands == 10) {
                hundredThousands = 0;
                millions ++;
                max7219A.setDigit( 0, 4, 0 , false);
                max7219A.setDigit( 0, 5, millions , false);

                if (millions == 10) {
                  millions = 0;
                  max7219A.setDigit( 0, 4, 0 , false);
                  max7219A.setDigit( 0, 5, millions , false);
                  resetAll();
                }
              }
            }
          }
        }
      }
    }
    Serial.print(millions);
    Serial.print(",");
    Serial.print(hundredThousands);
    Serial.print(tenThousands);
    Serial.print(thousands);
    Serial.print(",");
    Serial.print(hundreds);
    Serial.print(tens);
    Serial.println(ones);
    //delay(100);      // Setting to change in needed
  }
}

