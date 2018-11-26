/*
  Calibration
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
  pinMode(4, OUTPUT);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  Serial.begin(9600);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);

  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue1 = analogRead(sensorPin1);    

    // record the maximum sensor value
    if (sensorValue1 > sensorMax1) {
      sensorMax1 = sensorValue1;
    }
  
//     record the minimum sensor value
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


  // signal the end of the calibration period
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void loop() {
  // read the sensor:
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);

  // apply the calibration to the sensor reading
  sensorValue1 = map(sensorValue1, sensorMin1, sensorMax1, 0, 150);
  sensorValue2 = map(sensorValue2, sensorMin2, sensorMax2, 0, 150);

  // in case the sensor value is outside the range seen during calibration
  sensorValue1 = constrain(sensorValue1, 0, 150);
  sensorValue2 = constrain(sensorValue2, 0, 150);

  // fade the LED using the calibrated value:
  analogWrite(4, sensorValue2);
  analogWrite(5, sensorValue1);

  if(j%1000 == 0) {
    Serial.print("Sensor Derecho: ");
    Serial.println(sensorValue1);
    Serial.print("Sensor Izquierdo: ");
    Serial.println(sensorValue2);
    j++;  
  } else {
    j++;
  }
}
