int ledPin = 13;                // LED 
int pirPin = 9;                 // PIR Out pin 
int pirStat = 0;                   // PIR status

void setup() {
 pinMode(ledPin, OUTPUT);     
 pinMode(pirPin, INPUT);     
 Serial.begin(9600);
}
void loop(){
 pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {            // if motion detected
   digitalWrite(ledPin, HIGH);  // turn LED ON
   Serial.println("Hey I got you!!!");
   Serial.println(pirStat);
   delay(1000);
 } 
 else {
   blink(); // turn LED OFF if we have no motion
   Serial.println("No motion");
   Serial.println(pirStat);
   delay(1000);
   
 }
} 

void blink(){
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
}
