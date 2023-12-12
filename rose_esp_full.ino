#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 5   
#define DHTTYPE DHT11 
#include <HCSR04.h>
#define metal 15
UltraSonicDistanceSensor distanceSensor(13, 12); 
float temp = 0.0;
float humid = 0.0;
float dist = 0.0;
float val = 0.0;
int meta = 0;
DHT dht ( DHTPIN, DHTTYPE ); 
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h" 
#define API_KEY ""
String data;
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "" 
#define FIREBASE_AUTH ""

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
void setup() {
Serial.begin(115200);
  WiFiManager wm;
bool res;
res = wm.autoConnect("Spybot");
        config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  pinMode(14,INPUT);
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  dht.begin();
  pinMode(metal,INPUT);
}

void loop() {

temp = dht.readTemperature();
humid = dht.readHumidity();
dist = distanceSensor.measureDistanceCm();
val = map(analogRead(A0),0,1023,0,100);
if(digitalRead(metal)==HIGH)
{
  meta = 1;
  }
  else
  {
    meta = 0;
    }
  if (Firebase.ready() && signupOK){
    Firebase.RTDB.setFloat(&fbdo, "data/temp",temp);
    delay(50);
    Firebase.RTDB.setFloat(&fbdo, "data/humid", humid);
    delay(50);
    Firebase.RTDB.setFloat(&fbdo, "data/dist", dist);
    delay(50);
    Firebase.RTDB.setFloat(&fbdo, "data/gas", val); 
    delay(50);
    Firebase.RTDB.setInt(&fbdo, "data/metal", meta);
    delay(50);

    }
}
