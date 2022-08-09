#include <M5Stack.h>
int count = 0;

void setup() {
  M5.begin();
  Serial.begin(9600);
  Serial.println(" ");
  M5.update();
}

void loop() {
  if (M5.BtnA.wasPressed()) {
    Serial.print("The button is ");
    count += 1;
    Serial.print("Click");
    Serial.println(count);
  } 
  M5.update();
}

