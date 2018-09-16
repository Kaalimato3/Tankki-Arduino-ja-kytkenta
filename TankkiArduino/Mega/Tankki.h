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
    Tankki(uint8_t leftFwd, uint8_t leftBwd, uint8_t rightFwd, uint8_t rightBwd, uint8_t turretCCWPin, uint8_t turretCWPin);

    void begin();

    void moveLeft(uint8_t speed);
    void moveRight(uint8_t speed);
    void stopLeft();
    void stopRight();
    void turnTurret(uint8_t val);
    void stopTurret();
private:
    uint8_t m_leftFwdPin;
    uint8_t m_rightFwdPin;
    uint8_t m_leftBwdPin;
    uint8_t m_rightBwdPin;
    uint8_t m_turretCCWPin;
    uint8_t m_turretCWPin;

};

#endif

