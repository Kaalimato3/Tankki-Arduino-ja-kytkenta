#define LEDBIT   0b00010000
#define LASERBIT 0b00001000
#define AMPUBIT  0b00000100
#define YLOSBIT  0b00000010
#define ALASBIT  0b00000001

byte nanocmd[12] =
{ 1, 2, 0b00000000, 'a', 0, 'b', 0, 'c', 0, 'd', 0, 'f' };

bool ampu = 0, konsu = 0, laser = 0, nostoylos = 1, nostoalas = 0;
int akku[4] = { 200, 200, 200, 200 };

void setup() {
  Serial2.begin(9600);
  Serial.begin(38400);
}

void loop() {
  sendCmd();
  delay(500);
  laser = !laser;
  konsu = !konsu;
}

void sendCmd()
{
  if(ampu)
    nanocmd[2] = nanocmd[2] | LEDBIT;
  else
    nanocmd[2] = nanocmd[2] & LEDBIT;
  if(ampu)
    nanocmd[2] = nanocmd[2] | LASERBIT;
  else
    nanocmd[2] = nanocmd[2] & LASERBIT;
  if(ampu)
    nanocmd[2] = nanocmd[2] | AMPUBIT;
  else
    nanocmd[2] = nanocmd[2] & AMPUBIT;
  if(ampu)
    nanocmd[2] = nanocmd[2] | YLOSBIT;
  else
    nanocmd[2] = nanocmd[2] & YLOSBIT;
  if(ampu)
    nanocmd[2] = nanocmd[2] | ALASBIT;
  else
    nanocmd[2] = nanocmd[2] & ALASBIT;
  for (int i = 0; i < 4; i++)
  {
    nanocmd[4 + i * 2] = akku[i];
  }
  
  for(int i = 0; i < 12; i++)
  {
    Serial.write(nanocmd[i]);
    Serial2.write(nanocmd[i]);
  }
}
