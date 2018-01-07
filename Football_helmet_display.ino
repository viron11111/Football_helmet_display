//       19
//   18       20
//       17
//   13       15
//       14       16

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment object
 
void setup() {                
  // initialize the digital pin as an output.
  pinMode(13, OUTPUT);  
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);  

  digitalWrite(21, HIGH);

  byte numDigits = 3;   
  byte digitPins[] = {23, 22, 21};
  byte segmentPins[] = {19, 20, 15, 14, 13, 18, 17, 16};
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = N_TRANSISTORS; // See README.md for options
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);
}

// the loop routine runs over and over again forever:
void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;
  
  if (millis() - timer >= 100) {
    timer += 100;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    
    if (deciSeconds == 1000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(deciSeconds, 1);
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
