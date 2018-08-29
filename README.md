HapTouch BoosterPack Library
=============================================================================

This Energia library supports the [HapTouch BoosterPack][1].

<Add comments about being designed by Element 14, links to press release. Obtained a couple when Newark put them on a fire sale. Limited usefulness until now due to lack of availability of the TI HapTouch library ... link ...
Reverse engineered my own library based on available datasheets .... links.... and testing.
Note error in datasheet for some params/command IDs.
List commands and IDs, params and IDs, effects and IDs, error codes and IDs (where available).

Usage
-----
_See the sketch included in the `examples` folder._

Create an object and call begin method
- Note about how to deal with SetModule
- Other assumptions on operation
- How to use bit-bang SPI if desired (for example, my SWI2C library)

Usage Notes
---------------------------
Existing TCH5E code still running, so touching the cap-touch buttons will impact operation
Can use some undocumented commands to "disable" and re-enable the board (the audio commands might also do this).
Power issues LRA vs ERM
Should work with any MSP430. The smaller LaunchPads (like G2 or FR2433) make it difficult to use the LaunchPad buttons without accidentally hitting the captouch buttons on the BoosterPack, although you can use the 6-pin header ("Host Connector") and separate the BoosterPack from the LaunchPad. 



References
----------
+ HapTouch BoosterPack [reference design][1]
+ HapTouch BoosterPack [user guide][2]
+ Haptics Library [designer's guide][3]
+ HapTouch [SDK][4]. Note that the SDK is [no longer available][5].
+ 43oh Forum [discussion][6] on the BoosterPack.
+ Element14 product [announcement][8].
+ Element14 [product page and road test reviews][7].

[1]: http://www.ti.com/tool/TIDM-LPBP-HAPTOUCH
[2]: http://www.ti.com/lit/an/slaa616/slaa616.pdf
[3]: http://www.ti.com/lit/ug/slau543/slau543.pdf
[4]: http://www.ti.com/tool/MSP430-HAPTOUCH-SDK
[5]: https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/541078
[6]: https://forum.43oh.com/topic/4786-msp430tch5e-haptouch-is-available/
[7]: https://www.element14.com/community/roadTests/1268
[8]: https://www.element14.com/community/docs/DOC-65467/
