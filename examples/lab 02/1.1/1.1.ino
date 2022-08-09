#include <M5Stack.h>

int ledPin = 21;
int ledState = LOW;

void setup(){
  M5.begin();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  M5.update();
  M5.Lcd.setBrightness(255);
}

void loop() {
  if (M5.BtnA.wasPressed() or M5.BtnB.wasPressed() or M5.BtnC.wasPressed()){
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    M5.Lcd.fillScreen(0xffff);
  }
  M5.Lcd.fillScreen(0x00);
  M5.update();
}  

