#include <M5Stack.h>
#include <SimpleDHT.h>
#include <Wire.h>

#define DHTPIN 5
SimpleDHT11 dht;
int temperature, humidity;
int old_t = -1000;
int old_h = -1000;


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
  int xpos = 0;
  int ypos = 0;
  if (status == SimpleDHTErrSuccess) {
    temperature = temp;
    humidity = humid;
  }
  if (temperature != old_t) {
    if (temp > 27) {
      M5.Lcd.setTextColor(0xe8e4);
    }
    else {
      M5.Lcd.setTextColor(0x2589);
    }
    M5.Lcd.setCursor(0,0);
    M5.Lcd.fillScreen(0);
    M5.Lcd.print(temperature);
    M5.Lcd.print(" C"); 
    M5.Lcd.setCursor(0,70);
    M5.Lcd.print(humidity);
    M5.Lcd.print(" %");
  }
  if (humidity != old_h){
    M5.Lcd.setCursor(0,0);
    M5.Lcd.fillScreen(0);
    M5.Lcd.print(temperature);
    M5.Lcd.print(" C"); 
    M5.Lcd.setCursor(0,70);
    M5.Lcd.print(humidity);
    M5.Lcd.print(" %");
  }
  old_t = temperature;
  old_h = humidity;
  M5.update();
}
