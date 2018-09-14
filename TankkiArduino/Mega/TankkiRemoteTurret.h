// TankkiRemoteTurret.h

#ifndef _TANKKIREMOTETURRET_h
#define _TANKKIREMOTETURRET_h


#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
#else
    #include "WProgram.h"
#endif

#define CANNON_BIT	0b00000001
#define LASER_BIT	0b00000010
#define MG_BIT		0b00000100

struct TurretMessage {

};


struct TurretCommand {
    uint8_t elevation;
    bool cannon = 0;
    bool laser = 0;
    bool mg = 0;
};

class TankkiRemoteTurret 
{
public:
    TankkiRemoteTurret(HardwareSerial &iface);
    void sendMsg(TurretCommand cmd);
    TurretMessage readMsg();
private:
    HardwareSerial& m_iface;
};
#endif

