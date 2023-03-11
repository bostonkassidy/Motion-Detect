#include <elapsedMillis.h>
#include <Keyboard.h>

////SENSOR PINS
#define sensor1 A0

const int sensorCount = 1;
int touchFlag;
long total[sensorCount];

long threshhold = 200;
long reset = 400;

int led = 13;

int resetTime = 30 * 1000; ///30 seconds
int calibrationTime = 10;

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 3;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int average[numReadings];                // the average

elapsedMillis activeTime;

void(* resetFunc) (void) = 0;//declare reset function

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  //Keyboard.begin();

  pinMode(sensor1, INPUT);

  ///reset filtering array
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
/*
  ///CALIBRATE SENSOR
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("Done Calibrating");
  Serial.println("/r");

*/
}

void loop() {
  // read sensor and subtract the last reading:
  total[0] = total[0] - readings[readIndex];
  readings[readIndex] = analogRead(sensor1);
  total[0] = total[0] + readings[readIndex];

  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  for (int i; i <= sensorCount; i++) {
    average[i] = total[i] / numReadings;
  }

  //// Uncomment for setup
  for (int i = 0; i <= sensorCount - 1; i++) {
    Serial.print(i + 1);
    Serial.print(":");
    Serial.print(average[i]);
    Serial.print("\t");
    if (i == sensorCount - 1) {
      Serial.print("threshhold: " + String(threshhold));
      Serial.println("\t");
      delay(50);
    }
  }

  if (average[0] > threshhold && touchFlag == 0) {
    Serial.print("touched : ");
    Serial.print(average[0]);
    Serial.print("\t");
    Serial.println("threshhold: " + String(threshhold));
    touchFlag = 1;
    digitalWrite(15, LOW);
    //Keyboard.println("1");
      //Keyboard.press(KEY_F1);
      //Keyboard.releaseAll();
    //delay(1000);
  }

  if (average[0] < threshhold) {
    touchFlag = 0;
    digitalWrite(15, HIGH);
  }
}

