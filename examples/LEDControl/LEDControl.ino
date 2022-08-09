#include <MicroGear.h>
#include <M5Stack.h>

// constants won't change. They're used here to 
// set pin numbers:
#define D0 16  // USER LED Wake
#define ledPin  D0        // the number of the LED pin

const char* ssid     = "Fah";
const char* password = "123456789";

#define APPID   "PenpimSmartHome"
#define KEY     "6kCilGm9cQPbH0e"
#define SECRET  "YtCZWi6Rgjs1Y4BDu4nSxL78d"

#define ALIAS   "M5Stack"
#define TargetWeb "DigitalOUTPUT_HTML_web"

WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
  Serial.print("Incoming message --> ");
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
  for (int i = 0; i < msglen; i++) 
  {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
  Serial.println();

  String stateStr = String(strState).substring(0, msglen);

  if(stateStr == "ON") 
  {
    digitalWrite(ledPin, HIGH);
    microgear.chat(TargetWeb, "ON");
  } 
  else if (stateStr == "OFF") 
  {
    digitalWrite(ledPin, LOW);
    microgear.chat(TargetWeb, "OFF");
  }
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

    pinMode(ledPin,OUTPUT);
    digitalWrite(ledPin,LOW); // Turn off LED
}

void loop() 
{
  if(microgear.connected()) 
  {
    microgear.loop();
    Serial.println("connect...");
  } 
  else 
  {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
  delay(250);
}
