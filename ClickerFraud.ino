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
