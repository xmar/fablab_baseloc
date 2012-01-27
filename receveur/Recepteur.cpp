#include "Recepteur.h"
#include <XBee.h>


Recepteur::Recepteur()
{
  xBee = XBee();
  XBeeResponse();
  Rx16Response rx16 = Rx16Response();
  data = (uint8_t*) malloc (sizeof(uint8_t)*1);
}

Recepteur::~Recepteur()
{
 free(data); 
}

void Recepteur::begin(long baud)
{
  xBee.begin(baud);
}

void Recepteur::readPacket()
{
  xBee.readPacket();
}

bool Recepteur::responseIsAvailable()
{
 bool isAvailable = xBee.getResponse().isAvailable();
 if (isAvailable)
 {
   xBee.getResponse().getRx16Response(rx16);
   data = rx16.getData();
 }
  return isAvailable;
}

unsigned int Recepteur::traitementReponse()
{
  if (data[0]==0xA1)
  {
    uint8_t* timeT = (uint8_t*) &time;
    for (int i = 0; i<4; i++)
    {
      timeT[i] = data[1+i];
    }
    uint8_t* timeNbT = (uint8_t*) &timeNb;
    for (int i = 0; i<4; i++)
    {
      timeNbT[i] = data[5+i];
    }
     return 1; // Temps
  }
  else if(data[0]==0xE1)
  {
    if (data[1]==0xE2)
    {
      uint8_t* timeNbT = (uint8_t*) &timeNb;
      for (int i = 0; i<4; i++)
      {
        timeNbT[i] = data[2+i];
      }
      return 2; //TOP départ
    }
    else
    {
      return 0; //Erreur
    }
  }
  else
  {
    return 0; //Erreur
  }
}
