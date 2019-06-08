#pragma once
#include "Tankki.h"
#include <Servo.h>

#define MIN_MILLIS 600
#define MAX_MILLIS 2400
#define MID_MILLIS (MIN_MILLIS + MAX_MILLIS) / 2

class TankkiBrushless :
    public Tankki
{
public:
    TankkiBrushless(uint8_t leftESCPin, uint8_t rightESCPin, uint8_t turretCCWPin, uint8_t turretCWPin);
    ~TankkiBrushless();

    virtual void begin();

    virtual void moveLeft(uint8_t speed);
    virtual void moveRight(uint8_t speed);
    virtual void stopLeft();
    virtual void stopRight();
private:
    Servo m_leftESC;
    Servo m_rightESC;
};

