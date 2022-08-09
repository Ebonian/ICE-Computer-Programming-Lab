//Created by Panus Sawetpiyakul 9/9/2020

#include <M5Stack.h>
#define TFT_GREY 0x5AEB

uint32_t targetTime = 0;
uint8_t ss = 0, mm = 0; 

byte omm = 99, oss = 99;
int xcolon = 160;
unsigned int colour = 0;

int xpos = 0, ypos = 75;

int timeCheckA, timeCheckB, timeCheckC = 0;
int countdownCheck = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextSize(1);
  targetTime = millis() + 1000;
  draw(0, 0);
}
void loop() {
  // put your main code here, to run repeatedly:
  if (M5.BtnC.wasPressed()) {
    timeCheckC = millis();
  }
  if (M5.BtnC.wasReleased() && millis() - timeCheckC >= 5000 && countdownCheck%2 == 0) {
      mm = 0;
      ss = 0;
      timeCheckC = 0; 
  }
  if (M5.BtnC.wasReleased() && millis() - timeCheckC <= 5000){
    countdownCheck ++;
  }
  if (M5.BtnA.wasPressed() && countdownCheck%2 == 0) {
    timeCheckA = millis();
    mm ++;
    if (mm == 6) {
      mm = 0;
    }
  }
  if (M5.BtnA.wasReleased() && millis() - timeCheckA >= 5000 && countdownCheck%2 == 0) {
    mm = 0;
    timeCheckA = 0; 
  }
  if (M5.BtnB.wasPressed() && countdownCheck%2 == 0) {
    timeCheckB = millis();
    ss ++;
    if (ss == 60) {
      ss = 0;
      mm ++;
      if (mm == 6) {
        mm = 0;
      }
    }
  }
  if (M5.BtnB.wasReleased() && millis() - timeCheckB >= 5000 && countdownCheck%2 == 0) {
    ss = 0;
    timeCheckB = 0;
  }
  if (mm == 0 && ss == 0) {
    countdownCheck = 0;
  }
  countdown (countdownCheck);
  if (M5.BtnA.isPressed() or M5.BtnB.isPressed() or M5.BtnC.isPressed()){
    M5.Speaker.mute();
  }
  draw(mm, ss);
  M5.update();
}

void draw(uint8_t mm, uint8_t ss) {
  if (omm != mm) {
    M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
    omm = mm;
    xpos = xcolon;
    xpos -= M5.Lcd.drawChar(':', xpos, ypos-8, 8);
    xpos -= M5.Lcd.drawNumber(mm, xpos - 24, ypos, 8);
    xpos -= M5.Lcd.drawChar('0', xpos - 24, ypos, 8);
  }
  if (oss != ss) {
    oss = ss;
    xpos = xcolon;
    if (ss%2) {
      M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
      xpos += M5.Lcd.drawChar(':', xpos, ypos - 8, 8);
    }
    else {
      xpos += M5.Lcd.drawChar(':', xpos, ypos - 8, 8);
    }
    if (ss < 10) xpos += M5.Lcd.drawChar('0', xpos, ypos, 8); 
    xpos += M5.Lcd.drawNumber(ss, xpos, ypos, 8);
  }
}

void countdown(int coundownCheck) {
  if (targetTime < millis() && coundownCheck%2 == 1) {
    targetTime = millis() + 1000;  
    if (ss == 0) {
      ss = 60;
      omm = mm;        
      mm--;            
    }
    ss--;
    if (mm == 0 && ss == 0) {
      M5.Speaker.tone(232);
    }            
  }
}

