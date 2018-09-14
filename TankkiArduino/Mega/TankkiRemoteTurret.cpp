// 
// 
// 

#include "TankkiRemoteTurret.h"

TankkiRemoteTurret::TankkiRemoteTurret(HardwareSerial &iface) :
    m_iface(iface)
{
}

void TankkiRemoteTurret::sendMsg(TurretCommand cmd)
{
    uint8_t bits = 0b00000000;
    bits = bits | (CANNON_BIT * cmd.cannon); // Set cannon control bit
    bits = bits | (LASER_BIT * cmd.laser);   // Set laser control bit
    bits = bits | (MG_BIT * cmd.mg);         // Set MG control bit
    m_iface.write(1);
    m_iface.write(255);
    m_iface.write(cmd.elevation);
    m_iface.write(bits);
}

TurretMessage TankkiRemoteTurret::readMsg()
{
    return TurretMessage();
}
