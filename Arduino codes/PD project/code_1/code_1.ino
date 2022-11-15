int pir_1 = 6;
int pir_2 = 7;
int in_1, in_2;
int pirOutput_1[3] = {0, 0, 0};
int pirOutput_2[3] = {0, 0, 0};
int pirOutput_3[3] = {0, 0, 0};
int pirOutput_4[3] = {0, 0, 0};
int pirTime_1[3] = {0, 0, 0};
int pirTime_2[3] = {0, 0, 0};
unsigned long t1 = 0;
unsigned long t2 = 0;
int count = 0;
int count2 = 0;
int peopleCount = 0;
void setup() {
  pinMode(6, INPUT); pinMode(7, INPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  in_1 = pir_output(pir_1);
  in_2 = pir_output(pir_2);
  t1 = pir_time(pir_1);
  t2 = pir_time(pir_2);
  if (count >= 3) {
    //pirOutput_3 = pirOutput_1;
    //pirOutput_4 = pirOutput_2;
    count = 0;
  }
  pirOutput_1[count] = in_1;
  pirOutput_2[count] = in_2;
  pirTime_1[count] = t1;
  pirTime_2[count] = t2;
  count += 1;

//  if ((pirOutput_1=={1,1,1} and pirOutput_3=={1,1,1}) or (pirOutput_2=={1,1,1} and pirOutput_4=={1,1,1})){
//    // at least one person is continuously moving on the sensor lines
//    count2 += 1;
//  }
//  else if ((pirTime_1[2] < pirTime_2[1]) and pirTime_1[2] != 0 and pirTime_2[0] != 0) {
//    // pir_1 recieved first signal, first cross pir_1, comes into the room
//    //pirTime_1 = {0, 0, 0};
//    //pirTime_2 = {0, 0, 0};
//    peopleCount += 1;
//  }
//  else if ((pirTime_2[2] < pirTime_1[1]) and pirTime_1[2] != 0 and pirTime_2[0] != 0) {
//    // pir_2 recieved first signal, first cross pir_2, goes out to the room
//    //pirTime_1 = {0, 0, 0};
//    //pirTime_2 = {0, 0, 0};
//    peopleCount -= 1;
//  }
  Serial.print("in2: ");
  Serial.print(in_2);
  Serial.print(" ");
  Serial.println(t2);
  Serial.print("in1: ");
  Serial.print(in_1);
  Serial.print(" ");
  Serial.println(t1);
  delay(500);
  // put your main code here, to run repeatedly:

}
int pir_output(int pin) {
  int a = digitalRead(pin);
  return a;
}
unsigned long pir_time(int pin) {
  unsigned long t = 0;
  if (digitalRead(pin) == 1) {
    t = millis();
  }
  return t;

}
