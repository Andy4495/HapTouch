/* HapTouch.h

Library to interface with HapTouch BoosterPack.

https://github.com/Andy4495/HapTouch

*/
/* Version History
   1.0.0    08/30/2018  A.T.   Original
*/

#ifndef HAPTOUCH_H
#define HAPTOUCH_H

#include <Arduino.h>

#define DEFAULT_TCH5E_I2C_ADDR 0x10
#define DEFAULT_I2C_MODULE     0x00

class HapTouch {
public:
  HapTouch(uint8_t i2c_module  = DEFAULT_I2C_MODULE,
           uint8_t i2c_address = DEFAULT_TCH5E_I2C_ADDR);

  void begin();
  uint8_t playEffect(uint8_t effect, int duration, uint8_t override);
  uint8_t playSequence(uint8_t* effect_list, int effect_count, uint8_t repeat_count,
                       uint8_t override);
  uint8_t stopPlayback();
  void readbackPing(char* c);
  void readbackButtonState(char* c);
  void readbackButtonCounts(char* c);
  void readbackGeneric(uint8_t readback_index, char* c, uint8_t n);
  uint8_t audioHapticsEnable(uint8_t en);
  uint8_t audioHapticsConfig(uint8_t midpoint, uint8_t wakeupThreshold,
                             uint8_t inputMin, uint8_t inputMax,
                             uint8_t strengthAtFloor, uint8_t strengthMax);
  uint16_t enterGameState();
  uint8_t touchTune();
  uint8_t genericCommand(uint8_t command, uint8_t* params, uint8_t param_length);
  uint8_t getResponseCode();

  // HapTouch Library Documented commands
  enum {
    CMD_PLAY_EFFECT          = 0x54,
    CMD_PLAY_SEQ             = 0x50,
    CMD_STOP_PLAYBACK        = 0x52,
    CMD_READBACK             = 0x30,
    CMD_RESET                = 0x00, // Unknown; value not documented
    CMD_AUDIOHAPTICS_ENABLE  = 0x40,
    CMD_AUDIOHAPTICS_CONFIG  = 0x41,
    CMD_ENTER_GAME_STATE     = 0x55, // Documented in BoosterPack User Guide
    CMD_TOUCHTUNE            = 0x71  // Documented in BoosterPack User Guide
  };

  // HapTouch Library Readback Indices
  enum {
    RB_PING                  = 0x01,   // Designer's Guide documents as 0x00,
                                       // but Haptics Library uses 0x01
    RB_BUTTON_STATE          = 0x02,   // Documented in BoosterPack User Guide
                                       // This may only work while BoosterPack
                                       // is in GAME_STATE
    RB_BUTTON_COUNTS         = 0x03    // Documented in BoosterPack User Guide
                                       // This may only work while BoosterPack
                                       // is in GAME_STATE
  };

private:
  uint8_t _i2c_addr;
  uint8_t _i2c_module;

};

