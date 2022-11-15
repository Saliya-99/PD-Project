#include "IRremote.h"

int trigPin =  3;
int echoPin = 2;
int trig = 12;
int echo = 11;
int Bulb = 10;
#define receiverPin 8

bool light;
int On = 0; //output value from IR Receiver
int L;  //Output value from Ultrasonic Sensor
int M ;
int headCount = 0;
float distantThreshold = 100;
int initialD1, initialD2, distance1, distance2;
String seq = "";
int counter = 0;
int timeout = 100;

IRrecv receiveIR(receiverPin);
decode_results Results;

void setup() {
  pinMode(trigPin, OUTPUT); //enabling pins
  pinMode(echoPin, INPUT);
  pinMode(trig, OUTPUT); //enabling pins
  pinMode(echo, INPUT);
  pinMode(Bulb, OUTPUT);
  receiveIR.enableIRIn();
  Serial.begin(9600);
  delay(1000);
  initialD1 = measureDistance(trigPin, echoPin);
  initialD2 = measureDistance(trig, echo);
}

void loop() {

  IRreceiver();
  Serial.print("Remote Command:");
  Serial.println(On);
  

  distance1 = measureDistance(trigPin, echoPin);
  distance2 = measureDistance(trig, echo);


  if (distance1 < distantThreshold && seq[0] != '1') {

    seq += '1';

  }

  if (distance2 < distantThreshold && seq[0] != '2') {

    seq += '2';

  }

  if (seq == "12") {
    headCount += 1;
    seq = "";
    delay(200);
  }

  if (seq == "21" && headCount > 0) {
    headCount -= 1;
    seq = "";
    delay(200);
  }

  if (seq.length() == 1) {
    counter += 1;

  }
  else {
    counter = 0;

  }

  if (timeout <= counter || seq == "21" || seq == "12" || seq.length() > 2) {
    seq = "";
    counter = 0;
  }

  Serial.print("Distance1: ");
  Serial.println(distance1);
  Serial.print("Distance2: ");
  Serial.println(distance2);
  Serial.print("Heads: ");
  Serial.println(headCount);

  if (On ==0){
    digitalWrite(Bulb,0);
    
  }
  if(On == 2){
    digitalWrite(Bulb,1);
  }

  if(On ==1){
    if (headCount >0){
      digitalWrite(Bulb,1);
    }
    else{
      digitalWrite(Bulb,0);
    }
  }
  delay(500);

}


int measureDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(250);
  int distance = pulseIn(echo, HIGH) * 0.017;
  return distance;
}

void IRreceiver() { //Function for IR receiver
  if (receiveIR.decode(&Results)) {
    //Serial.println(Results.value);
    switch (Results.value) {
      case 16738455: //press * to switch on the system to give control to the sensors. (0xFF38C7 - hexadecimal code)
        On = 1;
    }
    switch (Results.value) {
      case 16750695: //press 0 to completely switch off the system
        On = 0;
    }
    switch (Results.value) {
      case 16756815: //press # to completely switch on the system whatever the sensor input is.
        On = 2;
    }
  }
  receiveIR.resume();
}
