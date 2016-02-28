# TFT_ST7735
A fast driver for ST7735 displays that works with Arduino's and Teensy's<br>
...Oh no! Another ST7735 library?<br><br>
Look for a better version? Click here https://github.com/sumotoy/TFT_ST7735/tree/1.1b1<br><br>

I'm actually using this library as playground for all my TFT libraries so I will transfer features when ready.<br>
The goals are:<br>
- Very Fast but using compatible-with-other-devices SPI. I like to use it with other devices sharing the same SPI line!<br>
- Complete set of graphic primitives.<br>
- An unreleased and solid font rendering engine that can use 'rle compressed' fonts and 'big' fonts! It also work with variable width fonts (and not like some library that use only fixed size fonts).<br>
- Should work with many CPU.<br>
- Use all features of the display, included idle, sleep.<br>
- Can work with any orientation.<br>
- Precise center align of text phrases (useful for interfaces).<br>
- Full SPI Transaction compatible (where supported).<br>
- 30Mhz or more SPI capable.<br>
- Use just 4 wires (all outputs)<br>
- Separate User settings file let you add different displays without impact resource usage.<br>
- Commands are very similar to Adafruit libraries so easy to migrate.

The current beta it's a working preview, the rle decompressor it's included but I'm still working on it so the included fonts are not compressed. The internal font it's quite large, has full set ASCII and much better than one from Adafruit, fonts was created with a modified program that I will release as soon the author give me the authorization, in the meantime if you have free font you want to include please let me know and send, I can convert ttf or standard character but NOT bitmaps or image fonts, I need to enlarge to do a good conversion.<br>
Of course there's bugs! Actually it uses a lot of RAM resources so using with poor RAM CPU can be a problem but this it's on the top of my to-do list and will be solved.<br>
The text rendering engine can use RLE-Encoded fonts and next version can decode 2-byte languages as well, it's using custom encoded fonts so do not ask to use other library fonts, it has 2 nice features like font scaling (with any font) and next version can paint chars by using graphic primitives for create big text efx, etc. Another nice feature it's an autocenter option I have introduced in RA8875 library that can precisely center text on x,y address, for example:<br>
 - setCursor(50,50);      -> |ABCD (autocenter off)
 - setCursor(50,50,true): -> AB|CD (autocenter on)

With autocenter the text will be aligned on Y axis as well!<br>

This is really useful when design interfaces!<br>
The drawArc can use thickness to draw nice looking volume style knobs, I have added drawPolygon, drawMesh and drawQuad that it's unvaluable for 3D solid rendering (example included).<br>
Any suggestion or bug report it's higly appreciated!<br>

