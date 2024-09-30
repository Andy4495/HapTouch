# HapTouch BoosterPack Library

[![Arduino Compile Sketches](https://github.com/Andy4495/HapTouch/actions/workflows/arduino-compile-sketches.yml/badge.svg)](https://github.com/Andy4495/HapTouch/actions/workflows/arduino-compile-sketches.yml)
[![Check Markdown Links](https://github.com/Andy4495/HapTouch/actions/workflows/check-links.yml/badge.svg)](https://github.com/Andy4495/HapTouch/actions/workflows/check-links.yml)

This library provides an I2C command interface to the [HapTouch BoosterPack][1].

The HapTouch BoosterPack was produced and available through Element14/Newark/Farnell based on a reference design from Texas Instruments.

The HapTouch BoosterPacks are no longer supported. An [SDK][4] contained details on how to program the TCH5E controller on the BoosterPack and also how to interface with the factory-programmed code on the TCH5E controller with I2C. However, the SDK is [no longer available][5].

This library provides an I2C interface to the BoosterPack based on still-available documentation and experimenting with the BoosterPack.

## Usage

_See the sketch included in the `examples` folder._

First, **create a HapTouch object**:

```cpp
HapTouch myHapTouch;
```

Note that the above constructor has two default parameters: the I2C address of the HapTouch BoosterPack and the I2C module number for the Wire library. The default values are typically the correct values, so the constructor can be called without arguments, but the ability to change those values is available if needed.

Next, **initialize the interface**:

```cpp
myHapTouch.begin();
```

This intitializes the I2C interface. It calls Wire.setModule() and Wire.begin(). If you want to initialize I2C separately in your sketch, the above method does not need to be called.

Then, call any of the **HapTouch commands** as needed for your sketch. These commands are explained in the HapTouch library [designer's guide][3] and in the BoosterPack [user's guide][2]:

```cpp
uint8_t playEffect(uint8_t effect, int duration, uint8_t override);
uint8_t playSequence(uint8_t* effect_list, int effect_count,
                     uint8_t repeat_count, uint8_t override);
uint8_t stopPlayback();
void readbackPing(char* c);
void readbackButtonState(char* c);
void readbackButtonCounts(char* c);
uint8_t audioHapticsEnable(uint8_t en);
uint8_t audioHapticsConfig(uint8_t midpoint, uint8_t wakeupThreshold,
                           uint8_t inputMin, uint8_t inputMax,
                           uint8_t strengthAtFloor, uint8_t strengthMax);
uint16_t enterGameState();
uint8_t touchTune();
```

The following commands are available for experimentation or to access undocumented commands:

```cpp
void readbackGeneric(uint8_t readback_index, char* c, uint8_t n);
uint8_t genericCommand(uint8_t command, uint8_t* params,
                       uint8_t param_length);
uint8_t getResponseCode();
```

## Operational Notes

- The HapTouch BoosterPack uses pins 14/15 for the I2C interface. These pins are typically defined as module 0 in the MSP board packages. The default HapTouch constructor sets I2C module 0.
- Since the factory-programmed firmware is still running on the TCH5E controller on the BoosterPack, touching the cap-touch buttons will generate the factory-programmed haptic response. However, it is possible to disable the CapTouch buttons by scraping away some solder resist on the buttons and the surrounding ground plane and creating a solder bridge between the buttons and ground.
- Some LaunchPads may not be able to supply enough power for the ERM haptic actuator. A symptom of this is the board resetting whenever a haptic effect is played. Therefore, it is recommended to set the BoosterPack switch to LRA mode when using LaunchPad power. When using the ERM actuator, use an external 3V3 power source that can supply at least 200 mA.
- This library should work with any of the MSP430 LaunchPad variants. The form factors of the smaller boards (like the G2) make it difficult to use the LaunchPad buttons without affecting the CapTouch buttons on the BoosterPack. In those cases, it is recommended to disable the CapTouch buttons as mentioned above.
- The BoosterPack includes a 2x3 "Host Connector" with power and I2C signals which can be used to interface with the board instead of using the standard BoosterPack 20/40 pin connector.

## Future Enhancements

- Currently, this library requires the use of the Wire library. A future iteration may include support for a software I2C library (like this [one][9])

## References

- HapTouch BoosterPack [product page][1] via Farnell
- HapTouch BoosterPack [user guide][2]
- Haptics Library [designer's guide][3]
- HapTouch [SDK][4]. Note that the SDK is [no longer available][5].
- 43oh Forum [discussion][6] ([archived copy][8]) on the BoosterPack.
- Element14 [product page and road test reviews][7].

## License

The software and other files in this repository are released under what is commonly called the [MIT License][100]. See the file [`LICENSE`][101] in this repository.

[1]: https://il.farnell.com/element14/boostxl-haptouch/haptics-boosterpack-for-launchpad/dp/2362893
[2]: https://community.element14.com/products/devtools/technicallibrary/m/files/17054
[3]: http://www.ti.com/lit/ug/slau543/slau543.pdf
[4]: http://www.ti.com/tool/MSP430-HAPTOUCH-SDK
[5]: https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/541078
[6]: https://forum.43oh.com/topic/4786-msp430tch5e-haptouch-is-available/
[7]: https://community.element14.com/products/roadtest/rt/roadtests/396/ti_haptics_enabled_g#pifragment-4100=4&pifragment-4106=7
[8]: ./extras/43oh-MSP430TCH5E-HAPTOUCH.pdf
[9]: https://github.com/Andy4495/SWI2C
[100]: https://choosealicense.com/licenses/mit/
[101]: ./LICENSE
[//]: # ([200]: https://github.com/Andy4495/HapTouch)

[//]: # (Dead link from previous version of README: Element14 Product Announcement https://www.element14.com/community/docs/DOC-65467/)
[//]: # ( Old [2] URL: http://www.ti.com/lit/an/slaa616/slaa616.pdf )
[//]: # ([1]: http://www.ti.com/tool/TIDM-LPBP-HAPTOUCH)
