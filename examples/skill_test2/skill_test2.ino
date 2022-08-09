#include <M5Stack.h>
char readData;
boolean a=false,b=false,c=false;
void setup() {
  M5.begin();
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()>0){
    readData = Serial.read();
    Serial.write(readData);
    if(readData>=48 && readData<=57) {a=true;b=false;}
    else if(readData>=65 && readData<=90) {a=false;b=true;}
    else  c=true;
    if(c==true){
      M5.Lcd.fillScreen(0x00);
      M5.Lcd.drawCircle(160,120,100,0xffff);
      M5.Lcd.fillCircle (130,120,3,0xffff);
      M5.Lcd.fillCircle (190,120,3,0xffff);
      M5.Lcd.drawLine(130,150,190,150,0xffff);
   
    }
    
    
    if (a==true){
      M5.Lcd.fillScreen(0x00);
      M5.Lcd.drawCircle(160,120,100,0xffff);
      M5.Lcd.fillCircle (130,100,3,0xffff);
      M5.Lcd.fillCircle (190,100,3,0xffff);
      M5.Lcd.drawCircleHelper(160,160,30,3,0xffff);
      
    
      
    } if (b==true){
      M5.Lcd.fillScreen(0x00);
      M5.Lcd.drawCircle(160,120,100,0xffff);
      M5.Lcd.fillCircle (130,100,3,0xffff);
      M5.Lcd.fillCircle (190,100,3,0xffff);
      M5.Lcd.drawCircleHelper(160,130,30,4,0xffff);
      M5.Lcd.drawCircleHelper(160,130,30,8,0xffff);
      
    } 
      

  }
   M5.update(); 
  }
  

//}
