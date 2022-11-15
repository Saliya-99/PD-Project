//#include "IRremote.h"

#define trigPin 3
#define echoPin 2
#define trig 12
#define echo 11
#define led 10
//#define receiverPin 8

unsigned long t1;
unsigned long t2;
bool light;
//int On = 0; //output value from IR Receiver
int L;  //Output value from Ultrasonic Sensor
int M ;
int heads;
float distantThreshold = 100;

//IRrecv receiveIR(receiverPin);
//decode_results Results;


void setup() {
  pinMode(trigPin, OUTPUT); //enabling pins
  pinMode(echoPin, INPUT);
  pinMode(trig, OUTPUT); //enabling pins
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
  // receiveIR.enableIRIn();
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  ultrasonicsensor();
  ultrasonicsensor2();
  //Serial.println(t2 - t1);
  Serial.println(t1);
  Serial.println(t2);
  if ((t2-t1)>100 && (t1!=0) && (t2 !=0)){
    digitalWrite(led,HIGH);
    light = true;
    t1 = 0;
    heads ++;
  }
  else if ((t1-t2)>100 && (t1!=0) && (t2 !=0)) {
    t2 = 0;
    heads --;
    if (heads<=0){
      digitalWrite(led,LOW);
      light = false;
      //heads = 0;
    }


  }
  Serial.print("Heads                      :");
  Serial.println(heads);
  delay(1000);
  
}

void ultrasonicsensor() { //Function for Ultrasonic sensor
  long TimeDuration, Distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  TimeDuration = pulseIn(echoPin, HIGH); //Calculating time
  Distance = (TimeDuration / 2) / 29.1; //Calculating the distance
  Serial.print("D1 : ");
  Serial.println(Distance);
  if (Distance < distantThreshold) { //person goes into the room(Distance less than the width of the door) distance is in cm
    L = 1;
    t1 = millis()%32767;
    if (!(light) && (t2 !=0)){
      digitalWrite(led,HIGH);
    }

  }
  else {
    L = 0;  //person goes out of the room and no person passing (Distance is equal to the width of the door)
  }
}


void ultrasonicsensor2() { //Function for Ultrasonic sensor
  long TimeDur, Dist;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  TimeDur = pulseIn(echo, HIGH); //Calculating time
  Dist = (TimeDur / 2) / 29.1; //Calculating the distance
  Serial.print("D2 : ");
  Serial.println(Dist);
  if (Dist < distantThreshold ) { //person goes into the room(Distance less than the width of the door) distance is in cm
    M = 1;
    t2 = millis()%32767;
  }
  else {
    M = 0;  //person goes out of the room and no person passing (Distance is equal to the width of the door)
  }
}
/*
  void IRreceiver(){ //Function for IR receiver
  if (receiveIR.decode(&Results)){
    switch(Results.value){
      case 0xFF38C7: //press 5 to switch on the system to give control to the sensors. (0xFF38C7 - hexadecimal code)
      On = 1;
    }
    switch(Results.value){
      case 0xFF18E7: //press 2 to completely switch off the system
      On = 0;
    }
    switch(Results.value){
      case 0xFF7A85: //press 3 to completely switch on the system whatever the sensor input is.
      On = 2;
    }
  }
  }*/
