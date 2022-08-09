#include <M5Stack.h>
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setBrightness(255);
  M5.Lcd.fillScreen(0xffff);
  M5.Lcd.drawCircle(160,120,101,0x00);
  M5.Lcd.fillCircleHelper(160,120,100,2,0,0xffff);
  M5.Lcd.fillCircleHelper(160,120,100,1,0,0x00);
  M5.Lcd.fillCircle(210,120,50,0xffff);
  M5.Lcd.fillCircle(110,120,50,0x00);
  M5.Lcd.fillCircle(210,120,10,0x00);
  M5.Lcd.fillCircle(110,120,10,0xffff);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
