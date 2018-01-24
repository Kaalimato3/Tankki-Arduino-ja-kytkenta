#include <Servo.h>
#include <SoftwareSerial.h>

#define LEDBIT   0b00010000
#define LASERBIT 0b00001000
#define AMPUBIT  0b00000100
#define YLOSBIT  0b00000010
#define ALASBIT  0b00000001

#define ampuPin 3
#define laserPin 11
#define ledPin 7
#define servoPin 4

#define rxPin 6
#define txPin 5

bool ampu = 0, konsu = 0, laser = 0, nostoylos = 0, nostoalas = 0;
int akku[4];
byte cmd[12];
int korko = 0;
Servo servo;
SoftwareSerial ss(rxPin, txPin);
long time = 0;

void setup() {
  ss.begin(9600);
  Serial.begin(38400);
  pinMode(ampuPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
  
  if(ss.available() > 11 && ss.peek() == 1)
  {
    for(int i = 0; i < 12; i++)
    {
      cmd[i] = ss.read();
    }
    konsu = cmd[2] & LEDBIT;
    laser = cmd[2] & LASERBIT;
    ampu = cmd[2] & AMPUBIT;
    nostoylos = cmd[2] & YLOSBIT;
    nostoalas = cmd[2] & ALASBIT;
  }
  if(nostoylos && korko > 0)
    korko--;
  if(nostoalas && korko < 180)
    korko++;
  servo.write(korko);
  digitalWrite(ampuPin, ampu);
  digitalWrite(ledPin, konsu);
  digitalWrite(laserPin, laser);
  if(time + 500 < millis())
  {
    time = millis();
    for ( int i = 0; i < 12; i++)
    {
      Serial.print(cmd[i]);
      Serial.print("\t");
    }
    Serial.println(" ");
  }
}
