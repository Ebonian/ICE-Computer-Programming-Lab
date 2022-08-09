#include <M5Stack.h>
const int nC4 = 262;
const int nD4 = 294;
const int nE4 = 330;
const int nF4 = 349;
const int nG4 = 392;
const int nA4 = 440;
const int nB4 = 494;
const int nC5 = nC4*2;
const int nD5 = nD4*2;
const int nE5 = nE4*2;
const int nF5 = nF4*2;
const int nG5 = nG4*2;
const int nA5 = nA4*2;
const int nB5 = nB4*2;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {
    int key = Serial.read();
    Serial.write(key);
    switch (key) {
      case 'c' :
        paino(nC4);
      break;
      case 'd' :
        paino(nD4);
      break;
      case 'e' :
        paino(nE4);
      break;
      case 'f' :
        paino(nF4);
      break;
      case 'g' :
        paino(nG4);
      break;
      case 'a' :
        paino(nA4);
      break;
      case 'b' :
        paino(nB4);
      break;
      case 'C' :
        paino(nC5);
      break;
      case 'D' :
        paino(nD5);
      break;
      case 'E' :
        paino(nE5);
      break;
      case 'F' :
        paino(nF5);
      break;
      case 'G' :
        paino(nG5);
      break;
      case 'A' :
        paino(nA5);
      break;
      case 'B' :
        paino(nB5);
      break;
    }
    delay (1300);
    menu();
  }
  M5.update();
}

void paino(int frequency) {
  M5.Speaker.tone(frequency);
  delay (1000);
  M5.Speaker.mute();
}
void menu() {
  Serial.println("\nExercise 3\nPlease enter note [c, d, e, f, g, a, b, C, D, E, F, G, A, B]");
  Serial.print(">");
}

