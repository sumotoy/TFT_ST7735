# TFT_ST7735
A fast driver for ST7735 displays that works with Arduino's and Teensy's<br>
...Oh no! Another ST7735 library?<br><br>
FAQ<br>
 - (q) It uses DMA SPI?
 - (r) No. It uses the fastest SPi alternative to keep compatibility if other devices sharing the same SPI lines.
 - (q) It's easy to convert my code to use this library?
 - (r) Yes. It use almost the same commands, only slight differences.
 - (q) It's faster than alternative libraries?
 - (r) Overall yes. Some library are optimized for one CPU and uses DMA that is faster but not so compatible if other SPI devices are sharing the same SPI lines.
 - (q) It's fully SPI transaction compatible.
 - (r) Yes. SPI transactions are great! You can have many devices works in harmony but be sure that other SPI devices library uses SPI transaction.
 - (q) What about graphic primitives, this one provide just basic stuff?
 - (r) No, the graphic primitives you can use are much more than adafruitGFX and faster.
 - (q) What about user font? Can I use alternative font?
 - (r) There's a basic support for external fonts that will be expanded in the 1.0 release and it's fast!
 - (q) IDE compatibility?
 - (r) It can work with IDE 1.0.6 but for Teensy 3 you will need 1.24 since it uses the last features.
 - (q) Compatibility with CPU?
 - (r) Any arduino 8bit, All Teensy's, Arduino DUE, ESP, etc.

Recently the price of the ST7735 has dropped a lot and in ebay you can find a lot of chinese displays for really cheap.
Unfortunatly the 95% of the libraries I found around are based on adafruit_ra8875 that for me it's actually a mess since bugs are rarely fixed and almost never recoded in a better version. Another problem are the user patches, sometime accepted without verification and the adafruit:gfx that was a great idea some years ago but currently (with a lot of 32 bit cpu) it's quite useless and again outdated and rarely upgraded.<br>
So I have coded this one, most of the work it's from my other library ILI9163C library (the 1.0 preview actually) that it's really fast.<br>
It's faster than Adafruit, even a bit faster than the Paul Stoffregen version and has much more features included full SPI transaction support (where applicable) and a new and never appeared support for an undocumented scroll feature of this chip that I discovered by incident.<br>
This is a working preview, it was really never tested fully but if you notice any bug please open an issue and inform me, I will really appreciate the help.

