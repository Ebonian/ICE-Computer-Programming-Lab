#include <M5Stack.h>
int ledPin = 21;
int ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(9600);
  Serial.println("Exercise 4 : Enter the number to light up LED");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
  M5.update();
}
int readData = 10;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {
    Serial.println("Please input a number");
    readData = Serial.read();
    if (readData>=48 and readData<=57){
       digitalWrite(ledPin, HIGH);
       delay (3000);
       digitalWrite(ledPin, LOW);
    }
  }
   M5.update();
}
