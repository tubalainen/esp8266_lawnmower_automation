//OGD: Added support for 4 inputs, and changed from LOW to HIGH on the outputs
//OGD: Tested with NodeMcu 
// NodeMcu: https://goo.gl/W0u9Sp
// 4 channel relay module: https://goo.gl/RQrd4D
//EJ: 4 Relay Switch over WIFI using MQTT and Home Assistant with OTA Support
//EJ: The only way I know how to contribute to the HASS Community... you guys ROCK!!!!!
//EJ: Erick Joaquin :-) Australia
// Original sketch courtesy of ItKindaWorks
//ItKindaWorks - Creative Commons 2016
//github.com/ItKindaWorks
//
//Requires PubSubClient found here: https://github.com/knolleary/pubsubclient
//
//ESP8266 Simple MQTT switch controller


#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

void callback(char* topic, byte* payload, unsigned int length);

//EDIT THESE LINES TO MATCH YOUR SETUP
#define MQTT_SERVER "192.168.1.1"  //you MQTT IP Address
#define mqtt_user "username" 
#define mqtt_password "password"
#define mqtt_port 1883
const char* ssid = "ssid";
const char* password = "password";
char const* switchTopic1 = "/test/switch1/";
char const* switchTopic2 = "/test/switch2/";
char const* switchTopic3 = "/test/switch3/";
char const* switchTopic4 = "/test/switch4/";
char const* switchconfirmTopic1 = "/test/switchConfirm1/";
char const* switchconfirmTopic2 = "/test/switchConfirm2/";
char const* switchconfirmTopic3 = "/test/switchConfirm3/";
char const* switchconfirmTopic4 = "/test/switchConfirm4/";
char const* buttonTopic1 = "/test/button1/";
char const* buttonTopic2 = "/test/button2/";
char const* buttonTopic3 = "/test/button3/";
char const* buttonTopic4 = "/test/button4/";


//EJ: Data PIN Assignment on WEMOS D1 R2 https://www.wemos.cc/product/d1.html
// if you are using Arduino UNO, you will need to change the "D1 ~ D4" with the corresponding UNO DATA pin number 

const int switchPin1 = D0;
const int switchPin2 = D1;
const int switchPin3 = D2;
const int switchPin4 = D3;
const int led = D4;
const int buttonPin1 = D5;
const int buttonPin2 = D6;
const int buttonPin3 = D7;
const int buttonPin4 = D8;

// setup for input 1
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

int lastButtonState1 = 0;
int lastButtonState2 = 0;
int lastButtonState3 = 0;
int lastButtonState4 = 0;

char msg01[20];
char msg02[20];
char msg03[20];
char msg04[20];

//EJ: These are the MQTT Topic that will be used to manage the state of Relays 1 ~ 4
//EJ: Refer to my YAML component entry
//EJ: feel free to replicate the line if you have more relay switch to control, but dont forget to increment the number suffix so as increase switch logics in loop()


WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, mqtt_port, callback, wifiClient);

`void setup() {`
  //initialize the switch as an output and set to HIGH (relay off)
  pinMode(switchPin1, OUTPUT); // Relay Switch 1
  digitalWrite(switchPin1, HIGH);

  pinMode(switchPin2, OUTPUT); // Relay Switch 2
  digitalWrite(switchPin2, HIGH);

  pinMode(switchPin3, OUTPUT); // Relay Switch 3
  digitalWrite(switchPin3, HIGH);

  pinMode(switchPin4, OUTPUT); // Relay Switch 4
  digitalWrite(switchPin4, HIGH);
  
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  ArduinoOTA.setHostname("My Arduino WEMO"); // A name given to your ESP8266 module when discovering it as a port in ARDUINO IDE
  ArduinoOTA.begin(); // OTA initialization

  //start the serial line for debugging
  Serial.begin(115200);
  delay(100);

  //start wifi subsystem
  WiFi.begin(ssid, password);
  //attempt to connect to the WIFI network and then connect to the MQTT server
  reconnect();

  //wait a bit before starting the main loop
      delay(2000);
}

