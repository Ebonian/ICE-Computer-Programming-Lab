#include <M5Stack.h>

#define NOTE_B1 262
#define NOTE_Cd1 277
#define NOTE_D1 294
#define NOTE_Dd1 311
#define NOTE_E1 330
#define NOTE_F1 349
#define NOTE_Fd1 370
#define NOTE_G1 392
#define NOTE_Gd1 415
#define NOTE_A1 440
#define NOTE_Ad1 466
#define NOTE_H1 494

int music[] = {
  NOTE_E1, NOTE_E1, NOTE_E1,
  NOTE_E1, NOTE_E1, NOTE_E1,
  NOTE_E1, NOTE_G1, NOTE_Cd1, NOTE_D1, NOTE_E1,
  NOTE_F1, NOTE_F1, NOTE_F1, NOTE_F1,
  NOTE_E1, NOTE_E1, NOTE_E1,
  NOTE_E1, NOTE_D1, NOTE_D1, NOTE_E1, NOTE_D1,
  NOTE_G1
};

int t = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (M5.BtnA.wasPressed()) {
    if (t == ((sizeof(music)/sizeof(int))-1)) {
      t = 0;
    }
    M5.Speaker.tone(music[t]);
  }
  if (M5.BtnA.wasReleased()) {
    M5.Speaker.mute();
    t++;
  }
  M5.update();
}
