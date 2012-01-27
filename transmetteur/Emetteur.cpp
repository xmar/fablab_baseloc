#include "Emetteur.h"
#include <XBee.h>



Emetteur::Emetteur()
{
  xBee = XBee();
  lengthPayload = 1;
  payload = (uint8_t*) malloc (sizeof(uint8_t)*lengthPayload);
  address = 0xFFFF;
  tx = Tx16Request(address, payload, sizeof(uint8_t)*lengthPayload);
  txStatus = TxStatusResponse();
  nbSecance = 0;
}

/*Emetteur::Emetteur(unit16_t address, unsigned int lengthPayload)
{
  xBee = XBee();
  this.lengthPayload = lengthPayload;
  payload = new uint8_t[lengthPayload];
  this.address = address;
  tx = Tx16Request(address, payload, sizeof(payload));
  txStatus = TxStatusResponse();
}*/

Emetteur::~Emetteur()
{
  free (payload);
}

void Emetteur::setAddress(uint16_t address)
{
  this->address = address;
}

uint16_t Emetteur::getAddress()
{
 return  address;
}

void Emetteur::setPayload(unsigned int lengthPayload, uint8_t* nPayLoad)
{
  this->lengthPayload = lengthPayload;
  delete payload;
  payload = nPayLoad;
  
}

void Emetteur::initPayLoad(unsigned int lengthPayload)
{
  this->lengthPayload = lengthPayload;
  free (payload);
  payload = (uint8_t*) malloc (sizeof(uint8_t)*lengthPayload);

}


void Emetteur::sendTime(unsigned long int time, unsigned long int timeNb)
{
  initPayLoad(9);
  tx = Tx16Request(address, payload, lengthPayload);
  payload[0]=0xA1;
  uint8_t* timeT = (uint8_t*) &time;
  for (unsigned int i=0; i < 4; i++)
  {
     payload[1+i] = timeT[i]; 
  }
  uint8_t* timeNbT = (uint8_t*) &timeNb;
  for (unsigned int i=0; i < 4; i++)
  {
    payload[5+i] = timeNbT[i];
  }

  xBee.send(tx);
}

void Emetteur::begin(long baud)
{
  xBee.begin(baud);
}

void Emetteur::sendTop()
{
  initPayLoad(6);
  tx = Tx16Request(address, payload, lengthPayload);
  payload[0]=0xE1;
  payload[1]=0xE2;
  uint8_t* timeNbT = (uint8_t*) nbSecance;
  for (int i = 0; i<4;i++)
  {
    payload[2+i]= timeNbT[i];
  }
  xBee.send(tx);
  nbSecance++;
}
