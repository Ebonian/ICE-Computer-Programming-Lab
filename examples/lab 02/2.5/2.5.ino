#include <M5Stack.h>

void setup() {
  M5.begin();
  Serial.begin(9600);
  pinMode(21,OUTPUT);
  digitalWrite(21, LOW);
  menu();
  M5.update();
}

int readData=0;

void loop() {
  if (Serial.available()>0) {
    readData = Serial.read();
    Serial.write(readData);
    Serial.println("");
    if (readData == '1') {
        student1();
        delay (3000);
        turnLEDOff();
    }
    else if (readData == '2') {
        student2();
        delay (3000);
        turnLEDOff();
    }
    else if (readData == '3') {
        student1();
        student2();
        delay (3000);
        turnLEDOff();
    }
    menu();
  }
  M5.update();
}

void menu() {
  Serial.println("Exercise 5 : Multi-functions program");
  Serial.println("\nPlease select your function.");
  Serial.println(" 1 - First member ");
  Serial.println(" 2 - Second member ");
  Serial.println(" 3 - Both member ");
  Serial.print("\n> ");
}

void turnLEDOff() {
  Serial.println(" - ");
  digitalWrite(21, LOW);
}

void student1() {
  Serial.println("1. ID: 6338138921  Mr. Panus Sawetpiyakul");
  digitalWrite(21, HIGH);
}

void student2() {
  Serial.println("2. ID: 1298318336  Mr. Sawetpiyakul Panus");
  digitalWrite(21, HIGH);
}

