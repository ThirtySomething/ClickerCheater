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
