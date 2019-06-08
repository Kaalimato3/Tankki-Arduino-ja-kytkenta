#include "TankkiBrushless.h"



TankkiBrushless::TankkiBrushless(uint8_t leftESCPin, uint8_t rightESCPin, uint8_t turretCCWPin, uint8_t turretCWPin) 
    : Tankki(turretCCWPin, turretCWPin)
{
    m_leftESC.attach(leftESCPin, MIN_MILLIS, MAX_MILLIS);
    m_rightESC.attach(rightESCPin, MIN_MILLIS, MAX_MILLIS);
}


TankkiBrushless::~TankkiBrushless()
{
}

void TankkiBrushless::begin()
{
    Serial.println("TankkiBrushless init");
    Tankki::begin();
}

void TankkiBrushless::moveLeft(uint8_t speed)
{
    m_leftESC.writeMicroseconds(map(speed, 10, 243, MIN_MILLIS, MAX_MILLIS));
}

void TankkiBrushless::moveRight(uint8_t speed)
{
    m_rightESC.writeMicroseconds(map(speed, 10, 243, MIN_MILLIS, MAX_MILLIS));
}

void TankkiBrushless::stopLeft()
{
    m_leftESC.writeMicroseconds(MID_MILLIS);
}

void TankkiBrushless::stopRight()
{
    m_rightESC.writeMicroseconds(MID_MILLIS);
}
