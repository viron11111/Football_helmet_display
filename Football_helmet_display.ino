//       5
//   6       4
//       7
//   11       9
//      10       8

// state 0 : helmet on bottom, no display
// state 1 : helmet at top, button illuminated, no display
// state 2 : helmet hits, display value for temporary time then return to state 0


#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment object

int val = 0;
float cm = 0;
float cm_old1 = 0;
float cm_old2 = 0;
float cm_old3 = 0;
int demo = 0;

int state = 0;
long clutch_timer = 0;
int clutch_length = 3000;

int button_state = 0;
long button_timer = 0;
bool blinker = 0;

int break_beam = 0;
long beam_timer = 0;

long delay_timer = 0;
int delay_length = 50;  //delay amount to ensure helmet has hit before displaying value

int randNumber;

long display_timer = 0;
int display_length = 5000;

long too_long_timer = 0;
int too_long_length = 90000;
int helmet_raised_for_too_long_length = 90000;
long helmet_raised_length_timer = 0;
bool sonar_state = 0;

int helmet_array[10];  //taking average value during init
float helmet_distance; //value used
 
void setup() {      
  randomSeed(analogRead(0));          
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT); //right-most led display 
  pinMode(1, OUTPUT); //led display
  pinMode(2, OUTPUT); //led display
  pinMode(3, OUTPUT); //left-most led display
  pinMode(4, OUTPUT); //individual led
  pinMode(5, OUTPUT); //individual led
  pinMode(6, OUTPUT); //individual led
  pinMode(7, OUTPUT); //individual led
  pinMode(8, OUTPUT); //individual led
  pinMode(9, OUTPUT); //individual led
  pinMode(10, OUTPUT); //individual led 
  pinMode(11, OUTPUT); //individual led

  pinMode(12, OUTPUT); //Relay or clutch release 

  pinMode(23, INPUT); //Button pressed
  pinMode(22, OUTPUT); //Button LED

  Serial.begin(115200);

  digitalWrite(12, HIGH);
  delay(2000);

  for (int i = 0; i < 10; i++){
    helmet_array[i] = analogRead(7);     // read the input pin
    delay(5);
  }

  int sumer = 0;

  for (int i = 0; i < 10; i = i + 1) {
    sumer = sumer + helmet_array[i];
    //Serial.println(helmet_array[i]);
  }

  helmet_distance = sumer / 10;
  
  Serial.println(helmet_distance);

  helmet_distance = helmet_distance + 15;

  if (helmet_distance > 70) helmet_distance = 70;
  
  Serial.println(helmet_distance);
  //delay(000);
  
  

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
  too_long_timer = millis() + too_long_length;
}

// the loop routine runs over and over again forever:
void loop() {
  delay(5);
  static unsigned long timer = millis();
  static int deciSeconds = 0;

  cm_old3 = cm_old2;
  cm_old2 = cm_old1;
  cm_old1 = cm;

  
  val = analogRead(7);     // read the SONAR
  //val = val/2;
  cm = (val + cm_old1 + cm_old2 + cm_old3)/4.0;

  button_state = digitalRead(23);

  break_beam = analogRead(6);
  //Serial.print("break: ");
  //Serial.println(break_beam);

  //reset counter for determining if helmet has been left inbetween break beam and bottom
  if (state == 0 && cm <= (helmet_distance)){
    helmet_raised_length_timer = millis() + helmet_raised_for_too_long_length;
  }

  //Serial.print ("Break: ");
  //Serial.println(break_beam);
   
  if (break_beam >= 950 && state == 0){
    too_long_timer = millis() + too_long_length;
    helmet_raised_length_timer = millis() + helmet_raised_for_too_long_length;
    state = 1;
  }
  else if (helmet_raised_length_timer <= millis() && state == 0){
    state = 4;
    clutch_timer = millis() + clutch_length;
  }
  else if (button_state == 0 && state == 1){
    too_long_timer = millis() + too_long_length;
    helmet_raised_length_timer = millis() + helmet_raised_for_too_long_length;
    state = 2;
    clutch_timer = millis() + clutch_length;
  }
  else if ((clutch_timer <= millis() || cm <= helmet_distance) && state == 2){
    delay_timer = millis() + delay_length;
    state = 5;
  }
  else if (delay_timer <= millis() && state == 5){
    too_long_timer = millis() + too_long_length;
    helmet_raised_length_timer = millis() + helmet_raised_for_too_long_length;
    randNumber = random(2580, 2621);
    sevseg.setNumber(randNumber,0);
    display_timer = millis() + display_length;
    state = 3;
  }
  else if (display_timer <= millis() && state == 3){
    state = 0;
  }
  else if (too_long_timer <= millis() && state != 0 && state != 4){
    state = 4;
    clutch_timer = millis() + clutch_length;
  }
  else if (clutch_timer <= millis() && state == 4){
    state = 0;
    too_long_timer = millis() + too_long_length;
  }
 
  /*if (clutch_timer > millis()){
    state = 1;
  }
  else if (button_timer > millis()){
    state = 2;
  }
  else{
    state = 0;
  }*/
  
  if (millis() - timer >= 200) {
    timer += 200;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    if (state == 0){
      digitalWrite(22, LOW);
      digitalWrite(12, LOW);
      //digitalWrite(22, LOW);
      if (demo == 0){
        sevseg.setChars("-   ");
      }
      else if (demo == 1){
        sevseg.setChars(" -  ");
      }
      else if (demo == 2){
        sevseg.setChars("  - ");
      }      
      else if (demo == 3){
        sevseg.setChars("   -");
      }      
      demo++;
      if (demo >= 4){
        demo = 0;
      }
    }
    else if (state == 1){
       sevseg.blank();
       digitalWrite(12, LOW);
       digitalWrite(22, blinker);
       blinker = !blinker;
    }
    else if (state == 2){
       //sevseg.setChars("Andy");       
       digitalWrite(22, HIGH);
       digitalWrite(12, HIGH);
    }  
    else if (state == 5){
       digitalWrite(22, HIGH);
       digitalWrite(12, HIGH);
    }      
    else if (state == 3){
       digitalWrite(22, LOW);
       digitalWrite(12, HIGH);
    }
    else if (state == 4){
      sevseg.setChars("rest");
      digitalWrite(12, HIGH);
      digitalWrite(22, LOW);
    }
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

