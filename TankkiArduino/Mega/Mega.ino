/*
 Name:		Mega.ino
 Created:	9/15/2018 12:40:08 AM
 Author:	Simo
*/
#include "TankkiBrushed.h"
#include "TankkiBrushless.h"
#include "TankkiRemoteTurret.h"
#define LEFT_FORWARD_PIN 11 // blue wire
#define RIGHT_FORWARD_PIN 9 // orange wire
#define LEFT_BACKWARD_PIN 3 // blue/white wire
#define RIGHT_BACKWARD_PIN 10 // orange/white wire

#define TURRET_TURN_CCW 5
#define TURRET_TURN_CW 6

#define FAN_PIN 7

#define TEMP1_PIN A9
#define TEMP2_PIN A8

#define BT_RX_PIN 2
#define BT_TX_PIN 4

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

//#define commandSource Serial
#define commandSource Serial3

byte cmd[PACKET_SIZE];

unsigned long lastCmdReceiveTime = 0;

int velLeft = 127;
int velRight = 127;
int turretTurn = 127;
//TankkiBrushed tank(LEFT_FORWARD_PIN, LEFT_BACKWARD_PIN, RIGHT_FORWARD_PIN, RIGHT_BACKWARD_PIN, TURRET_TURN_CCW, TURRET_TURN_CW);
TankkiBrushless tank(LEFT_BACKWARD_PIN, RIGHT_FORWARD_PIN, TURRET_TURN_CCW, TURRET_TURN_CW);
TankkiRemoteTurret turret(Serial2);

int temp1 = 0;
int temp2 = 0;

void setup() {
    pinMode(BT_RX_PIN, INPUT); // pin2 and 4 connected to Serial3 pins
    pinMode(BT_TX_PIN, INPUT);
    commandSource.begin(9600);
    //Serial.begin(38400); // For debugging via USB
    //Serial2.begin(9600); // Serial 2: Rx 17, Tx 16 ; Nano/turret communication
    //Serial3.begin(9600); // Serial 3: Rx 15, Tx 14 ; Bluetooth communication
    // Uncomment below lines to change motor control frequency
    // See below link for specific frequency values
    // http://playground.arduino.cc/Main/TimerPWMCheatsheet
    //TCCR1B = (TCCR1B & 0b11111000) | 0x01; // pins 9 and 10 31372.55Hz
    //TCCR2B = (TCCR2B & 0b11111000) | 0x01; // pins 11 and 3 31372.55Hz
    tank.begin();
    pinMode(FAN_PIN, OUTPUT);
    pinMode(TEMP1_PIN, INPUT); // Analog
    pinMode(TEMP2_PIN, INPUT); // Analog
    tank.stopLeft();
    tank.stopRight();
    tank.stopTurret();
}

void loop() {
    temp1 = analogRead(TEMP1_PIN);
    temp2 = analogRead(TEMP2_PIN);
    //Serial.print("loop() begin S3.available(): ");
    //Serial.print(commandSource.available());
    //Serial.print("commandSource.peek(): ");
    //Serial.print(commandSource.peek());
    if (commandSource.available() == PACKET_SIZE && commandSource.peek() == 1) {
        lastCmdReceiveTime = millis();
        for (int i = 0; i < PACKET_SIZE; i++) {
            cmd[i] = commandSource.read();
        }

        for (int i = 0; i < PACKET_SIZE; i++)
        {
            Serial.print(cmd[i]);
            Serial.print("\t");
        }
        /*
        Serial.print(temp1);
        Serial.print('\t');
        Serial.print(temp2);
        */
        TurretCommand turretCmd;

        if (cmd[0] == 1 && cmd[1] == 255) {
            velRight = cmd[2];
            velLeft = cmd[3];
            turretTurn = cmd[5];
            turretCmd.elevation = cmd[4];
            turretCmd.cannon = cmd[6] == 2;
            turretCmd.mg = cmd[8] == 2;
            turretCmd.laser = cmd[7] == 2;
        }

        tank.turnTurret(turretTurn);
        tank.moveRight(velRight);
        tank.moveLeft(velLeft);
        turret.sendMsg(turretCmd);
        //Serial.print("\n");
    }
    else if (commandSource.available() > PACKET_SIZE) {
        commandSource.read();
    }
    else {
        // Get the current time (millis since execution started).
        // Check if it has been 500ms since we received last command.
        if ((millis() - lastCmdReceiveTime)>500) {
            //More tan 500ms have passed since last command received, tank is out of range.
            Serial.println("Connection lost");
            tank.stopLeft();
            tank.stopRight();
            tank.stopTurret();
        }
    }

    // Temperature monitoring and fan control
    // Room temp : 576 - 568
    //if (temp1 < 250 || temp2 < 250) {
    //    digitalWrite(FAN_PIN, HIGH);
    //}
    //if (temp1 > 300 && temp2 > 300) {
    //    digitalWrite(FAN_PIN, LOW);
    //}
}