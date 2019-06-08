#include "TankkiBrushed.h"



TankkiBrushed::TankkiBrushed(uint8_t leftFwd, uint8_t leftBwd, uint8_t rightFwd, uint8_t rightBwd, uint8_t turretCCWPin, uint8_t turretCWPin)
    : Tankki(turretCCWPin, turretCWPin), m_leftFwdPin(leftFwd), m_leftBwdPin(leftBwd), m_rightFwdPin(rightFwd), m_rightBwdPin(rightBwd)
{
}


TankkiBrushed::~TankkiBrushed()
{
    Serial.println("TankkiBrushed init");
    pinMode(m_leftBwdPin, OUTPUT);
    pinMode(m_leftFwdPin, OUTPUT);
    pinMode(m_rightBwdPin, OUTPUT);
    pinMode(m_rightFwdPin, OUTPUT);
    Tankki::begin();
}

void TankkiBrushed::begin()
{

}

void TankkiBrushed::moveLeft(uint8_t velocity) {
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

void TankkiBrushed::moveRight(uint8_t velocity) {
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

void TankkiBrushed::stopRight() {
    analogWrite(m_rightBwdPin, 0);
    analogWrite(m_rightFwdPin, 0);
}

void TankkiBrushed::stopLeft() {
    analogWrite(m_leftFwdPin, 0);
    analogWrite(m_leftBwdPin, 0);
}