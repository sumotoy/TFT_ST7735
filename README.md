# TFT_ST7735
A fast driver for ST7735 displays that works with Arduino's and Teensy's
...Oh no! Another ST7735 library!?

Recently the price of the ST7735 has dropped a lot and in ebay you can find a lot of chinese displays for really cheap.
Unfortunatly the 95% of the libraries I found around are based on adafruit_ra8875 that for me it's actually a mess since bugs are rarely fixed and almost never recoded in a better version. Another problem are the user patches, sometime accepted without verification and the adafruit:gfx that was a great idea some years ago but currently (with a lot of 32 bit cpu) it's quite useless and again outdated and rarely upgraded.
So I have coded this one, most of the work it's from my other library ILI9163C library (the 1.0 preview actually) that it's really fast.
It's faster than Adafruit, even a bit faster than the Paul Stoffregen version and has much more features included full SPI transaction support (where applicable) and a new and never appeared support for an undocumented scroll feature of this chip that I discovered by incident.

