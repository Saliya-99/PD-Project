#include "IRremote.h"

int PIR = 3;

int Bulb = 10;
int receiverPin = 8;
int pirOutput;
float ldrOutput;
bool light;
int On = 0; //output value from IR Receiver
int LED1 = 2;
int LED2 = 11;
int LED3 = 12;

IRrecv receiveIR(receiverPin);
decode_results Results;

void setup() {
  pinMode(PIR, INPUT);
  pinMode(Bulb, OUTPUT);
  receiveIR.enableIRIn();
  Serial.begin(9600);
  delay(1000);
}

void loop() {

  IRreceiver();
  Serial.print("Remote Command:");
  Serial.println(On);

  pirOutput = digitalRead(PIR);
  Serial.print("PIR Output   :");
  Serial.println(pirOutput);

  ldrOutput = analogRead(A0);
  Serial.print("LDR Output   :");
  Serial.println(ldrOutput);


  if (On == 0) {

    digitalWrite(Bulb, 0);
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 0);
    digitalWrite(LED3, 0);

  }
  if (On == 2) {
    digitalWrite(Bulb, 1);
  }

  if (On == 3) {
    if (pirOutput > 0) {
      digitalWrite(Bulb, 1);
    }
    else {
      digitalWrite(Bulb, 0);
    }
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 1);
    digitalWrite(LED3, 0);
  }
  if (On == 1) {
    if (ldrOutput < 500) {

      if (pirOutput > 0) {
        digitalWrite(Bulb, 1);
      }
      else {
        digitalWrite(Bulb, 0);
      }
    }
    else {
      digitalWrite(Bulb, 0);
    }
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
    digitalWrite(LED3, 1);
  }
  delay(500);
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
    switch (Results.value) {
      case 16748655: //press 9 to switch on the system to give control to the sensors except LDR.
        On = 3;
    }
  }

  receiveIR.resume();
}
