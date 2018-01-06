/*
  Resistomatic

  Measures an unknown resistance using a voltage divider.
  Known resistors are attached to digital pins d7-d12
  Their other ends are commoned and connected to one end of the resistor under test.
  The other end of the resistor under test is grounded.

  setup opens the serial port and makes each of d7-d11 an input (so high impedence):
  loop:
     for each of d7-d11:
        make the pin an output
        set the output high
        wait 5 ms for the converter to settle
        read, convert and print the analogue reading
        make the pin an input
     wait 1000 ms


 */


const int analogInPin = A0;  // Analog input
const int PIN_COUNT = 6;
const int SAMPLE_COUNT = 2;

const int pin[PIN_COUNT] = {2, 3, 4, 5, 6, 7};
const float r1[PIN_COUNT] = {100.0, 1000.0, 10000.0, 100000.0, 390000.0, 1000000.0};

int buttonState = 0;
bool mode = 1;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  // send all the pins we'll use low, and then configure them as inputs
  for (int i=0; i<PIN_COUNT; i++) {
     pinMode(pin[i], OUTPUT);
     digitalWrite(pin[i],LOW);
  }
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  digitalWrite(11,LOW);
  //Serial.println("OHM-METER MODE");
  Serial.println("CONDUCTIVITY SENSOR MODE");
  delay(5);

  for (int i=0; i<PIN_COUNT; i++) {  
    pinMode(pin[i], OUTPUT);
    digitalWrite(pin[i],HIGH);
    //float v = averageVoltage();
    //Serial.println(v);
    float total = analogRead(analogInPin);
    digitalWrite(pin[i],LOW);     
    pinMode(pin[i], INPUT);
  }
}

// take SAMPLE_COUNT succesive readings of the voltage and average them
float averageVoltage() {
  float total = 0.0;
  for (int i=0;i<SAMPLE_COUNT;i++) {
    delay(5);
    total += float(analogRead(analogInPin));
  }
  // convert to voltage and average
  return 5.0*total/(SAMPLE_COUNT*1023.0);
}

// see blog post for details of this caluclation
float calculateResistance(float r, float v) {
   return r * (1.0/((5.0/v)-1));
   //r/(3.3/v-1.0);
}

void clearem(){
  for (int i=0; i<PIN_COUNT; i++) {
    digitalWrite(pin[i],LOW);
  }
}

void loop() {
   float minimum = 2.5;
   float resistance = 100000000.0; // default value

   /* loop through finding the best estimate
      which we'll get when the measured voltage is closest
      to 1.65v  */
   buttonState = digitalRead(12);

   if (buttonState == LOW) {
     //Serial.println(mode);
     mode = !mode;
     if (mode == 0) Serial.println("OHM-METER MODE");
     else Serial.println("CONDUCTIVITY SENSOR MODE");
     delay(1000);
   }

   if (mode == 0){
     for (int i=0; i<PIN_COUNT; i++) {  
       digitalWrite(11,LOW);
       pinMode(pin[i], OUTPUT);
       digitalWrite(pin[i],HIGH);
       float v = averageVoltage();
       //Serial.println(v);
       digitalWrite(pin[i],LOW);     
       pinMode(pin[i], INPUT);
       float difference = abs(v-2.5);
       //Serial.println(difference);
       if (5.0 > v && difference <= minimum) {
          minimum = difference;
          resistance = calculateResistance(r1[i], v);
       }
     } 
  
     if (resistance >= 20000000){
      digitalWrite(13, LOW);    
      Serial.println("Open Circuit...");
     }
     else{
       digitalWrite(13, HIGH);    
       Serial.print("resistance = ");
       Serial.println(resistance);
     }
     delay(100);
   }
   else{
     digitalWrite(13, LOW);
     pinMode(7, OUTPUT);
     digitalWrite(7,HIGH);
     float v = averageVoltage();
     //Serial.println(v);
     digitalWrite(7,LOW);     
     pinMode(7, INPUT);   
     if (v <= 4.70){
      digitalWrite(11,HIGH);
     }
     else{
      digitalWrite(11,LOW);
     }
     //Serial.println(v);
     //delay(500); 
   }
   delay(1);
} 
