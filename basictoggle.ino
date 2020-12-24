#include <MicroGear.h>
#include <WiFi.h>
#include <DHT.h>
#include <EasyBuzzer.h>
#include <NewPing.h>
#include "sonar.h"
const char* ssid     = "*** Wifi Name";
const char* password = "*** Wifi Password";

#define APPID   "iotproject1234"
#define KEY     "1hSwWjllFpQhqjy"
#define SECRET  "YNvylCG5XQe9DqCnlghTKJ02G"
#define ALIAS   "ESP32"
#define DHTTYPE DHT11

uint8_t DHTPin = 27;
DHT dht(DHTPin, DHTTYPE);
const int kPin_Photocell = 13;//light ///will change pin values
int sensorPin = 14; //fire  // will change pin values
int sensorsval = 0;
int Flame = HIGH;
float Temperature;
float Humidity;
const int sensor = 35;
int val = 0;
const int TRIGGER_PIN = 2;
const int ECHO_PIN = 5;
const int MAX_DISTANCE = 100;
const int Sound = 34;
long duration;
int distance;
const int buzz =33; 
int count = 0;
char state = 0;
char stateOutdated = 0;
char buff[16];
const float dist = {0.0};
int prediction = 0;

WiFiClient client;
int timer = 0;
MicroGear microgear(client);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void sendState(){
 if (state==0) {
 microgear.chat("Sensor/buzz","0");
 }else{
 microgear.chat("Sensor/buzz","1");
 Serial.println("send state..");
 stateOutdated = 0;
 }
}
void updateIO(){
 if (state >= 1) {
 EasyBuzzer.singleBeep(1000,200);
 }
 else {
 state = 0;
 EasyBuzzer.stopBeep();
 }
}

int predicted(int distance) {
  const float dist[][1] = {{distance/100.0}};
  Serial.print("normalized=");
  Serial.println(distance/100.0);
  prediction = sonar_predict(dist[0], 1);
}

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  char m = *(char *)msg;
  Serial.println(m);
  msg[msglen] = '\0';

  
  if (m == '0' || m == '1') {
    state = m=='0'?0:1;
    updateIO();
  } 
  if (m == '0' || m == '1' || m == '?') stateOutdated = 1;
  

  
  int distance = sonar.ping_cm();
   Serial.print(distance);
   Serial.println("cm");
  int confirm = digitalRead(sensor);
   microgear.chat("Sensor/distance1",distance);
   if (confirm == HIGH) {
    microgear.chat("Sensor/Motion", 1);
    microgear.chat("Sensor/deet", "Motion detected");
    Serial.print("Movement detected");
//    delay(2000);
    //    microgear.chat("Sensor/deetu","Motion detected");

  } else {
    microgear.chat("Sensor/Motion", 0);
    microgear.chat("Sensor/deet", "Motion  Not detected");
//    delay(2000);
  }
  int pot = dht.readTemperature();
  delay(1000);
  int pot1 = dht.readHumidity();
  delay(1000);

  //  val = analogRead(potPin);
  //  delay(500);
  
  int lighting = 0;

  microgear.chat("Sensor/temperature", pot);

