#include <M5Stack.h>
#include <WiFi.h>
#include <Wire.h>

#define triggerPin 14
#define echoPin 12

// Replace with your SSID and Password
const char* ssid     = "a";
const char* password = "123456789";
int binheight = 50;
// Replace with your unique IFTTT URL resource
const char* resource = "https://maker.ifttt.com/trigger/trash/with/key/cX9ZsWUe1IwnU0r4vZx4Ey";

// How your resource variable should look like, but with your own API KEY (that API KEY below is just an example):
//const char* resource = "/trigger/bme280_readings/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy3";

// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Time to sleep
uint64_t uS_TO_S_FACTOR = 1000000;  // Conversion factor for micro seconds to seconds
// sleep for 30 minutes = 1800 seconds
uint64_t TIME_TO_SLEEP = 10;
int throwtime;



//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

void setup() {
  Serial.begin(115200); 
  delay(2000);
  pinMode(triggerPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  binheight = getDistance(triggerPin,echoPin);
  initWifi();
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);
  String jsonObject = String("{\"value1\":\"") + String(binheight) + "\",\"value2\":\"" + "bin height"
                      + "\"}";
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}

void loop() {
  while(true)
  {
    delay(10000);
    makeIFTTTRequest();
  }
}

// Establish a Wi-Fi connection with your router
void initWifi() {
  Serial.print("Connecting to: "); 
  Serial.print(ssid);
  WiFi.begin(ssid, password);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}

// Make an HTTP request to the IFTTT web service
void makeIFTTTRequest() {
  Serial.print("Connecting to "); 
  Serial.print(server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);
  float percentage = ((binheight - getDistance(triggerPin,echoPin))/binheight)*100;
  percentage = percentage >0 ? percentage <100? percentage : 100 : 0;
  String jsonObject = "";
  if(percentage<75 and throwtime < 48){
  jsonObject = String("{\"value1\":\"") + String(percentage) + "\",\"value2\":\"" + "no need to throw the trash"
                      + "\"}";
  if(percentage<5){ 
  throwtime = 0;
  }
  else{
  throwtime += 6;
  }
  }
  else{
  jsonObject = String("{\"value1\":\"") + String(percentage) + "\",\"value2\":\"" + "Time to throw out the trash"
                      + "\"}";
  }
                      
  // Comment the previous line and uncomment the next line to publish temperature readings in Fahrenheit                    
  /*String jsonObject = String("{\"value1\":\"") + (1.8 * bme.readTemperature() + 32) + "\",\"value2\":\"" 
                      + (bme.readPressure()/100.0F) + "\",\"value3\":\"" + bme.readHumidity() + "\"}";*/
                      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}
float getDistance(int tPin,int ePin){
  
  long duration, distance;
    
  digitalWrite(tPin, LOW);  // Reset the trigger pin.
  delayMicroseconds(2); 
  digitalWrite(tPin, HIGH);  // Start a measurement.
  delayMicroseconds(10); // 
  digitalWrite(tPin, LOW);   // Complete the pulse.
  duration = pulseIn(ePin, HIGH);  // Wait for a reflection pulse.
  distance = (duration/2) / 29.1;     // Calculate the appropriate distance using the estimated speed of sound.

  // This section is useful when debugging the sensor.
/*
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
   Serial.print(distance);
   Serial.println(" cm");
  }
  */
  return distance;
}
