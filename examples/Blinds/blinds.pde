/*
Moving Blinds connected to D5 and D6 PINS to 20 percent and back to 0 in a loop
*/

#define WINPOW  D5    // The POWER PIN for the Windpw
#define WINUD   D6    // The UP/DOWN selection PIN for the Window
#define WINTIME 24000 // 24 sec for full open(close);

#include <Blinds.h>

Blinds win(WINPOW, WINUD, WINTIME, win, true);

unsigned long c;

void setup() {
  Serial.begin(9600);
  c = millis();
}

void loop() {
  win.run();
  if (millis() - c > 500) {
    if(win.getPosition() == 20) win.setPosition(0);
    if(win.getPosition() == 0) win.setPosition(20);
    c = millis();
  }  
}