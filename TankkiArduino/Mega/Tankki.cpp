#include "Tankki.h"


Tankki::Tankki(uint8_t leftFwd, uint8_t leftBwd, uint8_t rightFwd, uint8_t rightBwd) :
    m_leftBwdPin(leftBwd), m_leftFwdPin(leftFwd), m_rightBwdPin(rightBwd), m_rightFwdPin(rightFwd)
{
}

void Tankki::moveLeft(uint8_t velocity) {
    //Serial.write("moveLeft vel: ");
    //Serial.write(velocity);
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
    //Serial.write("moveRight vel: ");
    //Serial.write(velocity);
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

void Tankki::stopLeft() {
    analogWrite(m_leftFwdPin, 0);
    analogWrite(m_leftBwdPin, 0);
}