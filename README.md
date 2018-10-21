# ClickerFraud
[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/) [![GitHub forks](https://img.shields.io/github/forks/ThirtySomething/ClickerFraud.svg?style=social&label=Fork&maxAge=2592000)](https://GitHub.com/ThirtySomething/ClickerFraud/network/) [![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/) [![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)

**ClickerFraud** is distributed under the terms of the [**Unlicense**][Unlicense]. The text of the license is included in the file [<code>LICENSE</code>][license] in the project root.

## Motivation
There are many clicker games. Playing can ruin your mouse, touchpad, or fingers. I've been thinking about how to simulate clicking. Normal software may not work depending on which clicker game you are playing. But hardware would do it. An additional benefit of hardware is the independency of operating systems. In theory this should work for Linux, Mac OS and also Windows.

## Arduino/Teensy
At first I thought of an [Arduino]. But unfortunately this device does not emulate a [HID Device] out of the box. Through a quick search on the internet I found the [Teensy] board. This emulates a [HID device] and is surprisingly cheaper than an [Arduino]. And the [Arduino IDE][AIDE] supports the [Teensy] board - everything was set.

## The software
The code for the clicker cheater is just simple:

```C++
#include <Mouse.h>

#define CPS 20                              // Clicks per second
#define ONS 1000                            // One second in milli seconds
#define LIM 1000                            // Clicks for one loop
#define GAP 2000                            // Delay before loop restarts
#define ICMI 10                             // Minimum random delay
#define ICMA 20                             // Maximum random delay

int defaultWait;                            // Delay after one click
int countClicks;                            // Click counter
int randomWait;                             // Random delay after one click

void setup() {
  Mouse.begin();                            // Initialize mouse
  randomSeed(analogRead(0));                // Initialize 'random device'
 }

void loop() {
  defaultWait = (int)(ONS/CPS);             // Calculate delay after one click
  countClicks = 0;                          // Init click counter
  randomWait = random(ICMI, ICMA);          // Calculate random delay after one click
  while (countClicks < LIM)                 // While amount of clicks/loop not reached
  {
    Mouse.click(MOUSE_LEFT);                // Do a click on left mouse button
    delay(defaultWait + randomWait);        // Wait until next action
    randomWait = random(ICMI, ICMA);        // Recalculate random delay after one click
    countClicks++;                          // Increase clicks/loop counter
  }
  delay(GAP);                               // Wait before next loop start
}
```

There are some tricks:

- The **GAP** defines the delay between the restart of the loop. Without this delay the USB bus can be flooded. This will continue clicking even though the device has been unplugged from the USB.
- The **randomWait** has been added because the games sometimes try to detect scammers. This causes uneven delays between each click and makes detection more difficult. Maybe this should also be added to the **GAP** duration.

## Improvements
Of course, a complete fraud device requires much more than this demonstration. For example:

- A display to show the current setup, for example the [Adafruit Monochrome 0.96" 128x64 OLED graphic display][Display]
- A switch to start/stop the loop as described in the [Arduino manual][Switch]
- A possiblity to change the setup, maybe a [rotary encounter][RotaryEncounter]
- Anything else I forgot.

But that exceeds my abilities. The [Teensy] comes as a [PCB] - you have to solder any extension to this board.

[Display]: https://www.adafruit.com/product/326
[AIDE]: Software
[Arduino]: https://store.arduino.cc/arduino-uno-rev3
[HID Device]: https://en.wikipedia.org/wiki/Human_interface_device
[license]: https://github.com/ThirtySomething/YAIP/ClickerFraud/master/LICENSE
[PCB]: https://en.wikipedia.org/wiki/Printed_circuit_board
[RotaryEncounter]: https://playground.arduino.cc/Main/RotaryEncoders
[Switch]: https://www.arduino.cc/en/Tutorial/Button
[Teensy]: https://www.pjrc.com/store/teensy.html
[Unlicense]: http://unlicense.org/
