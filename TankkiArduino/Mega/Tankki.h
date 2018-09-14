// Tankki.h

#ifndef _TANKKI_h
#define _TANKKI_h
#include "TankkiRemoteTurret.h"
#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

class Tankki {
public:
    Tankki(uint8_t leftFwd, uint8_t leftBwd, uint8_t rightFwd, uint8_t rightBwd);
    void moveLeft(uint8_t speed);
    void moveRight(uint8_t speed);
    void stopLeft();
    void stopRight();
private:
    uint8_t m_leftFwdPin;
    uint8_t m_rightFwdPin;
    uint8_t m_leftBwdPin;
    uint8_t m_rightBwdPin;

};

#endif