void loop(){

  //reconnect if connection is lost
  if (!client.connected() && WiFi.status() == 3) {reconnect();}

  //maintain MQTT connection
  client.loop();

  //MUST delay to allow ESP8266 WIFI functions to run
  delay(10); 
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);  
    if (buttonState1 != lastButtonState1)
    {
      digitalWrite(led, LOW);
      Serial.println("buttonState1");
      Serial.println(buttonState1);
      snprintf(msg01, 75, "%ld", buttonState1);
      client.publish(buttonTopic1, msg01);
      lastButtonState1 = buttonState1;
      digitalWrite(led, HIGH);
    }
    if (buttonState2 != lastButtonState2)
    {
      digitalWrite(led, LOW);
      Serial.println("buttonState2");
      Serial.println(buttonState2);
      snprintf(msg02, 75, "%ld", buttonState2);
      client.publish(buttonTopic2, msg02);
      lastButtonState2 = buttonState2;
      digitalWrite(led, HIGH);
    }
    if (buttonState3 != lastButtonState3)
    {
      digitalWrite(led, LOW);
      Serial.println("buttonState3");
      Serial.println(buttonState3);
      snprintf(msg03, 75, "%ld", buttonState3);
      client.publish(buttonTopic3, msg03);
      lastButtonState3= buttonState3;
      digitalWrite(led, HIGH);
    }
    if (buttonState4 != lastButtonState4)
    {
      digitalWrite(led, LOW);
      Serial.println("buttonState4");
      Serial.println(buttonState4);
      snprintf(msg04, 75, "%ld", buttonState4);
      client.publish(buttonTopic4, msg04);
      lastButtonState4 = buttonState4;
      digitalWrite(led, HIGH);
    }
  ArduinoOTA.handle();
}

void callback(char* topic, byte* payload, unsigned int length) {

  //convert topic to string to make it easier to work with
  String topicStr = topic; 
  //EJ: Note:  the "topic" value gets overwritten everytime it receives confirmation (callback) message from MQTT

  //Print out some debugging info
  Serial.println("Callback update.");
  Serial.print("Topic: ");
  Serial.println(topicStr);
     
    if (topicStr == switchTopic1) 
    {

     //turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
     if (payload[0] == '1'){
       digitalWrite(switchPin1, LOW);
       client.publish(switchconfirmTopic1, "1");
       }

  //turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
 else if (payload[0] == '0'){
   digitalWrite(switchPin1, HIGH);
   client.publish(switchconfirmTopic1, "0");
   }
 }

 // EJ: copy and paste this whole else-if block, should you need to control more switches
 else if (topicStr ==switchTopic2) 
 {
 //turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
 if(payload[0] == '1'){
   digitalWrite(switchPin2, LOW);
   client.publish(switchconfirmTopic2, "1");
   }

  //turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
 else if (payload[0] == '0'){
   digitalWrite(switchPin2, HIGH);
   client.publish(switchconfirmTopic2, "0");
   }
 }
 else if (topicStr == switchTopic3) 
 {
 //turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
 if(payload[0] == '1'){
   digitalWrite(switchPin3, LOW);
   client.publish(switchconfirmTopic3, "1");
   }

  //turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
 else if (payload[0] == '0'){
   digitalWrite(switchPin3, HIGH);
   client.publish(switchconfirmTopic3, "0");
   }
 }
 else if (topicStr == switchTopic4) 
 {
 //turn the switch on if the payload is '1' and publish to the MQTT server a confirmation message
 if(payload[0] == '1'){
   digitalWrite(switchPin4, LOW);
   client.publish(switchconfirmTopic4, "1");
   }

  //turn the switch off if the payload is '0' and publish to the MQTT server a confirmation message
 else if (payload[0] == '0'){
   digitalWrite(switchPin4, HIGH);
   client.publish(switchconfirmTopic4, "0");
   }
 }
 }



void reconnect() {

//attempt to connect to the wifi if connection is lost
  if(WiFi.status() != WL_CONNECTED){
//debug printing
Serial.print("Connecting to ");
Serial.println(ssid);

//loop while we wait for connection
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

//print out some more debug once connected
Serial.println("");
Serial.println("WiFi connected");  
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
  }

  //make sure we are connected to WIFI before attemping to reconnect to MQTT
  if(WiFi.status() == WL_CONNECTED){
  // Loop until we're reconnected to the MQTT server
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");

  // Generate client name based on MAC address and last 8 bits of microsecond counter
  String clientName;
  clientName += "esp8266-";
  uint8_t mac[6];
  WiFi.macAddress(mac);
  clientName += macToStr(mac);

  //if connected, subscribe to the topic(s) we want to be notified about
  //EJ: Delete "mqtt_username", and "mqtt_password" here if you are not using any 
  if (client.connect((char*) clientName.c_str(),mqtt_user, mqtt_password)) {  //EJ: Update accordingly with your MQTT account 
    Serial.print("\tMQTT Connected");
    client.subscribe(switchTopic1);
    client.subscribe(switchTopic2);
    client.subscribe(switchTopic3);
    client.subscribe(switchTopic4);
    //EJ: Do not forget to replicate the above line if you will have more than the above number of relay switches
  }

  //otherwise print failed for debugging
  else{Serial.println("\tFailed."); abort();}
    }
  }
}

//generate unique name from MAC addr
String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

if (i < 5){
  result += ':';
}
  }

  return result;
}
