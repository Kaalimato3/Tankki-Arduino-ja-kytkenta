/*
 Name:		Mega.ino
 Created:	9/15/2018 12:40:08 AM
 Author:	Simo
*/
#include "Tankki.h"
#include "TankkiRemoteTurret.h"
#define vEteen 11 // Si
#define oEteen 9 // Or
#define vTaakse 3 // SiVa
#define oTaakse 10 // OrVa

#define FAN_PIN 7

#define TURRET_TURN_CCW 5
#define TURRET_TURN_CW 6

#define rxPin 2
#define txPin 4

#define PACKET_SIZE 9

struct TankCommand {
    uint8_t velRight;
    uint8_t velLeft;
    uint8_t rotation;
    uint8_t elevation;
    bool cannon;
    bool laser;
    bool mg;
};


byte cmd[PACKET_SIZE];

unsigned long timer0 = 2000;
unsigned long timer1 = 0;

int velLeft = 127;
int velRight = 127;
int turretTurn = 127;
Tankki tank(vEteen, vTaakse, oEteen, oTaakse, TURRET_TURN_CCW, TURRET_TURN_CW);
TankkiRemoteTurret turret(Serial2);

void setup() {
    pinMode(rxPin, INPUT); // pin2 ja 4 kytketty Serial kolmoseen
    pinMode(txPin, INPUT);
    Serial.begin(38400); // For debugging via USB
    Serial2.begin(9600);   // Serial 2: Rx 17, Tx 16 ; Nano/turret communication
    Serial3.begin(9600);   // Serial 3: Rx 15, Tx 14 ; Bluetooth communication
                           // Kuitenkin n‰ytt‰‰ silt‰ ett‰ vakiotaajuus (490) on parempi
                           //TCCR1B = (TCCR1B & 0b11111000) | 0x01; // Nastat 9 ja 10 31372.55Hz
                           //TCCR2B = (TCCR2B & 0b11111000) | 0x01; // Nastat 11 ja 3 31372.55Hz
    tank.begin();
    //pinMode(oTaakse, OUTPUT);
    //pinMode(oEteen, OUTPUT);
    //pinMode(vTaakse, OUTPUT);
    //pinMode(vEteen, OUTPUT);
    //
    //pinMode(FAN_PIN, OUTPUT);
    //
    //pinMode(TURRET_TURN_CCW, OUTPUT);
    //pinMode(TURRET_TURN_CW, OUTPUT);
    tank.stopLeft();
    tank.stopRight();
    tank.stopTurret();
}

void loop() {
    //Serial.print("loop() begin S3.available(): ");
    //Serial.print(Serial3.available());
    //Serial.print("Serial3.peek(): ");
    //Serial.print(Serial3.peek());
    if (Serial3.available() == PACKET_SIZE && Serial3.peek() == 1) {
        timer1 = millis();
        for (int i = 0; i < PACKET_SIZE; i++) {
            cmd[i] = Serial3.read();
        }

        for (int i = 0; i < PACKET_SIZE; i++)
        {
            Serial.print(cmd[i]);
            Serial.print("\t");
        }

        TurretCommand turretCmd;

        if (cmd[0] == 1 && cmd[1] == 255) {
            velRight = cmd[2];
            velLeft = cmd[3];
            turretTurn = cmd[5];
            turretCmd.elevation = cmd[4];
            turretCmd.cannon = cmd[6] > 0;
            turretCmd.mg = cmd[8] > 0;
            turretCmd.laser = cmd[7] > 0;

            /*for (int i = 0; i < 6; i++)
            {
            Serial.print(cmd[i]);
            Serial.print("\t");
            }*/
        }

        tank.turnTurret(turretTurn);
        tank.moveRight(velRight);
        tank.moveLeft(velLeft);
        turret.sendMsg(turretCmd);
        Serial.print("\n");
    }
    else if (Serial3.available() > PACKET_SIZE) {
        Serial3.read();
    }
    else {
        timer0 = millis();  //Get the current time (millis since execution started).
                            //Check if it has been 500ms since we received last command.
        if ((timer0 - timer1)>500) {
            //More tan 500ms have passed since last command received, car is out of range.
            tank.stopLeft();
            tank.stopRight();
            tank.stopTurret();
        }
    }
}