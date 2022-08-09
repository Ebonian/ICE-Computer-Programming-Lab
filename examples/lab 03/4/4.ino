#include <M5Stack.h>
const int nC4 = 262;
const int nD4 = 294;
const int nE4 = 330;
const int nF4 = 349;
const int nG4 = 392;
const int nA4 = 440;
const int nB4 = 494;

const int note[] = {
  nE4, nE4,nE4,nE4, nE4, nE4, nE4, nG4, nC4, nD4, nE4, nF4, nF4, nF4, nF4, nF4, nE4, nE4, nE4, nD4, nD4, nE4, nD4, nG4
};


void setup() {
  // put your setup code here, to run once:
  M5.begin();
}

int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  
  if (M5.BtnA.wasPressed()) {
    M5.Speaker.tone(note[i]);
  }
  else if (M5.BtnA.wasReleased()) {
    M5.Speaker.mute(); 
    i++;
  }
  if (i == 24) {
    i = 0;
  }
  M5.update();
}
