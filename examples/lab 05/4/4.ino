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

uint32_t targetTime = 0;                    // for next 1 second timeout


static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x


uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3); 
uint8_t ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time


byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;
int ampmCheck = 0;
String ampm = "AM";


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Wire.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextFont(4);
  targetTime = millis() + 1000;
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
    screen (temperature, unit, humidity, hh, mm, ss, ampm);
  }
  old_t = temperature;
  old_h = humidity;
  if (M5.BtnB.wasPressed()){
    ampmCheck ++;
  }
  if (targetTime < millis() || M5.BtnB.wasPressed()) {
    // Set next update for 1 second later
    targetTime = millis() + 1000;
    // Adjust the time values by adding 1 second
    ss++;              // Advance second
    if (ss == 60) {    // Check for roll-over
      ss = 0;          // Reset seconds to zero
      omm = mm;        // Save last minute time for display update
      mm++;            // Advance minute
      if (mm > 59) {   // Check for roll-over
        mm = 0;
        hh++;          // Advance hour
        if (hh > 23) { // Check for 24hr roll-over (could roll-over on13)
          hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
    }
    screen (temperature, unit, humidity, hh, mm, ss, ampm);
  }
  M5.update();
}

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

void screen(int temperature, String unit, int humidity, int hh, int mm, int ss, String ampm) {
    M5.Lcd.fillScreen(0);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print(temperature);
    M5.Lcd.print(unit); 
    M5.Lcd.setCursor(0,70);
    M5.Lcd.print(humidity);
    M5.Lcd.print(" %");
    M5.Lcd.setCursor(0,140);
    if (ampmCheck % 2 == 0){
      ampm = "";
    }
    else if (ampmCheck %2 == 1) {
      if (hh > 11) {
        hh -= 12;
        ampm = "PM";
      }
      else if (hh <= 11) {
        ampm = "AM";
      }
    }
    if (hh<10) {
      M5.Lcd.print('0');
    }
    M5.Lcd.print(hh);
    M5.Lcd.print(":");
    if (mm<10) {
      M5.Lcd.print('0');
    }
    M5.Lcd.print(mm);
    M5.Lcd.print(":");
    if (ss<10) {
      M5.Lcd.print('0');
    }
    M5.Lcd.print(ss);
    M5.Lcd.print (ampm);
}
