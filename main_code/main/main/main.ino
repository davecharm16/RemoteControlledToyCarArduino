#include <Servo.h>

String BLE_val;
boolean MoveForward_Flag;
boolean MoveLeft_Flag;
boolean MoveRight_Flag;
boolean MoveBackward_Flag;
int default_speed;
int claw_degrees;
int arm_degrees;
int base_degrees;

Servo myservo1;
Servo myservo2;
Servo myservo3;

void setup(){
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  claw_degrees = 90;//initialize the angle value of claw servo 1
  arm_degrees = 90;//initialize the angle value of arm servo 2
  base_degrees = 90;//initialize the angle value of base servo 3

  myservo1.write(claw_degrees);
  delay(500);
  myservo2.write(arm_degrees);
  delay(500);
  myservo3.write(base_degrees);
  delay(500);
  Stop();

  
  BLE_val = "";
  MoveForward_Flag = false;
  MoveLeft_Flag = false;
  MoveRight_Flag = false;
  MoveBackward_Flag = false;

  default_speed =130;
}

void loop(){
  while (Serial.available() > 0) {
    BLE_val = BLE_val + ((char)(Serial.read()));
    delay(2);
  }
  if (0 < String(BLE_val).length() && 2 >= String(BLE_val).length()) {
    Serial.println(BLE_val);
    switch (String(BLE_val).charAt(0)) {
     case 'F':
      MoveForward_Function();
      break;
     case 'L':
      MoveLeft_Function();
      break;
     case 'R':
      MoveRight_Function();
      break;
     case 'B':
      MoveBackward_Function();
      break;
     
    }
    BLE_val = "";
  }
  else{
    BLE_val = "";  
  }
}

void MoveForward_Function(){
   MoveForward_Flag = true;
   while(MoveForward_Flag){
    MoveForward(default_speed);
      if(Serial.read() == 'S'){
        MoveForward_Flag = false;
        Stop();
      }
   }
}

void MoveLeft_Function(){
   MoveLeft_Flag = true;
   while(MoveLeft_Flag){
    MoveLeft(default_speed);
      if(Serial.read() == 'S'){
        MoveLeft_Flag = false;
        Stop();
      }
   }
}

void MoveRight_Function(){
   MoveRight_Flag = true;
   while(MoveRight_Flag){
    MoveRight(default_speed);
      if(Serial.read() == 'S'){
        MoveRight_Flag = false;
        Stop();
      }
   }
}

void MoveBackward_Function(){
   MoveBackward_Flag = true;
   while(MoveBackward_Flag){
    MoveBackward(default_speed);
      if(Serial.read() == 'S'){
        MoveBackward_Flag = false;
        Stop();
      }
   }
}

void MoveForward(int speed){
   digitalWrite(2,HIGH);
   analogWrite(5,speed);
   digitalWrite(4,LOW);
   analogWrite(6,speed);
}

void MoveLeft(int speed){
   digitalWrite(2,LOW);
   analogWrite(5,speed+30);
   digitalWrite(4,LOW);
   analogWrite(6,speed+30);
}

void MoveRight(int speed){
   digitalWrite(2,HIGH);
   analogWrite(5,speed+30);
   digitalWrite(4,HIGH);
   analogWrite(6,speed+30);
}

void MoveBackward(int speed){
   digitalWrite(2,LOW);
   analogWrite(5,speed);
   digitalWrite(4,HIGH);
   analogWrite(6,speed);
}

void Stop(){
   digitalWrite(2,LOW);
   analogWrite(5,0);
   digitalWrite(4,LOW);
   analogWrite(6,0);
}
