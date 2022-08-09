#include <M5Stack.h>
int i=0;
// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin();
  M5.Lcd.setTextColor(0xffff);
  M5.Lcd.setTextSize(10);
  M5.Lcd.print(i);
}

// the loop routine runs over and over again forever
void loop() {
  if(M5.BtnA.wasPressed()){
    M5.Lcd.fillScreen(0x00);
    M5.Lcd.setCursor(0,0);
    i+=1;
    M5.Lcd.print(i);
  } else if (M5.BtnB.wasPressed()){
    if(i>0) {
      M5.Lcd.fillScreen(0x00);
      M5.Lcd.setCursor(0,0);
      i-=1;
      M5.Lcd.print(i);
    } else {
      M5.Lcd.fillScreen(0x00);
      M5.Lcd.setCursor(0,0);
      M5.Lcd.setTextSize(4);
      M5.Lcd.print("Your number can't go beyond zero!");
    }
  } else if (M5.BtnC.wasPressed()){
      M5.Lcd.fillScreen(0x00);
      M5.Lcd.setCursor(0,0);
      i=0;
      M5.Lcd.print(i);
  }
  M5.update();
}
