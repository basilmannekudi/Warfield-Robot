#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(A0, A1);

Servo servo_1;
Servo servo_2;

int int1 = 2;
int int2 = 3;
int int3 = 4;
int int4 = 5;
int pump = 8;

int state;
int speed = 130;

int pos1 = 90;
int pos2 = 10;

void setup(){
servo_1.attach(10);
servo_2.attach(9);
servo_1.write(pos1); 
servo_2.write(pos2); 


pinMode(int1, OUTPUT);
pinMode(int2, OUTPUT);
pinMode(int3, OUTPUT);
pinMode(int4, OUTPUT);
pinMode(pump, OUTPUT);



Serial.begin(9600);
BT.begin(9600); // Setting the baud rate of Software Serial Library 
 
 delay(1000);
 }

void loop(){
//if some date is sent, reads it and saves in state
if(BT.available() > 0){     
state = BT.read(); 

if(state > 15){speed = state;}      
}

    
   // if the state is '1' the DC motor will go forward
if (state == 1){forword();}

// if the state is '2' the motor will Backword
else if (state == 2){backword();}
    
// if the state is '3' the motor will turn left
else if (state == 3){turnLeft();}
    
// if the state is '4' the motor will turn right
else if (state == 4){turnRight();}
    
// if the state is '5' the motor will Stop
else if (state == 5) {stop();}    

else if (state == 6) {if(pos1<170){pos1 = pos1+1;}} 
else if (state == 7) {if(pos1>10){pos1 = pos1-1;}} 
else if (state == 8) {    if(pos2>0){pos2 = pos2-3;}}  
else if (state == 9) { if(pos2<60){pos2 = pos2+3;}} 

else if (state == 10){ digitalWrite(pump, HIGH);} 
else if (state == 11){ digitalWrite(pump, LOW);} 
Serial.println(pos1);
servo_1.write(pos1); 
servo_2.write(pos2); 


}


void stop(){
    digitalWrite(int1, LOW);
    digitalWrite(int2, LOW); 
    digitalWrite(int3, LOW);
    digitalWrite(int4, LOW);
}

void forword(){
    digitalWrite(int1, LOW);
    digitalWrite(int2, HIGH); 
    digitalWrite(int3, LOW);
    digitalWrite(int4, HIGH);  
}

void backword(){
    digitalWrite(int1, HIGH);
    digitalWrite(int2, LOW); 
    digitalWrite(int3, HIGH);
    digitalWrite(int4, LOW);   
}


void turnRight(){
    digitalWrite(int1, LOW);
    digitalWrite(int2, HIGH); 
    digitalWrite(int3, HIGH);
    digitalWrite(int4, LOW);  
}

void turnLeft(){
    digitalWrite(int1, HIGH);
    digitalWrite(int2, LOW); 
    digitalWrite(int3, LOW);
    digitalWrite(int4, HIGH); 
}
