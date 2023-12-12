#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h" 
#define API_KEY ""
String data;
// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "" 
#define FIREBASE_AUTH ""
FirebaseData fbdo;
    float T = 0.00;
    float H = 0.00;
    float D = 0.00;
    int G = 0;
    int Ma = 0;
    int Me = 0;
    int P = 0;
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
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {

  if (Serial.available() > 0) { //Check if data is available to read
    data = Serial.readStringUntil('\n'); //Read data from serial port
    //Serial.println(data);
    
    int commaIndex1 = data.indexOf(','); //Find first comma
    int commaIndex2 = data.indexOf(',', commaIndex1 + 1); 
    int commaIndex3 = data.indexOf(',', commaIndex2 + 1); 
    int commaIndex4 = data.indexOf(',', commaIndex3 + 1); 
    int commaIndex5 = data.indexOf(',', commaIndex4 + 1); 
    int commaIndex6 = data.indexOf(',', commaIndex5 + 1); 
     T = data.substring(0, commaIndex1).toFloat();
     H = data.substring(commaIndex1 + 1, commaIndex2).toFloat();
     D = data.substring(commaIndex2 + 1, commaIndex3).toFloat();
     G = data.substring(commaIndex3 + 1, commaIndex4).toInt();
     Ma = data.substring(commaIndex4 + 1, commaIndex5).toInt();
     Me = data.substring(commaIndex5 + 1, commaIndex6).toInt();
     P = data.substring(commaIndex6+1).toInt();
  
  }
  if (Firebase.ready() && signupOK){
    Firebase.RTDB.setFloat(&fbdo, "data/temp",T);
    Firebase.RTDB.setFloat(&fbdo, "data/humid", H);
    Firebase.RTDB.setFloat(&fbdo, "data/dist", D);
    Firebase.RTDB.setInt(&fbdo, "data/gas", G);
    Firebase.RTDB.setInt(&fbdo, "data/mag", Ma);
    Firebase.RTDB.setInt(&fbdo, "data/metal", Me);
    Firebase.RTDB.setInt(&fbdo, "data/pump",P);
    }
}
