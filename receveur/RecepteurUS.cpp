#include "RecepteurUS.h"



RecepteurUS::RecepteurUS()
{
  pinAnalog = A0;
  time1 = 0;
  time0 = 0;
}

RecepteurUS::~RecepteurUS()
{
}

void RecepteurUS::readPacket()
{
  if(analogRead(pinAnalog)>5)
  {
     time1 = micros();
     return;
  }
  else
  {
    return;
  }
}

bool RecepteurUS::readPacket(unsigned long waitTime)
{
  unsigned long start =  micros();
  bool ack = false;
  while (((micros()-start) < waitTime) && !(ack))
  {
    if (analogRead(pinAnalog)>5)
    {
       time1 = micros();
       ack = true;    
    }
  }
  return ack;
}

unsigned long RecepteurUS::dt()
{
  return (time1 - time0);
}

void RecepteurUS::setPin(uint8_t pin)
{
  pinAnalog = pin;
}

void RecepteurUS::setTop()
{
  time0=micros();
}
