
int left_track = 7;
int right_track = A1;
int center_track = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(left_track,INPUT); // Left track
  pinMode(center_track,INPUT); // Center Track
  pinMode(right_track,INPUT); // Right Track

  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);

  int right_value, center_value, left_value = 1;
  int black = 1;

}

void loop() {
   
  // put your main code here, to run repeatedly:
  LineTracing();
  left_value = digitalRead(left_track);
//   Serial.print("\n Left Tracking Value:" );
//   Serial.print(left_value);
   center_value = digitalRead(center_track);
//   Serial.print("\n Center Tracking Value:" );
//   Serial.print(center_value);
   right_value = digitalRead(right_track);
//   Serial.print("\n Right Tracking Value:" );
//   Serial.print(right_value);
//   Serial.print("\n");
//  
   if(center_value == black &&(right_value!=black && left_value !=black )){
      MoveForward(105);
   }
   else if(left_value !=  black &&(right_value == black && center_value == black)){
      RotateLeft(120);
   }
   else if(right_value != black && (left_value == black && center_value == black)){
      RotateRight(120); 
   }
   else if(right_value == black && (left_value != black && center_value != black)){
      RotateRight(95); 
   }
   else if(left_value ==  black &&(right_value != black && center_value != black)){
      RotateLeft(95);
   }
   else{
      Stop(); 
   }
}


void MoveForward(int speed){
   digitalWrite(2, HIGH);
   analogWrite(5, speed);
   digitalWrite(4, LOW);
   analogWrite(6, speed);
}

void RotateLeft(int speed){

  digitalWrite(2, LOW);
  analogWrite(5, speed+30);
  digitalWrite(4, LOW);
  analogWrite(6, speed+30);
    
}

void RotateRight(int speed){

  digitalWrite(2, HIGH);
  analogWrite(5, speed+30);
  digitalWrite(4, HIGH);
  analogWrite(6, speed+30);
    
}

void Stop(){
  digitalWrite(2, LOW);
  analogWrite(5, 0);
  digitalWrite(4, LOW);
  analogWrite(6, 0);
}

