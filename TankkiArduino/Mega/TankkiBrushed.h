#pragma once
#include "Tankki.h"
class TankkiBrushed :
    public Tankki
{
public:
    TankkiBrushed(uint8_t leftFwd, uint8_t leftBwd, uint8_t rightFwd, uint8_t rightBwd, uint8_t turretCCWPin, uint8_t turretCWPin);
    ~TankkiBrushed();

    virtual void begin();

    virtual void moveLeft(uint8_t speed);
    virtual void moveRight(uint8_t speed);
    virtual void stopLeft();
    virtual void stopRight();
private:
    uint8_t m_leftFwdPin;
    uint8_t m_rightFwdPin;
    uint8_t m_leftBwdPin;
    uint8_t m_rightBwdPin;
};

