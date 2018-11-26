#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo


int pos1 = 0;    // variable to store the servo position
int pos2 = 0;

const int pinServo1 = 11;
const int pinServo2 = 10;
#define IZQ 0
#define DER 1
// PINAJE
// MOTORES
const int motorD = 7;   // Motor Derecho Salida Digital      PIN 7 ----> 2  SN
const int motorDD = 6;  // Motor Derecho Salida Digital      PIN 6 ----> 7  SN
const int motorI = 9;   // Motor Izquierdo Salida Digital    PIN 8 ----> 10 SN
const int motorII = 8;  // Motor Izquierdo Salida Digital    PIN 9 ----> 15 SN

// LEDS
const int LEDD = 4;     // LED INDICADOR DE SENSOR DERECHO
const int LEDI = 5;     // LED INDICADOR DE SENSOR IZQUIERDIO

// SENDORES INFRAROJOS
const int sensorD=0;    // Sensor Infrarojo Derecho
const int sensorI=1;    // Sensor Infrarojo Izquierdo

// VALORES ANALOGOS DE SENSORES INFRAROJOS
int valorSensorD = 0;
int valorSensorI= 0;


int i = 0;
int norm1 = 0;
int norm2 = 0;

//ULTRASONICO
// defines pins numbers
const int trigPin = 3;
const int echoPin = 2;

// defines variables
long duration;
int distance;

void setup(){
  Serial.begin(9600);
  pinMode(motorI, OUTPUT);
  pinMode(motorII, OUTPUT);
  pinMode(motorD, OUTPUT);
  pinMode(motorDD, OUTPUT);
  pinMode(LEDD, OUTPUT);
  pinMode(LEDI, OUTPUT);
  pinMode(sensorD, INPUT);
  pinMode(sensorI, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  myservo1.attach(pinServo1);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(pinServo2);
  startPosition();
  
}

// 0-49 BLANCO
// 230-270 NEGRO

void loop(){
  int left_distance, right_distance;
  digitalWrite(LEDI, LOW);
  digitalWrite(LEDD, LOW);
  myservo1.write(80);
  myservo1.write(90);
  
  valorSensorD = binarizar(analogRead(sensorD), 600);
  valorSensorI = binarizar(analogRead(sensorI), 600);

  Serial.print("Sensor Derecho: ");
  Serial.println(valorSensorD);
  Serial.print("Sensor Izquierdo: ");
  Serial.println(valorSensorI);

  lectorLinea(valorSensorD, valorSensorI);
  
  if(!ultraLoop()){
    // Gira hacia la izquierda, despues derecha
    delay(1000);
    left_distance = lookLeft();
    right_distance = lookRight();
    delay(2000);
    
    if (left_distance >= right_distance){
      while (ultrasound() <= 15){
        Adelante();
        Adelante();
        Adelante();
        Derecha();
        Derecha();
        Derecha();
        delay(1000);
      }
    }
    else {
      while(ultrasound() <= 15){
        Adelante();
        Adelante();
        Adelante();
        Izquierda();
        Izquierda();
        Izquierda();
        delay(1000);
      }
    }
  }


}

int ultrasound(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  return distance;
}

void Atras(){
  Serial.println("ATRAS");
  digitalWrite(motorI, LOW);
  digitalWrite(motorII, HIGH);

  digitalWrite(motorD, LOW);
  digitalWrite(motorDD, HIGH); 
}

void Adelante(){
  Serial.println("ADELANTE");
  digitalWrite(motorI, HIGH);
  digitalWrite(motorII, LOW);

  digitalWrite(motorD, HIGH);
  digitalWrite(motorDD, LOW);
    
}

void Detener(){
  Serial.println("DETENER");
  digitalWrite(motorI, LOW);
  digitalWrite(motorII, LOW);

  digitalWrite(motorD, LOW);
  digitalWrite(motorDD, LOW);
    
}

void Derecha(){
  Serial.println("DERECHA");
  digitalWrite(motorI, HIGH);
  digitalWrite(motorII, LOW);

  digitalWrite(motorD, LOW);
  digitalWrite(motorDD, LOW);
    
}

void Izquierda(){
  Serial.println("IZQUIERDA");
  digitalWrite(motorI, LOW);
  digitalWrite(motorII, LOW);

  digitalWrite(motorD, HIGH);
  digitalWrite(motorDD, LOW);
    
}

void IzquierdaAtras(){
  Serial.println("IZQUIERDA");
  digitalWrite(motorI, LOW);
  digitalWrite(motorII, HIGH);

  digitalWrite(motorD, LOW);
  digitalWrite(motorDD, LOW);
    
}

void DerechaAtras(){
  Serial.println("DERECHA");
  digitalWrite(motorI, LOW);
  digitalWrite(motorII, LOW);

  digitalWrite(motorD, LOW);
  digitalWrite(motorDD, HIGH);
    
}

void startPosition(){
  myservo2.write(0);
  for (pos2 = 0; pos2 <= 90; pos2 += 1) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

int lookLeft(){
  for (pos2 = 90; pos2 >= 0; pos2 -= 5) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo1.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(500);
  distance = ultrasound();
  myservo1.write(90);
  Serial.print("IZQ: "); 
  Serial.print(distance);
  Serial.print('\n');
  return distance;
}

int lookRight(){
  for (pos2 = 90; pos2 <= 180; pos2 += 5) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    myservo1.write(pos2);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(500); 
  distance = ultrasound();
  myservo1.write(90);
  Serial.print("DER: ");
  Serial.print(distance);
  Serial.print('\n');
  return distance;
}


boolean ultraLoop(){
  distance = ultrasound();
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance <= 15){
    Detener();
    return false;
  } else {
    Atras();
    return true;  
  }
  return true;
}

void lectorLinea(int valorSensorD, int valorSensorI){
  static int memory = IZQ;
  Serial.print("LECTOR ACTIVADO");
  if(valorSensorD < valorSensorI){
    IzquierdaAtras();
    digitalWrite(LEDI, HIGH);
    digitalWrite(LEDD, LOW);
    memory = IZQ;
  }

  if(valorSensorD > valorSensorI){
    DerechaAtras();
    digitalWrite(LEDI, LOW);
    digitalWrite(LEDD, HIGH);
    memory = DER;
  }

  if (valorSensorD == valorSensorI && valorSensorD == 0){
    Atras();
    digitalWrite(LEDD, LOW);
    digitalWrite(LEDI, LOW);
  }
  else {
    if (memory == IZQ){
      IzquierdaAtras();
      digitalWrite(LEDI, HIGH);
      digitalWrite(LEDD, LOW);   
    }
    else{
      DerechaAtras();
      digitalWrite(LEDI, LOW);
      digitalWrite(LEDD, HIGH);
    }
  }
  
}

int binarizar(int value, int umbral){
  return value > umbral ? 255 : 0;
}
