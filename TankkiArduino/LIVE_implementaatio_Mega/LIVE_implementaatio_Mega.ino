#include <SoftwareSerial.h>
#define vEteen 11 // Si
#define oEteen 9 // Or
#define vTaakse 3 // SiVa
#define oTaakse 10 // OrVa

#define rxPin 2
#define txPin 4

#define MIN_VEL 10

byte cmd[6];

unsigned long timer0 = 2000;
unsigned long timer1 = 0;

int velLeft = 127;
int velRight = 127;
//SoftwareSerial mSoftSerial(rxPin, txPin);

void stopRight();
void stopLeft();
void moveLeft(int velocity);
void moveRight(int velocity);

void setup() {
  pinMode(2, INPUT); // pin2 ja 4 kytketty Serial kolmoseen
  pinMode(4, INPUT);
  Serial.begin(38400);
  Serial.println("Hello!");
  Serial3.begin(9600);   // Serial 3: Rx 15, Tx 14
  // Kuitenkin näyttää siltä että vakiotaajuus (490) on parempi
  //TCCR1B = (TCCR1B & 0b11111000) | 0x01; // Nastat 9 ja 10 31372.55Hz
  //TCCR2B = (TCCR2B & 0b11111000) | 0x01; // Nastat 11 ja 3 31372.55Hz
  pinMode(oTaakse, OUTPUT);
  pinMode(oEteen, OUTPUT);
  pinMode(vTaakse, OUTPUT);
  pinMode(vEteen, OUTPUT);
  stopLeft();
  stopRight();
}

void loop() {
  if(Serial3.available() > 6 && Serial3.peek() == 1) {
    timer1 = millis();
    for (int i = 0; i < 6; i++) {
      cmd[i] = Serial3.read();
    }
    /*
    for (int i = 0; i < 6; i++)
    {
      Serial.print(cmd[i]);
      Serial.print("\t");
    }
    */
    //Serial.print("\n");
    if (cmd[0] == 1 && cmd[1] == 2 && cmd[2] == 3 && cmd[5] == 4) {
      velRight = cmd[3];
      velLeft = cmd[4];
      /*for (int i = 0; i < 6; i++)
      {
        Serial.print(cmd[i]);
        Serial.print("\t");
      }*/
    }
    moveRight(velRight);
    moveLeft(velLeft);
  }else{
    //mSoftSerial.read();
    timer0 = millis();  //Get the current time (millis since execution started).
    //Check if it has been 500ms since we received last command.
    if((timer0 - timer1)>500){ 
      //More tan 500ms have passed since last command received, car is out of range.
      stopLeft();
      stopRight();
    }
  }
}

void moveLeft(int velocity){
  if(velocity > 127) {
      analogWrite(vTaakse, 0);
      analogWrite(vEteen, map(velocity, 127, 241, MIN_VEL, 255));
    }else if(velocity < 127) {
      analogWrite(vEteen, 0);
      analogWrite(vTaakse, map(velocity, 127, 13, MIN_VEL, 255));
    }else
      stopLeft();
}

void moveRight(int velocity){
  if(velocity > 127) {
      analogWrite(oTaakse, 0);
      analogWrite(oEteen, map(velocity, 127, 254, MIN_VEL, 255));
    }else if(velocity < 127) {
      analogWrite(oEteen, 0);
      analogWrite(oTaakse, map(velocity, 127, 0, MIN_VEL, 255));
    }else
      stopRight();
}

void stopRight(){
  analogWrite(oTaakse, 0);
  analogWrite(oEteen, 0);
}

void stopLeft(){
  analogWrite(vEteen, 0);
  analogWrite(vTaakse, 0);
}
