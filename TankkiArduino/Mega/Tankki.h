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
    Tankki(uint8_t turretCCWPin, uint8_t turretCWPin);

    virtual void begin();

    virtual void turnTurret(uint8_t val);
    virtual void stopTurret();
private:
    uint8_t m_turretCCWPin;
    uint8_t m_turretCWPin;

};

#endif

