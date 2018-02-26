//       5
//   6       4
//       7
//   11       9
//       10       8

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment object

int val = 0;
float cm = 0;
 
void setup() {                
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT);  
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);  
  pinMode(11, OUTPUT);  
  
  pinMode(22, OUTPUT); 

  Serial.begin(9600);

  /*for (int i = 0; i < 50; i++){
    digitalWrite(22, HIGH);
    delay(200);
    digitalWrite(22, LOW);
    delay(200);
  }*/
  

  //digitalWrite(0, HIGH);
  //digitalWrite(10, HIGH);
  //delay(3000);

  byte numDigits = 4;   
  byte digitPins[] = {3, 2, 1, 0};
  byte segmentPins[] = {5, 4, 9, 10, 11, 6, 7, 8};
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = N_TRANSISTORS; // See README.md for options
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);
}

// the loop routine runs over and over again forever:
void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;

  val = analogRead(7);     // read the input pin 
  val = val/2;
  cm = val * 2.54;
  //Serial.println(val);
  if (cm <= 50){
    digitalWrite(22,HIGH);
  }
  else{
    digitalWrite(22,LOW);
  }
  //delay(50);
  
  if (millis() - timer >= 100) {
    timer += 100;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    
    if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(cm, 1);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

void one(){
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  digitalWrite(20, HIGH);
}

void two(){
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
}

void three(){
  digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
}

void four(){
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, LOW);
  digitalWrite(20, HIGH);
}

void five(){
  digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(20, LOW);
}

void six(){
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(20, LOW);
}

void seven(){
  digitalWrite(13, LOW);
  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  digitalWrite(18, LOW);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
}

void eight(){
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
}

void nine(){
  digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, LOW);
  digitalWrite(17, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);
}

void decimal(){
  digitalWrite(16, HIGH);
}

void no_decimal(){
  digitalWrite(16, LOW);
}

