#include "Tankki.h"


Tankki::Tankki(uint8_t turretCCWPin, uint8_t turretCWPin) :
    m_turretCCWPin(turretCCWPin), m_turretCWPin(turretCWPin)
{
}

void Tankki::begin() 
{
    Serial.println("Tankki init");
    pinMode(m_turretCCWPin, OUTPUT);
    pinMode(m_turretCWPin, OUTPUT);
}

void Tankki::turnTurret(uint8_t val)
{
    //Serial.print("turnTurret val: ");
    //Serial.print(val);
    //Serial.print("\t");
    if (val > 127) {
        //Serial.print("CW");
        analogWrite(m_turretCCWPin, 0);
        analogWrite(m_turretCWPin, map(val, 127, 254, 10, 255));
    }
    else if (val < 127) {
        //Serial.print("CCW");
        analogWrite(m_turretCWPin, 0);
        analogWrite(m_turretCCWPin, map(val, 127, 0, 10, 255));
    }
    else {
        //Serial.print("0");
        stopTurret();
    }
}

void Tankki::stopTurret()
{
    analogWrite(m_turretCCWPin, 0);
    analogWrite(m_turretCWPin, 0);
}