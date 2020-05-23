#include <MicroGear.h>
#include <WiFi.h>
#include <DHT.h>

const char* ssid     = "FANCIA_2.4G";
const char* password = "NAVINASAWIN";

#define APPID   "iotproject1234"
#define KEY     "1hSwWjllFpQhqjy"
#define SECRET  "YNvylCG5XQe9DqCnlghTKJ02G"
#define ALIAS   "ESP32"
#define DHTTYPE DHT11

uint8_t DHTPin = 27; 
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;

const int sensor = 35;
 int val = 0; 
const int trigPin = 2;
const int echoPin = 5;
long duration;
int distance;
// const int vulu = 2;
// int lightInit;
// int lightVal;


WiFiClient client;
int timer = 0;
MicroGear microgear(client);

/* If a new message arrives, do this */
void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);

//  microgear.publish("/Sensor/try","56",true);

  int pot = dht.readTemperature();
  delay(1000);
  int pot1 = dht.readHumidity();
  delay(1000);

//  val = analogRead(potPin);
//  delay(500);
  int volu = 0;
  long confirm = digitalRead(sensor);
  int lighting =0;
  
  
 if(pot>=32){

  microgear.chat("Sensor/tempu","danger");
  microgear.publish("/will42/project","danger");
  Serial.print ("Push notification sent ->");
  microgear.chat("Sensor/temperature", pot);
 }else{
   microgear.chat("Sensor/temperature", pot);
  
 }
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print(distance);
  Serial.println(" cm");
  if(distance<=50){
    microgear.chat("Sensor/distance","someone just passed by !!ALERTTTTT");
    delay(100);
    microgear.chat("Sensor/distance1",distance);
  }else if(distance <= 200 && distance >= 50){
    microgear.chat("Sensor/distance","something  is  very wrong at home");
    delay(200);
    microgear.chat("Sensor/distance1",distance);
    
  }else {
//    microgear.chat("Sensor/distance","everything is fine ");
//        delay(1000);
    microgear.chat("Sensor/distance1",distance);
    
    
  }




 
  
  microgear.chat("Sensor/humidity",pot1);
   
    Serial.print ("Push notification sent ->");
//  delay(1000);
//  microgear.chat("Sensor/Sound",val);
  if(confirm==HIGH){
    volu  = 1;
    microgear.chat("Sensor/Motion",1);
    microgear.chat("Sensor/deet","Motion detected");
    microgear.chat("Sensor/deetu","Motion detected");
    
  }else{
    volu=0;
    microgear.chat("Sensor/Motion",0);
    microgear.chat("Sensor/deet","Motion  Not detected");
    
  }
  delay(2000);
  
  
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
  
//delay(500);
    
  
  
  
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
  Serial.println("Connected to NETPIE...");
  /* Set the alias of this microgear ALIAS */
  microgear.setAlias(ALIAS);
}


void setup() {
  /* Add Event listeners */
  pinMode(DHTPin, INPUT);
//  pinMode(potPin, INPUT);
  pinMode(sensor, INPUT);
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  

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
      Serial.print(".");
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
    Serial.println("connected");

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
