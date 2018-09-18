/*
Name:		NanoTurret.ino
Created:	9/14/2018 6:59:59 PM
Author:	Simo
*/

#include <Servo.h>
#include <SoftwareSerial.h>

#define CANNON_BIT	0b00000001
#define LASER_BIT	0b00000010
#define MG_BIT		0b00000100

#define CANNON_PIN 3
#define LASER_PIN 11
#define LED_PIN 10
#define SERVO_PIN 4

#define MAX_ELEV 150
#define MIN_ELEV 0
#define CMD_MIN_ELEV 254
#define CMD_MAX_ELEV 0

#define CMD_LENGTH 4

int batt[4];
byte cmd[CMD_LENGTH];
Servo servo;
long time = 0;
int curElev = 0;

void setup() {
    Serial.begin(9600);
    pinMode(CANNON_PIN, OUTPUT);
    pinMode(LASER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    servo.attach(SERVO_PIN);
}

void loop() {

    if (Serial.available() == CMD_LENGTH && Serial.peek() == 1)
    {
        for (int i = 0; i < CMD_LENGTH; i++)
        {
            cmd[i] = Serial.read();
        }

        for (int i = 0; i < CMD_LENGTH; i++) {
            Serial.print(cmd[i]);
            Serial.print("\t");
        }

        digitalWrite(LASER_PIN, ((cmd[3] & LASER_BIT) > 0) ? HIGH : LOW);
        digitalWrite(LED_PIN, ((cmd[3] & MG_BIT) > 0) ? HIGH : LOW);
        if (cmd[2] != 127) {
            if (map(cmd[2], CMD_MAX_ELEV, CMD_MIN_ELEV, MIN_ELEV, MAX_ELEV) > curElev) {
                if (curElev <= MAX_ELEV)
                    curElev++;
            }
            else if (map(cmd[2], CMD_MAX_ELEV, CMD_MIN_ELEV, MIN_ELEV, MAX_ELEV) < curElev) {
                if (curElev >= MIN_ELEV)
                    curElev--;
            }
        }

        Serial.print("\n");
    }
    else if (Serial.available() > CMD_LENGTH) {
        Serial.read();
    }
    servo.write(curElev);

}