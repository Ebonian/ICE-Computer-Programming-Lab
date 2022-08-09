//Original source code by Phu
#include <M5Stack.h>
const int nC4 = 262;
const int nD4 = 294;
const int nE4 = 330;
const int nF4 = 349;
const int nG4 = 392;
const int nA4 = 440;
const int nB4 = 494;

const int note[] = {
  nE4, nE4,nE4,nE4, nE4, nE4, nE4, nG4, nC4, nD4, nE4, nF4, nF4, nF4, nF4, nF4, nE4, nE4, nE4, nE4, nE4, nD4, nD4, nE4, nD4, nG4
};

const int rhythm[] = {
  8,8,4,8,8,4,8,8,6,16,2,8,8,6,16,8,8,8,16,16,8,8,8,8,4,4
};

void setup() {
  // put your setup code here, to run once:
  M5.begin();
}

int i = 0;
int playstopper = 0;
int timing = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (M5.BtnA.wasPressed()){
    playstopper = 1;
    timing = 2000;
  }
  else if (M5.BtnB.wasPressed()){
    playstopper = 1;
    timing = 4000;
  }
  else if (M5.BtnC.wasPressed()){
    playstopper = 1;
    timing = 3000;
  }
  if (playstopper != 0) {
    play(timing);
  }
  M5.update();
}

void play(int timing) {
  M5.Speaker.tone(note[i]);
  int wait = timing/rhythm[i];
  delay(wait);
  i++;
  if (i == 26) {
    i = 0;
  }
  M5.Speaker.mute();
}
