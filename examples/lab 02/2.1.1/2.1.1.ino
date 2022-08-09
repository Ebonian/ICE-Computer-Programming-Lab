#include <M5Stack.h>

void setup() {
  M5.begin();
  Serial.begin(9600);
  Serial.println(" ");
  M5.update();
}

void loop() {
  Serial.print("The button is ");
  if (M5.BtnA.wasPressed()) {
    Serial.println("Pressed");
  } else {
    Serial.println("Released");
  }
  M5.update();
}
