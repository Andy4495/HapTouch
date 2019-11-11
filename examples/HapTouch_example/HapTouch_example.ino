/* HapTouch Example Sketch

  Uses HapTouch library to interface with HapTouch BoosterPack.

  https://github.com/Andy4495/HapTouch

*/
/* Version History
   1.0.0    09/04/2018  A.T.   Original
*/

#include "HapTouch.h"

#if defined(__MSP430FR4133__)
#define BOARD_LED LED2
#endif

#if defined(__MSP430FR6989__)
#define BOARD_LED GREEN_LED
#endif

#if defined(__MSP430G2553__)
#define BOARD_LED GREEN_LED
#endif

#if defined(__MSP430F5529__)
#define BOARD_LED GREEN_LED
#endif

#if defined(__MSP430FR2433__)
#define BOARD_LED LED2
#endif

#if defined(__MSP430FR5969__)
#define BOARD_LED LED2
#endif

int LED_state = 0;

char readbackString[20];
uint8_t paramBuffer[20];

HapTouch myHapTouch;

void setup() {

  int rc;

  Serial.begin(9600);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(BOARD_LED, OUTPUT);

  Serial.println("HapTouch Example");

  // Initialize HapTouch
  myHapTouch.begin();

  // Get the PING readback string
  myHapTouch.readbackPing(readbackString);
  Serial.print("Readback PING string and length: ");
  Serial.print(readbackString);
  Serial.print(", ");
  Serial.println(strlen(readbackString));

  delay(1000);

  Serial.print("Press PUSH2 to start haptic sequence.");
}

void loop() {
  int rc;

  digitalWrite(RED_LED, LOW);

  paramBuffer[0] = 0x76; // Effect 1
  paramBuffer[1] = 0x14; // Gap length (5 ms increments)
  paramBuffer[2] = 0x2e; // Effect 2
  paramBuffer[3] = 0x28; // Gap
  paramBuffer[4] = 0x10; // Effect 3
  paramBuffer[5] = 0x3c; // Gap
  int effectCount = 3;
  int repeatCount = 3; // 0 = no repeats; sequence plays once

  if (digitalRead(PUSH2) == LOW) {
    digitalWrite(RED_LED, HIGH);
    rc = myHapTouch.playSequence(paramBuffer, effectCount, repeatCount, 0);  // Last param: Override: 0 = No, 1 = Yes
    Serial.print("Response code: 0x");
    if (rc < 16) Serial.print("0");
    Serial.println(rc, HEX);
  }

  delay(1000);
}
