#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN A0
#define ECHO_PIN A1
#define motor1a 7
#define motor1b 8
#define motor2a 11
#define motor2b 12
#define motor1en 5
#define motor2en 6
#define pirSwitch 9
#define speed 230
#define MAX_DISTANCE 500
Servo servo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void setup() {
  Serial.begin(9600);
  servo.attach(3);
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
  pinMode(motor1en, OUTPUT);
  pinMode(motor2en, OUTPUT);
  pinMode(pirSwitch, OUTPUT);
  digitalWrite(pirSwitch,HIGH);
  servo.write(90);
}
void loop() {
  delay(50);
  // moveForward();
  int dist=sonar.ping_cm();
  Serial.println(dist);
  if (dist !=0 && dist<6){
  stop();
  delay(700);
  moveBackward();
  delay(200);
  stop();
  digitalWrite(pirSwitch,LOW);
  delay(5000);
  digitalWrite(pirSwitch,HIGH);
  drive();
  delay(500);
}
else{
  moveForward();
}}
void rotateServo(int angle) {
  servo.write(angle);
   
}
void drive(){
  delay(50);
  int frontDistance = sonar.ping_cm();
  int leftDistance, rightDistance;
  rotateServo(180);
  delay(500);
  leftDistance = sonar.ping_cm();
  rotateServo(0);
  delay(500);
  rightDistance = sonar.ping_cm();
  rotateServo(90);
  // if (rightDistance < 30) {
  //   moveForward();
  // }
  if(rightDistance>leftDistance){
    turnRight();
    delay(500);
    stop();

  }
  if(rightDistance<leftDistance){
    turnLeft();
    delay(500);
    stop();
  }
  if(rightDistance==leftDistance){
    moveBackward();
    delay(500);
    stop();
  }
}
void moveForward() {
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);
  
  analogWrite(motor1en, speed);
  analogWrite(motor2en, 200);
}


void moveBackward() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, HIGH);
  
  analogWrite(motor1en, speed);
  analogWrite(motor2en, speed);
}


void turnRight() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, HIGH);
  digitalWrite(motor2a, HIGH);
  digitalWrite(motor2b, LOW);
 
  analogWrite(motor1en, speed);
  analogWrite(motor2en, speed);
}


void turnLeft() {
  digitalWrite(motor1a, HIGH);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, HIGH);
  analogWrite(motor1en, speed);
  analogWrite(motor2en, speed);
}
void stop() {
  digitalWrite(motor1a, LOW);
  digitalWrite(motor1b, LOW);
  digitalWrite(motor2a, LOW);
  digitalWrite(motor2b, LOW);
  analogWrite(motor1en, 0);
  analogWrite(motor2en, 0);
}
