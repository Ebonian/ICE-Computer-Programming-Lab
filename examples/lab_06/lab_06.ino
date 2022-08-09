#include <MicroGear.h>
#include <M5Stack.h>
#include <SimpleDHT.h>

const char* ssid     = "Fah";
const char* password = "0957322313";

#define APPID   "PenpimSmartHome"
#define KEY     "C0eu0RMDRAxvLSP"
#define SECRET  "Vd2FqmMhNdtrIxF9zD2P60SYn"

#define ALIAS   "NodeMCU1"
#define TargetWeb "HTML_web"

#define D4 5   // TXD1
#define DHTPIN G5   // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

SimpleDHT11 dht;

WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
    Serial.print("Incoming message --> ");
    msg[msglen] = '\0';
    Serial.println((char *)msg);
}


void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}

void setup() 
{
     /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);

    
    Serial.begin(115200);
    Serial.println("Starting...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
       delay(250);
       Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
}
void loop() 
{
    if (microgear.connected())
    {
       microgear.loop();
       Serial.println("connected");
  float temp, humid,Temp,Humidity;
  float status = dht.read2(DHTPIN, &temp, &humid, NULL);
  if (status == SimpleDHTErrSuccess) {
    Temp = temp;
    Humidity = humid;
  }
       // Read temperature as Celsius (the default)
       String data = "/" + String(Humidity) + "/" + String(Temp);
       char msg[128];
       data.toCharArray(msg,data.length());
       Serial.println(msg);    

       microgear.chat(TargetWeb , msg);
    }
   else 
   {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
   }
    delay(1500);
}
