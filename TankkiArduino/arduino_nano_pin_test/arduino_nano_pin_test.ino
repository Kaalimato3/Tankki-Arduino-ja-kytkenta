#include <Servo.h>

#define ampuPin 3
#define laserPin 11
#define ledPin 7
#define servoPin 4

int korko = 0;
Servo servo;

bool ampu = 0, konsu = 0, laser = 0, nostoylos = 1, nostoalas = 0;

void setup() {
  pinMode(ampuPin, OUTPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
  if(millis()%10000 > 5000)
    konsu = !konsu;
  
  if(millis()%10000 > 2000)
    laser = !laser;
  
  if(millis()%10000 > 5000)
    ampu = !ampu;
  
  if(millis()%1000 < 500)
    nostoylos = !nostoylos;
  
  if(millis()%1000 > 500)
    nostoalas = !nostoalas;
  
  if(nostoylos && korko > 0)
    korko--;
  if(nostoalas && korko < 180)
    korko++;
  servo.write(korko);
  digitalWrite(ampuPin, ampu);
  digitalWrite(ledPin, konsu);
  digitalWrite(laserPin, laser);
}
