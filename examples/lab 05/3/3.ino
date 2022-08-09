#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>

#define DHTPIN 5
SimpleDHT11 dht;
int temperature, humidity;
int old_t = -1000;
int old_h = -1000;
int unitChange = 0;
String unit = " C";


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextFont(4);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp, humid;
  int status = dht.read2(DHTPIN, &temp, &humid, NULL);
  if (status == SimpleDHTErrSuccess) {
    humidity = humid;
  }
  if (unitChange % 2 == 0) {
    temperature = temp;
    unit = " C";
  }
  else if (unitChange % 2 == 1) {
    temperature = temp*9/5+32;
    unit = " F";
  }
  if (M5.BtnA.wasPressed()) {
    unitChange ++;
  }
  if (temperature != old_t || humidity != old_h || M5.BtnA.wasPressed()) {
    if (temp > 27) {
      M5.Lcd.setTextColor(0xe8e4);
    }
    else {
      M5.Lcd.setTextColor(0x2589);
    }
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(temperature);
    M5.Lcd.print(unit); 
    M5.Lcd.setCursor(0,70);
    M5.Lcd.print(humidity);
    M5.Lcd.print(" %");
  }
  
  old_t = temperature;
  old_h = humidity;
  M5.update();
}
