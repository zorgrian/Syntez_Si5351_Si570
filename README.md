# Universal Digital VFO Si570/Si5351

Oscillator: You may deploy the  Si570 (expensive) and/or Si5351 or the MS5351M (Chinese and actually better)

CPU - Arduino Nano 5v ATMEGA328 or Chinese equivalent which is better

## Display:
- 2.8" SPI TFT ILI9341
- 1.8" SPI TFT ST7735
- LCD 1602
- OLED 0.91" 128x32, OLED 0.96" 128x64, OLED 1.3" 128/132x64

## Real-time clock:
- DS3231(preferred) or DS1307(Tiny RTC) or PCF8563

## Keyboard: 
-  BPF & other 
-  PCF8574

## Rotary encoder 

At this particular stage of the analysis, I believe that this code is in accordance with the conventional quadrature rotary encoder.  However, the omnipotent original author suggests that these are supported.

- optical 360-400 pulse/turn or 
- mechanical 20 pulse/turn

## Over the top offerings

- This allows any combination of two Si5351 and one Si570: Si5351, Si570, Si5351+Si5351, Si570+Si5351, Si570+Si5351+Si5351.
- Dual VFO A/B, SPLIT, RIT.
- Save current freq and band to EEPROM.
- CAT-enabled (Kenwood protocol).

## Supports different TRX architecture:

 1. Single and double IF superheterodyne.
 2. Up-conversion with general coverage 2-30MHz and high IF.
 3. Direct conversion with 2x or 4x output.
 4. Direct conversion with quadrature output.

Project homepage http://www.ur5ffr.com/viewtopic.php?t=174

## Required libraries:

 1. PDQ GFX with packed font support https://github.com/andrey-belokon/PDQ_GFX_Libs. You need to install PDQ_GFX, PDQ_ILI9341 and PDQ_ST7735
 2. UR5FFR_Si5351 https://github.com/andrey-belokon/UR5FFR_Si5351
 3. SSD1306Ascii - install from Arduino IDE

<img src="doc\ST7735_570_5351_two_plate\img\synt_v2_tft-10pin.jpg"></img>
<img src="doc\ST7735_570_5351_two_plate\img\synt_v2_tft-8pin.jpg"></img>
<img src="doc\ST7735_570_5351_two_plate\img\synt_1.8_9.jpg"></img>
<img src="doc\ST7735_570_5351_two_plate\img\synt_1.8_4.jpg"></img>
<img src="doc\ST7735_570_5351_two_plate\img\synt_1.8_7.jpg"></img>

<img src="doc\ST7735_570_5351_two_plate\Schematic_Digital VFO 1.8 main board 2.0.png"></img>
<img src="doc\ST7735_570_5351_two_plate\Schematic_Digital VFO 1.8 display board 2.0.png"></img>

Copyright (c) 2016-2020, Andrii Bilokon, UR5FFR
Licence GNU GPL, see licence.txt for more information
