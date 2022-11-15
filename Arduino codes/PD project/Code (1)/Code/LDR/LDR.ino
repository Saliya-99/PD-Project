int LDR = A0; //LDR Pin
int LdrValue; // Output of LDR sensor will store in this variable
int LED = 13; //LED pin

void setup() {
  Serial.begin(9600); //start the serial communication
}


void loop() {
  LdrValue = analogRead(LDR); // read the value from LDR
  
  if (LdrValue < 100){   
    digitalWrite(LED, HIGH);      
  }
  else{
    digitalWrite(LED, LOW);
  }
  
  delay(250);
}
