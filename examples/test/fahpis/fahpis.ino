#include <M5Stack.h>
int i=0;
void setup() {
  M5.begin();
  Serial.begin(9600);
  M5.Lcd.setTextColor(0xffff);
  M5.Lcd.setTextSize(10);
  M5.Lcd.print(i);
  
  
  // put your setup code here, to run once:

}

void loop() {
  
  if (M5.BtnA.wasPressed()){
    i=i+1;
    M5.Lcd.fillScreen(0x00);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(i);
  
    
  } else if (M5.BtnB.wasPressed()){
    i=i-1;
    M5.Lcd.fillScreen(0x00);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(i);
    
  } else if (M5.BtnC.wasPressed()) {
    i=0;
    M5.Lcd.fillScreen(0x00);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(i);
    
    
  }
  M5.update();

}
