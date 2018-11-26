#include "motor.h"
#include "Arduino.h"

const int motorD = 7;   // Motor Derecho Salida Digital      PIN 7 ----> 2  SN
const int motorDD = 6;  // Motor Derecho Salida Digital      PIN 6 ----> 7  SN
const int motorI = 9;   // Motor Izquierdo Salida Digital    PIN 8 ----> 10 SN
const int motorII = 8;  // Motor Izquierdo Salida Digital    PIN 9 ----> 15 SN	

Motor::Motor(){
}

void Motor::SETUP(){
    pinMode(motorI, OUTPUT);
    pinMode(motorII, OUTPUT);
    pinMode(motorD, OUTPUT);
    pinMode(motorDD, OUTPUT);
}

void Motor::Atras(){
    Serial.println("ATRAS");
    digitalWrite(motorI, LOW);
    digitalWrite(motorII, HIGH);

    digitalWrite(motorD, LOW);
    digitalWrite(motorDD, HIGH); 
}

void Motor::Adelante(){
    Serial.println("ADELANTE");
    analogWrite(motorI, 255);
    digitalWrite(motorII, LOW);

    analogWrite(motorD, 600);
    digitalWrite(motorDD, LOW);
    
}

void Motor::Detener(){
    Serial.println("DETENER");
    digitalWrite(motorI, LOW);
    digitalWrite(motorII, LOW);

    digitalWrite(motorD, LOW);
    digitalWrite(motorDD, LOW);
    
}

void Motor::Izquierda(){
    Serial.println("\nIZQUIERDA");
    digitalWrite(motorI, HIGH);
    digitalWrite(motorII, LOW);

    digitalWrite(motorD, LOW);
    digitalWrite(motorDD, LOW);
    
}

void Motor::Derecha(){
    Serial.println("\nDERECHA");
    digitalWrite(motorI, LOW);
    digitalWrite(motorII, LOW);

    digitalWrite(motorD, HIGH);
    digitalWrite(motorDD, LOW);
    
}	
