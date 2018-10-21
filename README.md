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

#define DELAY_MIN 25                                // Minimum random delay
#define DELAY_MAX 50                                // Maximum random delay
#define CLICKS_MIN 500                              // Minimum number of clicks per loop
#define CLICKS_MAX 1000                             // Maximum number of clicks per loop
#define WAIT_MIN 1000                               // Minimum miliseconds to wait after loop
#define WAIT_MAX 2000                               // Maximum miliseconds to wait after loop

int countClicks;                                    // Click counter
int randomWait;                                     // Random delay after one click
int clicksInLoop;                                   // Number of clicks per loop
int waitLoop;                                       // Miliseconds to wait after loop

void setup() {
  Mouse.begin();                                    // Initialize mouse
  randomSeed(analogRead(0));                        // Initialize 'random device'
 }

void loop() {
  countClicks = 0;                                  // Init click counter
  clicksInLoop = random(CLICKS_MIN, CLICKS_MAX);    // Random number of clicks per loop
  while (countClicks < clicksInLoop)                // While amount of clicks/loop not reached
  {
    Mouse.click(MOUSE_LEFT);                        // Do a click on left mouse button
    randomWait = random(DELAY_MIN, DELAY_MAX);      // Recalculate random delay after one click
    delay(randomWait);                              // Wait until next action
    countClicks++;                                  // Increase clicks/loop counter
  }
  waitLoop = random(WAIT_MIN, WAIT_MAX);            // Random milliseconds to wait
  delay(waitLoop);                                  // Wait before next loop start
}
```

There are some tricks:

- The **waitLoop** defines the delay between the restart of the loop. Without this delay the USB bus can be flooded. This will continue clicking even though the device has been unplugged from the USB.
- The **randomWait** has been added because the games sometimes try to detect scammers. This causes uneven delays between each click and makes detection more difficult.

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
