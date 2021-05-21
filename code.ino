#include <MsTimer2.h>

int vSpeed = 110;        // MAX 255
int turn_speed = 230;    // MAX 255 
int turn_delay = 10;
bool is_take_picture = false;


//L293 Connection   
const int motorA1      = 10;
const int motorA2      = 8;
const int motorB1      = 12;
const int motorB2      = 13;
const int moverobot   = 5;
const int takepicture = 6;

//Sensor Connection
const int left_sensor_pin =A0;
const int right_sensor_pin =A1;

int left_sensor_state;
int right_sensor_state;

void change(){
  is_take_picture = !is_take_picture;
  Serial.println("stop motion for picture");
  digitalWrite(motorA2,LOW);
  digitalWrite(motorA1,LOW);                       
  digitalWrite(motorB2,LOW);
  digitalWrite(motorB1,LOW);
    MsTimer2::stop();
}


void setup(){
  
  MsTimer2::set(3000, change); // 500ms period
  MsTimer2::start();
  
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  
  pinMode(takepicture, OUTPUT);
  pinMode(moverobot, INPUT);
  digitalWrite(moverobot, LOW);
  digitalWrite(takepicture, HIGH);

  Serial.begin(9600);
  delay(3000);
}

void loop() {
    while(is_take_picture){
      digitalWrite(takepicture, HIGH);
      while(!digitalRead(moverobot)){};
      MsTimer2::start();
      digitalWrite(takepicture, LOW);
     }
     
  left_sensor_state = analogRead(left_sensor_pin);
  right_sensor_state = analogRead(right_sensor_pin);
  
  if(right_sensor_state < 500 && left_sensor_state > 500)
  {
    Serial.println("turning right");
 
    digitalWrite (motorA1,LOW);
    digitalWrite(motorA2,HIGH);                       
    digitalWrite (motorB1,LOW);
    digitalWrite(motorB2,HIGH);
  }
  
  if(right_sensor_state > 500 && left_sensor_state < 500)
  {
    Serial.println("turning left");
    
    digitalWrite (motorA1,HIGH);
    digitalWrite(motorA2,LOW);                       
    digitalWrite (motorB1,HIGH);
    digitalWrite(motorB2,LOW);
  
    delay(turn_delay);
    }
  
  if(right_sensor_state < 500 && left_sensor_state < 500)
  {
    Serial.println("stop");
    digitalWrite(motorA2,LOW);
    digitalWrite(motorA1,LOW);                       
    digitalWrite(motorB2,LOW);
    digitalWrite(motorB1,LOW);
    delay(turn_delay);
  
    }
  
    if(right_sensor_state > 500 && left_sensor_state > 500){ 
        Serial.println("going forward");
        digitalWrite(motorA2,HIGH);
        digitalWrite(motorA1,LOW);                       
        digitalWrite(motorB2,LOW);
        digitalWrite(motorB1,HIGH);
      }

   

}










 
