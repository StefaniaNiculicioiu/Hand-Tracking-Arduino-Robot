#include<NewPing.h>
#include<Servo.h>
#include<AFMotor.h>

#define RIGHT A2
#define LEFT A3

#define MAX_DISTANCE 100
#define TRIGGER_PIN A1
#define ECHO_PIN A0  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// AF_DCMotor motorname(portnum, freq) 
// port num - selects which channel (1-4) of the motor controller the motor will be connected to
// freq - selects the PWM frequency.  If no frequency is specified, 1KHz is used by default.

AF_DCMotor Motor1(1,MOTOR12_1KHZ); // constructor for DC motor 1
AF_DCMotor Motor4(4,MOTOR34_1KHZ); // constructor for DC motor 2

Servo myservo;
 
int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  for(pos = 90; pos <= 180; pos += 1){
    myservo.write(pos);
    delay(15);
  }
  
  for(pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  
  for(pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
}

void loop() {
  delay(50);
  unsigned int distance = sonar.ping_cm();
  Serial.print("distance");
  Serial.println(distance);

  
  int Right_Value = digitalRead(RIGHT);
  int Left_Value = digitalRead(LEFT);
  
  Serial.print("RIGHT");
  Serial.println(Right_Value);
  Serial.print("LEFT");
  Serial.println(Left_Value);
  
  if((Right_Value == 1) && (distance >= 10 && distance <= 30)&&(Left_Value == 1)){  // move forward if we keep the hand in front of the ultrasonic sensor  
    Motor1.setSpeed(120);
    Motor1.run(FORWARD);
    Motor4.setSpeed(120);
    Motor4.run(FORWARD);
  }
  else if((Right_Value == 0) && (Left_Value == 1)) {  // move right 
    Motor1.setSpeed(200);
    Motor1.run(FORWARD);
    Motor4.setSpeed(100);
    Motor4.run(BACKWARD);
  }
  else if((Right_Value == 1)&&(Left_Value == 0)) {  // move left
    Motor1.setSpeed(100);
    Motor1.run(BACKWARD);
    Motor4.setSpeed(200);
    Motor4.run(FORWARD);
  }
  else if((Right_Value == 1)&&(Left_Value == 1)) {  // stop if no hand gesture is detected or if the distance > 30
    Motor1.setSpeed(0);
    Motor1.run(RELEASE);
    Motor4.setSpeed(0);
    Motor4.run(RELEASE);
  }
  else if(distance > 1 && distance < 10) {  // stop gesture - if the hand is placed right in front of the ultrasonic sensor 
    Motor1.setSpeed(0);
    Motor1.run(RELEASE);
    Motor4.setSpeed(0);
    Motor4.run(RELEASE);
  }
 }
