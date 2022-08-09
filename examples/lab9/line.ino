#include <M5Stack.h>
#include<WiFi.h>
#include<WiFiClientSecure.h>

String LINE_TOKEN = "lVtmgYtPN6tUDJbLU8nj8vaCFw6fvuW4x8PlEd6NcNb";

#include <M5Stack.h>
#include <SimpleDHT.h>
SimpleDHT11 dht;
#define DHTPIN 5

float temp, humid, Temp, Humidity;


// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

const char* ssid     = "Fah";   //Wifi Name
const char* password = "123456789";   //Wifi Password

void setup() {

  
      
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  int status = dht.read2(DHTPIN,&temp,&humid,NULL);
      if(status == SimpleDHTErrSuccess){
        Temp=temp;
        Humidity=humid;
      }
   Line_Notify(LINE_TOKEN,String(Humidity)); // Call funtion Line_Notify();
      delay(100);
   M5.update();
}

void Line_Notify(String LINE_Token, String message) {

  String msg = String("message=") + message;

  WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Authorization: Bearer " + String(LINE_Token) + "\r\n";
  req += "Content-Length: " + String(msg.length()) + "\r\n";
  req += "\r\n";
  req +=  msg;

  client.print(req);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}
