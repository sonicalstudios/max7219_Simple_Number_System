//************************************//
// Original script for Max7219 //
// re-written by Jeremy Atkinson From Sonical Studios //
// for basin number test //

// Inital Relations
#include "LedControl.h"

// Arduino Pin 7 to DIN, 6 to Clk, 5 to CS, no.of devices
LedControl max7219A = LedControl(7, 6, 5, 2);

// Initial Values
int number; // Would like to be able to call all others from this number
// Stiff working on that   :-)
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

  int devices = max7219A.getDeviceCount();

  for (int address = 0; address < devices; address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    max7219A.shutdown(address, false);
    /* Set the brightness to a medium values */
    max7219A.setIntensity(address, 8);
    /* and clear the display */
    max7219A.clearDisplay(address);
  }

}

// Runtime Loop
void loop() {

  maths();
  runMax7219();
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
void maths()
{

  if ((ones == 0) || (ones <= 11)) {
    ones++;
    //max7219A.setDigit( 0, 0, ones , false);

    if (ones == 10) {
      ones = 0;
      tens ++;

      if (tens == 10) {
        tens = 0;
        hundreds ++;

        if (hundreds == 10) {
          hundreds = 0;
          thousands ++;

          if (thousands == 10) {
            thousands = 0;
            tenThousands ++;

            if (tenThousands == 10) {
              tenThousands = 0;
              hundredThousands ++;

              if (hundredThousands == 10) {
                hundredThousands = 0;
                millions ++;

                if (millions == 10) {
                  millions = 0;

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
    //delay(100);
  }
}

void runMax7219()  {

  max7219A.setDigit( 0, 0, ones , false);
  max7219A.setDigit( 0, 1, tens , false);
  max7219A.setDigit( 0, 2, hundreds , false);
  max7219A.setDigit( 0, 3, thousands , false);
  max7219A.setDigit( 0, 4, tenThousands , false);
  max7219A.setDigit( 0, 5, hundredThousands , false);
  max7219A.setDigit( 0, 6, millions , false);

  max7219A.setDigit( 1, 0, ones / 2 , false);
  max7219A.setDigit( 1, 1, tens / 2 , false);
  max7219A.setDigit( 1, 2, hundreds / 2 , false);
  max7219A.setDigit( 1, 3, thousands / 2 , false);
  max7219A.setDigit( 1, 4, tenThousands / 2 , false);
  max7219A.setDigit( 1, 5, hundredThousands / 2 , false);
  max7219A.setDigit( 1, 6, millions / 2 , false);
}

