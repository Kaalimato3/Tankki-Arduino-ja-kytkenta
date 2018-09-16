#include "Tankki.h"


Tankki::Tankki(uint8_t leftFwd, uint8_t leftBwd, uint8_t rightFwd, uint8_t rightBwd, uint8_t turretCCWPin, uint8_t turretCWPin) :
    m_leftBwdPin(leftBwd), m_leftFwdPin(leftFwd), m_rightBwdPin(rightBwd), m_rightFwdPin(rightFwd), m_turretCCWPin(turretCCWPin), m_turretCWPin(turretCWPin)
{
}

void Tankki::begin() 
{
    Serial.println("Tankki init");
    pinMode(m_leftBwdPin, OUTPUT);
    pinMode(m_leftFwdPin, OUTPUT);
    pinMode(m_rightBwdPin, OUTPUT);
    pinMode(m_rightFwdPin, OUTPUT);
    pinMode(m_turretCCWPin, OUTPUT);
    pinMode(m_turretCWPin, OUTPUT);
}

void Tankki::moveLeft(uint8_t velocity) {
    //Serial.print("moveLeft vel: ");
    //Serial.print(velocity);
    if (velocity > 127) {
        analogWrite(m_leftBwdPin, 0);
        analogWrite(m_leftFwdPin, map(velocity, 127, 243, 10, 255));
    }
    else if (velocity < 127) {
        analogWrite(m_leftFwdPin, 0);
        analogWrite(m_leftBwdPin, map(velocity, 127, 10, 10, 255));
    }
    else {
        stopLeft();
    }
}

void Tankki::moveRight(uint8_t velocity) {
    //Serial.print("moveRight vel: ");
    //Serial.print(velocity);
    if (velocity > 127) {
        analogWrite(m_rightBwdPin, 0);
        analogWrite(m_rightFwdPin, map(velocity, 127, 243, 10, 255));
    }
    else if (velocity < 127) {
        analogWrite(m_rightFwdPin, 0);
        analogWrite(m_rightBwdPin, map(velocity, 127, 10, 10, 255));
    }
    else {
        stopRight();
    }
}

void Tankki::stopRight() {
    analogWrite(m_rightBwdPin, 0);
    analogWrite(m_rightFwdPin, 0);
}

void Tankki::turnTurret(uint8_t val)
{
    Serial.print("turnTurret val: ");
    Serial.print(val);
    Serial.print("\t");
    if (val > 127) {
        Serial.print("CW");
        analogWrite(m_turretCCWPin, 0);
        analogWrite(m_turretCWPin, map(val, 127, 254, 10, 255));
    }
    else if (val < 127) {
        Serial.print("CCW");
        analogWrite(m_turretCWPin, 0);
        analogWrite(m_turretCCWPin, map(val, 127, 0, 10, 255));
    }
    else {
        Serial.print("0");
        stopTurret();
    }
}

void Tankki::stopTurret()
{
    analogWrite(m_turretCCWPin, 0);
    analogWrite(m_turretCWPin, 0);
}

void Tankki::stopLeft() {
    analogWrite(m_leftFwdPin, 0);
    analogWrite(m_leftBwdPin, 0);
}