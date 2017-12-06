# Redgick_GFX
The core graphics library for all our displays.

## Installation

[Download this repository](https://github.com/redgick/Redgick_GFX/archive/master.zip) and unzip the following library folders into the Arduino libraries folder on your computer :

 - Redgick_GFX
 - Redgick_MatrixHT1632C
 - Redgick_MatrixLaboitePro
 - Redgick_MatrixMAX72XX

In the Arduino IDE, look at *File/Examples/Redgick_GFX* folder to load an example sketch.

## Hardware compatibility

<table>
<tr>
  <th rowspan=2>LED Matrix</th><th colspan=3>Arduino/Genuino</th><th>ESP8266</th><th rowspan=2>library</th>
</tr>
<tr>
  <th>Uno</th><th>Mega or Mega 2560</th><th>Mega ADK</th><th>NodeMCU</th>
</tr>
<tr>
  <th><a href="http://store3.sure-electronics.com/de-dp14116">Sure Electronics 32x16 RG Dual Color LED Dot Matrix Unit Board</a><td>OK</td><td>OK</td><td>OK</td><td>OK</td><td>Redgick_MatrixHT1632C</td>
</tr>
<tr>
  <th><a href="https://www.laboite.cc/help">laboîte originale</a></th><td>OK</td><td>OK</td><td>OK</td><td>OK</td><td>Redgick_MatrixHT1632C</td>
</tr>
<tr>
  <th>laboîte pro (prototype)</th><td>-</td><td>-</td><td>-</td><td>OK</td><td>Redgick_MatrixLaboitePro</td>
</tr>
<tr>
  <th><a href="https://github.com/laboiteproject/laboite-maker">laboîte maker</a></th><td>-</td><td>-</td><td>-</td><td>OK</td><td>Redgick_MatrixMAX72XX</td>
</tr>
</table>
