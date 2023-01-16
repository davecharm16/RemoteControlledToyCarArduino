#include <Servo.h>

String BLE_val;

boolean MoveForward_Flag;
boolean MoveLeft_Flag;
boolean MoveRight_Flag;
boolean MoveBackward_Flag;
boolean ClawOpen_Flag;
boolean ClawClose_Flag;
boolean ClawUp_Flag;
boolean ClawDown_Flag;
boolean ClawLeft_Flag;
boolean ClawRight_Flag;

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
  base_degrees = 100;//initialize the angle value of base servo 3

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
     case 'c':
      ClawClose_Function();
      break;
     case 'o':
      ClawOpen_Function();
      break;
     case 'u':
      ClawUp_Function();
      break;
     case 'd':
      ClawDown_Function();
      break;
     case 'l':
      ClawLeft_Function();
      break;
     case 'r':
      ClawRight_Function();
      break;
      
    }
    BLE_val = "";
  }
  else{
    BLE_val = "";  
  }
}

void ClawLeft_Function(){
  ClawLeft_Flag = true;
  while(ClawLeft_Flag){
    base_degrees = base_degrees+1;
    myservo3.write(base_degrees);
    delay(10);
    if(base_degrees >= 180){
        base_degrees = 180;
    }
    if(Serial.read() == 's'){
      ClawLeft_Flag = false;  
    }
  }  
}

void ClawRight_Function(){
  ClawRight_Flag = true;
  while(ClawRight_Flag){
    base_degrees = base_degrees-1;
    myservo3.write(base_degrees);
    delay(10);
    if(base_degrees <= 0){
        base_degrees = 0;
    }
    if(Serial.read() == 's'){
      ClawRight_Flag = false;  
    }
  }  
}

void ClawDown_Function(){
  ClawDown_Flag = true;
  while(ClawDown_Flag){
    arm_degrees = arm_degrees+1;
    myservo2.write(arm_degrees);
    delay(10);
    if(arm_degrees >= 150){
        arm_degrees = 150;
    }
    if(Serial.read() == 's'){
      ClawDown_Flag = false;  
    }
  }  
}

void ClawUp_Function(){
  ClawUp_Flag = true;
  while(ClawUp_Flag){
    arm_degrees = arm_degrees-1;
    myservo2.write(arm_degrees);
    delay(10);
    if(arm_degrees <= 20){
        arm_degrees = 20;
    }
    if(Serial.read() == 's'){
      ClawUp_Flag = false;  
    }
  }  
}


void ClawClose_Function(){
  ClawClose_Flag = true;
  while(ClawClose_Flag){
    claw_degrees = claw_degrees+1;
    myservo1.write(claw_degrees);
    delay(10);
    if(claw_degrees >= 180){
        claw_degrees = 180;
    }
    if(Serial.read() == 's'){
      ClawClose_Flag = false;  
    }
  }  
}

void ClawOpen_Function(){
  ClawOpen_Flag = true;
  while(ClawOpen_Flag){
    claw_degrees = claw_degrees-1;
    myservo1.write(claw_degrees);
    delay(10);
    if(claw_degrees <= 90){
        claw_degrees = 90;
    }
    if(Serial.read() == 's'){
      ClawOpen_Flag = false;  
    }
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
