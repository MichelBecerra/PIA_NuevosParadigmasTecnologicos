/*
  Calibration

  Demonstrates one technique for calibrating sensor input. The sensor readings
  during the first five seconds of the sketch execution define the minimum and
  maximum of expected values attached to the sensor pin.

  The sensor minimum and maximum initial values may seem backwards. Initially,
  you set the minimum high and listen for anything lower, saving it as the new
  minimum. Likewise, you set the maximum low and listen for anything higher as
  the new maximum.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0
  - LED attached from digital pin 9 to ground

  created 29 Oct 2008
  by David A Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Calibration
*/

// These constants won't change:
const int sensorPin1 = A0;    // pin that the sensor is attached to
const int sensorPin2 = A1;    // pin that the sensor is attached to
const int ledPin = 4;        // pin that the LED is attached to

// variables:
int j = 0;
int sensorValue1 = 0;         // the sensor value
int sensorValue2 = 0;         // the sensor value
int sensorMin1 = 1000;        // minimum sensor value
int sensorMax1 = 0;           // maximum sensor value
int sensorMin2 = 1000;        // minimum sensor value
int sensorMax2 = 0;           // maximum sensor value


void setup() {
  // turn on LED to signal the start of the calibration period:
  pinMode(5, OUTPUT);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  Serial.begin(9600);
  digitalWrite(5, HIGH);

  // calibrate during the first five seconds
  while (millis() < 10000) {
    sensorValue1 = analogRead(sensorPin1);
    sensorValue2 = analogRead(sensorPin2);

    // record the maximum sensor value
    if (sensorValue1 > sensorMax1) {
      sensorMax1 = sensorValue2;
    }

    if (sensorValue2 > sensorMax2) {
      sensorMax2 = sensorValue1;
    }
    // record the minimum sensor value
    if (sensorValue1 < sensorMin1) {
      sensorMin1 = sensorValue1;
    }
    if (sensorValue2 < sensorMin2) {
      sensorMin2 = sensorValue2;
    }
  }

  // signal the end of the calibration period
  digitalWrite(4, LOW);
}

void loop() {
  // read the sensor:
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);

  // apply the calibration to the sensor reading
  sensorValue1 = map(sensorValue1, sensorMin1, sensorMax1, 0, 100);
  sensorValue2 = map(sensorValue2, sensorMin2, sensorMax2, 0, 100);

  // in case the sensor value is outside the range seen during calibration
  sensorValue1 = constrain(sensorValue1, 0, 1);
  sensorValue2 = constrain(sensorValue2, 0, 1);

  // fade the LED using the calibrated value:
  analogWrite(4, sensorValue1);
  analogWrite(5, sensorValue2);

  if(j%5000 == 0) {
    Serial.print("Sensor Derecho: ");
    Serial.println(sensorValue1);
    Serial.print("Sensor Izquierdo: ");
    Serial.println(sensorValue2);
    j++;  
  } else {
    j++;
  }
}
