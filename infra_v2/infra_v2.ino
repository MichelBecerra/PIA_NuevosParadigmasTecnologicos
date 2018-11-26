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
}

void loop() {
  // read the sensor:
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);

  Serial.print(binarizar(sensorValue1, 600));
  Serial.print(" ");
  Serial.println(binarizar(sensorValue2, 600));
  delay(100);
  
  
}

int binarizar(int value, int umbral){
  return value > umbral ? 100 : 0;
}