/*
HapTouch Library effect codes from Appendix A of Designer's Guide
Used with playEffect() and playSequence() commands

0x00 Strong Click – 100%
0x01 Strong Click – 60%
0x02 Strong Click – 30%
0x03 Sharp Click – 100%
0x04 Sharp Click – 60%
0x05 Sharp Click – 30%
0x06 Soft Bump – 100%
0x07 Soft Bump – 60%
0x08 Soft Bump – 30%
0x09 Double Click – 100%
0x0A Double Click – 60%
0x0B Triple Click – 100%
0x0C Soft Fuzz – 60%
0x0D Strong Buzz – 100%
0x0E Empty
0x0F Empty
0x10 Strong Click 1 – 100%
0x11 Strong Click 2 – 80%
0x12 Strong Click 3 – 60%
0x13 Sharp Click 4 – 30%
0x14 Medium Click 1 – 100%
0x15 Medium Click 2 – 80%
0x16 Medium Click 3 – 60%
0x17 Sharp Tick 1 – 100%
0x18 Sharp Tick 2 – 80%
0x19 Sharp Tick 3 – 60%
0x1A Short Double Click Strong 1 – 100%
0x1B Short Double Click Strong 2 – 80%
0x1C Short Double Click Strong 3 – 60%
0x1D Short Double Click Strong 4 – 30%
0x1E Short Double Click Medium 1 – 100%
0x1F Short Double Click Medium 2 – 80%
0x20 Short Double Click Medium 3 – 60%
0x21 Short Double Sharp Tick 1 – 100%
0x22 Short Double Sharp Tick 2 – 80%
0x23 Short Double Sharp Tick 3 – 60%
0x24 Long Double Sharp Click Strong 1 – 100%
0x25 Long Double Sharp Click Strong 2 – 60%
0x26 Long Double Sharp Click Strong 3 – 30%
0x27 Long Double Sharp Click Strong 4 – 100%
0x28 Long Double Sharp Click Medium 1 – 100%
0x29 Long Double Sharp Click Medium 2 – 80%
0x2A Long Double Sharp Click Medium 3 – 60%
0x2B Long Double Sharp Tick 1 – 100%
0x2C Long Double Sharp Tick 2 – 80%
0x2D Long Double Sharp Tick 3 – 60%
0x2E Buzz 1 – 100%
0x2F Buzz 2 – 80%
0x30 Buzz 3 – 60%
0x31 Buzz 4 – 40%
0x32 Buzz 5 – 20%
0x33 Pulsing Strong 1 – 100%
0x34 Pulsing Strong 2– 60%
0x35 Pulsing Medium 1 – 100%
0x36 Pulsing Medium 2 – 60%
0x37 Pulsing Sharp 1 – 100%
0x38 Pulsing Sharp 2– 60%
0x39 Transition Click 1 – 100%
0x3A Transition Click 2 – 80%
0x3B Transition Click 3 – 60%
0x3C Transition Click 4 – 40%
0x3D Transition Click 5 – 20%
0x3E Transition Click 6 – 10%
0x3F Transition Hum 1– 100%
0x40 Transition Hum 2 – 80%
0x41 Transition Hum 3 – 60%
0x42 Transition Hum 4 – 40%
0x43 Transition Hum 5 – 20%
0x44 Transition Hum 6 – 10%
0x45 Transition Ramp Down Long Smooth 1 – 100 to 0%
0x46 Transition Ramp Down Long Smooth 2 – 100 to 0%
0x47 Transition Ramp Down Medium Smooth 1 – 100 to 0%
0x48 Transition Ramp Down Medium Smooth 2 – 100 to 0%
0x49 Transition Ramp Down Short Smooth 1 – 100 to 0%
0x4A Transition Ramp Down Short Smooth 2 – 100 to 0%
0x4B Transition Ramp Down Long Sharp 1 – 100 to 0%
0x4C Transition Ramp Down Long Sharp 2 – 100 to 0%
0x4D Transition Ramp Down Medium Sharp 1 – 100 to 0%
0x4E Transition Ramp Down Medium Sharp 2 – 100 to 0%
0x4F Transition Ramp Down Short Sharp 1 – 100 to 0%
0x50 Transition Ramp Down Short Sharp 2 – 100 to 0%
0x51 Transition Ramp Up Long Smooth 1 – 0 to 100%
0x52 Transition Ramp Up Long Smooth 2 – 0 to 100%
0x53 Transition Ramp Up Medium Smooth 1 – 0 to 100%
0x54 Transition Ramp Up Medium Smooth 2 – 0 to 100%
0x55 Transition Ramp Up Short Smooth 1 – 0 to 100%
0x56 Transition Ramp Up Short Smooth 2 – 0 to 100%
0x57 Transition Ramp Up Long Sharp 1 – 0 to 100%
0x58 Transition Ramp Up Long Sharp 2 – 0 to 100%
0x59 Transition Ramp Up Medium Sharp 1 – 0 to 100%
0x5A Transition Ramp Up Medium Sharp 2 – 0 to 100%
0x5B Transition Ramp Up Short Sharp 1 – 0 to 100%
0x5C Transition Ramp Up Short Sharp 2 – 0 to 100%
0x5D Transition Ramp Down Long Smooth 1 – 50 to 0%
0x5E Transition Ramp Down Long Smooth 2 – 50 to 0%
0x5F Transition Ramp Down Medium Smooth 1 – 50 to 0%
0x60 Transition Ramp Down Medium Smooth 2 – 50 to 0%
0x61 Transition Ramp Down Short Smooth 1 – 50 to 0%
0x62 Transition Ramp Down Short Smooth 2 – 50 to 0%
0x63 Transition Ramp Down Long Sharp 1 – 50 to 0%
0x64 Transition Ramp Down Long Sharp 2 – 50 to 0%
0x65 Transition Ramp Down Medium Sharp 1 – 50 to 0%
0x66 Transition Ramp Down Medium Sharp 2 – 50 to 0%
0x67 Transition Ramp Down Short Sharp 1 – 50 to 0%
0x68 Transition Ramp Down Short Sharp 2 – 50 to 0%
0x69 Transition Ramp Up Long Smooth 1 – 0 to 50%
0x6A Transition Ramp Up Long Smooth 2 – 0 to 50%
0x6B Transition Ramp Up Medium Smooth 1 – 0 to 50%
0x6C Transition Ramp Up Medium Smooth 2 – 0 to 50%
0x6D Transition Ramp Up Short Smooth 1 – 0 to 50%
0x6E Transition Ramp Up Short Smooth 2 – 0 to 50%
0x6F Transition Ramp Up Long Sharp 1 – 0 to 50%
0x70 Transition Ramp Up Long Sharp 2 – 0 to 50%
0x71 Transition Ramp Up Medium Sharp 1 – 0 to 50%
0x72 Transition Ramp Up Medium Sharp 2 – 0 to 50%
0x73 Transition Ramp Up Short Sharp 1 – 0 to 50%
0x74 Transition Ramp Up Short Sharp 2 – 0 to 50%
0x75 Long buzz for programmatic stopping – 100%, 10 seconds max
0x76 Smooth Hum 1 (No kick or brake pulse) – 50%
0x77 Smooth Hum 2 (No kick or brake pulse) – 40%
0x78 Smooth Hum 3 (No kick or brake pulse) – 30%
0x79 Smooth Hum 4 (No kick or brake pulse) – 20%
0x7A Smooth Hum 5 (No kick or brake pulse) – 10%
0x7B Empty
0x7C Empty
0x7D Empty
0x7E Empty
0x7F Empty

*/

#endif
