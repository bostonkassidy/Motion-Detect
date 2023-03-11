#include <elapsedMillis.h>
#include <Keyboard.h>

////SENSOR PINS
#define PIR1 14

const int sensorCount = 1;
int touchFlag;
long total[sensorCount];

long threshhold = 250;
long resetthreshhold = 400;

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
   
   Keyboard.begin();
   
  pinMode(PIR1, INPUT);
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

   for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
   }
}
      
void loop(){
   if (digitalRead(PIR1) == HIGH && touchFlag == 0){ 
      Serial.println("I SEE YOU");
      touchFlag = 1;
      Keyboard.println("1");
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
    }
    
    if (digitalRead(PIR1) == LOW){
      touchFlag = 0;
      }
}