//  Flame = digitalRead(sensorPin);
//  if (Flame==LOW){
//    Serial.println("Fire Detected Run");
//    microgear.chat("Sensor/aag","Fire Detected");
////    delay(10000);
//  }else{
//    Serial.println("No Fire");
//    microgear.chat("Sensor/aag","No Fire");
//  }
// 
//  int value = analogRead(kPin_Photocell);
//   if(value<200){
//    microgear.chat("Sensor/light11","Light off");
//    Serial.println(value);
//  }else{
//    microgear.chat("Sensor/light11","Light on");
//    Serial.println(value);
//  }
//  
  


  val = analogRead(Sound);
  Serial.println(val, DEC);
  if (val >= 150) {
    microgear.chat("Sensor/sound", val);
    //  microgear.chat("Sensor/sound", "Sound detected");
    delay(1000);
  } else {
    microgear.chat("Sensor/sound", val);
    delay(1000);
  }

  microgear.chat("Sensor/humidity", pot1);

  //    Serial.print ("Push notification sent ->");
  //  delay(1000);
  //  microgear.chat("Sensor/Sound",val);
 



  // lightVal = analogRead(vulu);
  ////  lighting = analogRead(vulu);
  // if(lightVal - lightInit < 50)
  //  {
  //      lighting = 0;
  //      microgear.chat("Sensor/light",0);
  //  }else{
  //    lighting=1;
  //    microgear.chat("Sensor/light",1);
  //  }

  if(confirm==HIGH  && distance<=30){
    
    count = count+1;
    microgear.chat("Sensor/Detection","Person Detected");
    Serial.print("Someone detected:");
    Serial.print("Distance="+distance);
//    Serial.print("Sound Level="+val);
    Serial.print("Motion= True");
    
   
    microgear.publish("/will42/project","Person detected");
    microgear.publish("/@push/owner","Intruder detected");            
    Serial.print ("Push notification sent ->");
//    digitalWrite(buzz, HIGH);
    EasyBuzzer.singleBeep(1000,200);
//    delay(2000);
  }else{
    microgear.chat("Sensor/Detection","Person Not Detected");
//    digitalWrite(buzz, LOW);
    EasyBuzzer.stopBeep();
  }
  microgear.chat("Sensor/countar",count);

 predicted(distance);
 
 if (prediction == 1 && confirm == HIGH) {
  microgear.chat("Sensor/Detection2","Person Detected");
  microgear.publish("/@push/owner","Intruder detected!"); 
//    Serial.print("Someone detected:");
//    Serial.print("Distance="+distance);
//    Serial.print("Motion= True");
      Serial.println(prediction);
//    microgear.publish("/will42/project","Person detected");
//    microgear.publish("/@push/owner","Intruder detected");            
//    Serial.print ("Push notification sent ->");
    EasyBuzzer.singleBeep(1000,200);
//    delay(2000);
 } else {
  microgear.chat("Sensor/Detection2","Person Not Detected");
    EasyBuzzer.stopBeep();
 }

  
}
void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Found new member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.print("Lost member --> ");
  for (int i = 0; i < msglen; i++)
    Serial.print((char)msg[i]);
  Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  //  Serial.println("Connected to NETPIE...");
  /* Set the alias of this microgear ALIAS */
  microgear.setAlias(ALIAS);
}


void setup() {
  /* Add Event listeners */
  pinMode(DHTPin, INPUT);
  //  pinMode(potPin, INPUT);
  pinMode(sensor, INPUT);
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
  pinMode(Sound, INPUT) ;
  EasyBuzzer.setPin(buzz);
  //  lightInit = analogRead(vulu);

  dht.begin();
  /* Call onMsghandler() when new message arraives */
  microgear.on(MESSAGE, onMsghandler);

  /* Call onFoundgear() when new gear appear */
  microgear.on(PRESENT, onFoundgear);

  /* Call onLostgear() when some gear goes offline */
  microgear.on(ABSENT, onLostgear);

  /* Call onConnected() when NETPIE connection is established */
  microgear.on(CONNECTED, onConnected);

  Serial.begin(115200);
  Serial.println("Starting...");

  /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
  /* You may want to use other method that is more complicated, but provide better user experience */
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      //      Serial.print(".");
    }
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /* Initial with KEY, SECRET and also set the ALIAS here */
  microgear.init(KEY, SECRET, ALIAS);

  /* connect to NETPIE to a specific APPID */
  microgear.connect(APPID);

}

void loop() {
  /* To check if the microgear is still connected */
  if (microgear.connected()) {
//        Serial.println("connected");
    if (stateOutdated) sendState();
    /* Call this method regularly otherwise the connection may be lost */
    microgear.loop();

    if (timer >= 1000) {
            Serial.println("Publish...");

      /* Chat with the microgear named ALIAS which is myself */
      microgear.chat(ALIAS, "Hello");
      timer = 0;

    }
    else timer += 100;
  }
  else {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000) {
      microgear.connect(APPID);
      timer = 0;
    }
    else timer += 100;
  }
  delay(100);

}
