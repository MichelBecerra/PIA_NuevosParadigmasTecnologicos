#include "motor.h"
#include "ultrasonico.h"
#include <Servo.h>


// Infrarojo
const int sensorPin1 = A0;    // pin that the sensor is attached to
const int sensorPin2 = A1;    // pin that the sensor is attached to

int j = 0;
int sensorValue1 = 0;         // the sensor value
int sensorValue2 = 0;         // the sensor value
int sensorMin1 = 1000;        // minimum sensor value
int sensorMax1 = 0;           // maximum sensor value
int sensorMin2 = 1000;        // minimum sensor value
int sensorMax2 = 0;           // maximum sensor value

// MOTOR
Motor myMotor;

// SERVO
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int pos1 = 0;    // variable to store the servo1 position
int pos2 = 0;    // variable to store the servo2 position

const int pinServo1 = 11;
const int pinServo2 = 10;

// LEDS
const int LEDD = 4;     // LED INDICADOR DE SENSOR DERECHO
const int LEDI = 5;     // LED INDICADOR DE SENSOR IZQUIERDIO

//ULTRASONICO
Ultrasonico myUltrasonic;
int ultraSonicValue = 0;

void setup(){
  // SERIAL
  Serial.begin(9600);
  // MOTORES
  myMotor.SETUP();
  // LEDS
  pinMode(LEDD, OUTPUT);
  pinMode(LEDI, OUTPUT);
  digitalWrite(LEDI, LOW);
  digitalWrite(LEDD, LOW);
  // ULTRASONICO
  myUltrasonic.SETUP();
  // SERVO
  myservo1.attach(pinServo1);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(pinServo2);
  startPosition();

  // Infrarojo
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);  
  calibration();
}

void loop(){    
  myservo1.write(80);
  myservo1.write(90);
  digitalWrite(LEDI, LOW);
  digitalWrite(LEDD, LOW);
 
  // read the sensor:
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);

  // apply the calibration to the sensor reading
  sensorValue1 = map(sensorValue1, sensorMin1, sensorMax1, 0, 150);
  sensorValue2 = map(sensorValue2, sensorMin2, sensorMax2, 0, 150);

  // in case the sensor value is outside the range seen during calibration
  sensorValue1 = constrain(sensorValue1, 0, 150);
  sensorValue2 = constrain(sensorValue2, 0, 150);

  if(sensorValue1 >= 75 && sensorValue2>=75){
    myMotor.Adelante();  
  } else if(sensorValue1 >= 75){
    myMotor.Izquierda();
  } else if(sensorValue2 >= 75){
    myMotor.Derecha();
  } else {
    myMotor.Detener();  
  }

  delay(100);

  // ULTRASONICO
  int uSV = 1000;
  int left_distance = 0; 
  int right_distance = 0;

  uSV = myUltrasonic.Lectura();

  if(uSV <= 15){
    myMotor.Detener();
    // Mirar hacia la izquierda
    lookLeft();       
    left_distance = myUltrasonic.Lectura();
    Serial.print("\nLeft_Side: ");
    Serial.print(left_distance);

    lookRight();   
    right_distance = myUltrasonic.Lectura(); 
    Serial.print("\nRight_Side: ");
    Serial.print(right_distance);
    uSV = 1000;

    ultraSonic_Turning(left_distance, right_distance);
  } 
  uSV = 1000;
  
  myMotor.Adelante();
  
}

void startPosition(){
  myservo2.write(0);
  for (pos2 = 0; pos2 <= 90; pos2 += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}


void lookLeft(){
  for (pos2 = 90; pos2 >= 0; pos2 -= 5) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo1.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
  }  
}

int lookRight(){
  for (pos2 = 90; pos2 <= 180; pos2 += 5) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo1.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
  }
}

void ultraSonic_Turning(int left, int right){
  if(left > right){
    digitalWrite(LEDI, HIGH);
    digitalWrite(LEDD, LOW);
    myMotor.Izquierda();     
  } else if(left < right){
    digitalWrite(LEDI, LOW);
    digitalWrite(LEDD, HIGH);
    myMotor.Derecha();    
  }
  myservo1.write(90);
  delay(1000);
  digitalWrite(LEDI, LOW);
  digitalWrite(LEDD, LOW);
  myMotor.Detener();
}


void calibration(){
   // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue1 = analogRead(sensorPin1);    

    // record the maximum sensor value
    if (sensorValue1 > sensorMax1) {
      sensorMax1 = sensorValue1;
    }
  
    //   record the minimum sensor value
    if (sensorValue1 < sensorMin1) {
      sensorMin1 = sensorValue1;
    }
    
  }

  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  while (millis() < 10000) {
    sensorValue2 = analogRead(sensorPin2);

    if (sensorValue2 > sensorMax2) {
      sensorMax2 = sensorValue2;
    }
    //  record the minimum sensor value
    if (sensorValue2 < sensorMin2) {
      sensorMin2 = sensorValue2;
    }
  }
}
