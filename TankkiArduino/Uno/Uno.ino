/*
 Name:		Uno.ino
 Created:	9/15/2018 12:40:54 AM
 Author:	Simo
*/
#include "Tankki.h"
#include <SoftwareSerial.h>
#define vEteen 11 // Si
#define oEteen 9 // Or
#define vTaakse 3 // SiVa
#define oTaakse 10 // OrVa

#define rxPin 2
#define txPin 4

#define MIN_VEL 10

#define CMD_LENGTH 11

struct TankCommand {
    uint8_t velRight;
    uint8_t velLeft;
    uint8_t rotation;
    bool cannon;
    bool laser;
    bool mg;
};

byte cmd[6];

unsigned long timer0 = 2000;
unsigned long timer1 = 0;

uint8_t velLeft = 127;
uint8_t velRight = 127;
SoftwareSerial mSoftSerial(rxPin, txPin);
Tankki tank(vEteen, vTaakse, oEteen, oTaakse);

void setup() {
    Serial.begin(38400);
    Serial.println("Hello!");
    mSoftSerial.begin(9600);
    // Kuitenkin näyttää siltä että vakiotaajuus (490) on parempi
    //TCCR1B = TCCR1B & 0b11111000 | 0x01; // Nastat 9 ja 10 122.55Hz
    //TCCR2B = TCCR2B & 0b11111000 | 0x01; // Nastat 11 ja 3 122.55Hz
    pinMode(oTaakse, OUTPUT);
    pinMode(oEteen, OUTPUT);
    pinMode(vTaakse, OUTPUT);
    pinMode(vEteen, OUTPUT);
    tank.stopLeft();
    tank.stopRight();
}

void loop() {
    if (mSoftSerial.available() > CMD_LENGTH && mSoftSerial.peek() == 1) {
        timer1 = millis();
        for (int i = 0; i < CMD_LENGTH; i++) {
            cmd[i] = mSoftSerial.read();
        }
        /*
        for (int i = 0; i < CMD_LENGTH; i++)
        {
        Serial.print(cmd[i]);
        Serial.print("\t");
        }*/

        Serial.print("\n");
        if (cmd[0] == 1 && cmd[1] == 255 && cmd[9] == 255 && cmd[10] == 1) {
            velRight = cmd[2];
            velLeft = cmd[3];

            for (int i = 0; i < CMD_LENGTH; i++)
            {
                Serial.print(cmd[i]);
                Serial.print("\t");
            }

        }
        tank.moveRight(velRight);
        tank.moveLeft(velLeft);
    }
    else {
        //mSoftSerial.read();
        timer0 = millis();  //Get the current time (millis since execution started).
                            //Check if it has been 500ms since we received last command.
        if ((timer0 - timer1)>500) {
            //More tan 500ms have passed since last command received, car is out of range.
            tank.stopLeft();
            tank.stopRight();
        }
    }
}
