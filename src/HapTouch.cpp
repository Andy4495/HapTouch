/* HapTouch.h

Library to interface with HapTouch BoosterPack.

https://gitlab.com/Andy4495/HapTouch

*/
/* Version History
   1.0.0    08/30/2018  A.T.   Original
*/
#include "HapTouch.h"
#include <Wire.h>

// Constructor
// Default arguments are typically correct when connecting the LaunchPad
// to the HapTouch BoosterPack using the standard LauncPad 20/40 pin
// headers. In that case, just call the constructor with no arguments.
HapTouch::HapTouch(uint8_t i2c_module,
                   uint8_t i2c_address)
{
  _i2c_addr = i2c_address;
  _i2c_module = i2c_module;
}

// Begin()
// Sets up the I2C bus. This call is optional, in which case sketch
// must manually setup I2C. For example, when you have multiple devices
// on I2C bus and don't want different devices calling Wire.begin().
void HapTouch::begin()
{
  Wire.setModule(0);        // G2 need to use I2C on pins 14/15
  Wire.begin();             // join i2c bus (address optional for master)
}

// playEffect()
// See section 6.2.1 in Haptics Library Designer's Guide (slau543)
uint8_t HapTouch::playEffect(uint8_t effect, int duration, uint8_t override)
{
  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(CMD_PLAY_EFFECT);     // Command opcode
  Wire.write(effect);
  Wire.write(duration & 0xff);     // LSB
  Wire.write(duration >> 8);       // MSB
  Wire.write(override);            // Override: 0 = abort if previous effect still playing
  Wire.endTransmission(true);

  return getResponseCode();
}

// playSequence()
// See section 6.2.2 in Haptics Library Designer's Guide (slau543)
uint8_t HapTouch::playSequence(uint8_t* effect_list, int effect_count, uint8_t repeat_count, uint8_t override)
{
  int i;

  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(CMD_PLAY_SEQ);              // Command opcode
  for (i = 0; i < effect_count; i++) {
    Wire.write(effect_list[i * 2]);      // Effect
    Wire.write(effect_list[i * 2 + 1]);  // Gap
  }
  Wire.write(0xFF);                      // End Signature
  Wire.write(repeat_count);
  Wire.write(override);                  // Override: 0 = abort if previous effect still playing
  Wire.endTransmission(true);

  return getResponseCode();
}

// stopPlayback
// See section 6.2.3 in Haptics Library Designer's Guide (slau543)
uint8_t HapTouch::stopPlayback() {

  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(CMD_STOP_PLAYBACK);        // Command opcode
  // No parameters
  Wire.endTransmission(true);

  return getResponseCode();
}

// readbackGeneric()
// See section 6.2.4 in Haptics Library Designer's Guide (slau543)
// Note that the Haptics Library only defines one readback index (PING),
// so you would generally use the readbackPing() method
void HapTouch::readbackGeneric(uint8_t readback_index, char* c, uint8_t n)
{
  int i;

  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(CMD_READBACK);           // Command opcode
  Wire.write(readback_index);
  Wire.endTransmission(true);

  Wire.requestFrom(I2C_SLAVE_ADDR_OF_TCH5E, n);  // Get the Response
  i = 0;
  while (Wire.available() && i < n) {
    c[i++] = Wire.read();
  }
  c[i] = '\0';            // Add NULL terminator
}

// readbackPing
// See section 6.2.4 in Haptics Library Designer's Guide (slau543)
// This directly implements the PING readback index
void HapTouch::readbackPing(char* c) {
  // RB_PING is the only readback index defined in designer's guide
  readbackGeneric(RB_PING, c, 12);  // 10 characters plus 2 dummy bytes
}

// readbackButtonState
// See section 8.3 of BoosterPack User Guide (slaa616)
void readbackButtonState(char* c)
{
  readbackGeneric(RB_PING, c, 10);  // 8 data bytes plus 2 dummy bytes
}

// readbackButtonCounts
// See section 8.3 of BoosterPack User Guide (slaa616)
void readbackButtonCounts(char* c)
{
  readbackGeneric(RB_PING, c, 10);  // 8 data bytes plus 2 dummy bytes
}

// audioHapticsEnable()
// See section 6.2.5 in Haptics Library Designer's Guide (slau543)
uint8_t HapTouch::audioHapticsEnable(uint8_t en)
{
  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(CMD_AUDIOHAPTICS_ENABLE);   // Command opcode
  Wire.write(en);                        // 0: Disable, non-zero: Enable
  Wire.endTransmission(true);

  return getResponseCode();
}

// audioHapticsEnable()
// See section 6.2.6 in Haptics Library Designer's Guide (slau543)
uint8_t HapTouch::audioHapticsConfig(uint8_t midpoint, uint8_t wakeupThreshold,
                           uint8_t inputMin, uint8_t inputMax,
                           uint8_t strengthAtFloor, uint8_t strengthMax)
{
  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(CMD_AUDIOHAPTICS_CONFIG);  // Command opcode
  Wire.write(midpoint);
  Wire.write(wakeupThreshold);    // Must be between 0 and (255 - midpoint)
  Wire.write(inputMin);           // Must be between 0 and (255 - midpoint)
  Wire.write(inputMax);           // Must be between 0 and (255 - midpoint)
  Wire.write(strengthAtFloor);
  Wire.write(strengthMax);
  Wire.endTransmission(true);

  return getResponseCode();
}

// enterGameState()
// See section 8.3 of BoosterPack User Guide (slaa616)
// Note that enterGameState returns 2 bytes instead of the usual 1 byte
uint16_t HapTouch::enterGameState()
{
  uint8_t rc[2];
  int i == 0;
  char c;

  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(CMD_ENTER_GAME_STATE);  // Command opcode
  Wire.write(midpoint);

  Wire.requestFrom(I2C_SLAVE_ADDR_OF_TCH5E, 2);  // Get the Response Code
  while (Wire.available() && i < 2) {
    c = Wire.read();
    if (c != 0x0c) { // If we get WAIT_FOR_RESPONSE, then try again
      rc[i] = c;
      i++;
    }
  }
  // Return code:
  // MSB is PlayerOneOrTwo
  // LSB is Response code
  return (rc[1] << 8) | rc[0];
}

// touchTune()
// See section 8.3 of BoosterPack User Guide (slaa616)
uint8_t HapTouch::touchTune()
{
    Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
    Wire.write(CMD_TOUCHTUNE);        // Command opcode
    // No parameters
    Wire.endTransmission(true);

    return getResponseCode();
}

// genericCommand()
// See section 6.2.1 in Haptics Library Designer's Guide (slau543)
// Implements a generic I2C message. Use this method to access
// undocumented HapTouch controller commands.
uint8_t HapTouch::genericCommand(uint8_t command, uint8_t* params,
                                 uint8_t param_length)
{
  uint8_t i = 0;

  Wire.beginTransmission(I2C_SLAVE_ADDR_OF_TCH5E);
  Wire.write(command);                // Command ID
  while (i < param_length) {
    Wire.write(params[i++]);   // Write out the parameters
  }
  Wire.endTransmission(true);

  return getResponseCode();
}

// getResponseCode()
// Used by the other command methods to retrieve the HapTouch controller
// response code after sending a command.
// This method would generally not be used in most sketches
uint8_t HapTouch::getResponseCode() {
  uint8_t c;
  Wire.requestFrom(I2C_SLAVE_ADDR_OF_TCH5E, 1);  // Get the Response Code
  while (Wire.available()) {
    c = Wire.read();
    if (c != 0x0c) return (uint8_t) c;    // If we get WAIT_FOR_RESPONSE, then try again
  }
}
