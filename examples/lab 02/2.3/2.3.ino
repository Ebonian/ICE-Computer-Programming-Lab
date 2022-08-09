void setup() {
      Serial.begin(9600);
      Serial.println("Exercise 3 : Ascii Converter");
}
int readData=0;
void loop() {
  if (Serial.available()>0) {
      readData = Serial.read();
      Serial.print("READ '");
      Serial.write(readData);
      Serial.print("' - ");
      Serial.print("DEC: ");
      Serial.print(readData,DEC);
      Serial.print(", HEX: 0x");
      Serial.print(readData,HEX);
      Serial.print(", BIN: ");
      Serial.print(readData,BIN);
      Serial.println(" .. done");
  }
}

