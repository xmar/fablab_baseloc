#ifndef EMETTEUR
#define EMETTEUR

#include <XBee.h>
#include "Arduino.h"


/**@brief Classe permettant d'emettre des paquets contenant les infos qu'on veut transmettre avec le module xBee */
class Emetteur 
{
 public:
 
  /**@brief constructeur de la classe */
  Emetteur();
  /**@brief déstructeur de la classe */
  ~Emetteur();
  /**@brief Set the address with the address parameter value*/
  /**@param address Address to send the messages*/
  void setAddress(uint16_t address);
  /**@brief Pour obtenir l'adresse du destinatère du message*/
  uint16_t getAddress();
  /**@brief To set a new payLoad*/
  /**@param lengthPayload The new length for the payLoad */
  /**@param newPayLoad The new payLoad to set*/
  void setPayload(unsigned int lengthPayload, uint8_t* newPayLoad);
  /**@brief Pour initialiser un payload de lengthPayload octets à 0*/
  /**@param lengthPayload The new length for the payLoad */
  void initPayLoad(unsigned int lengthPayload);
  /**@brief Envoie à l'hote ayant l'adresse address un paquet contenant 1 octet informant qu'on envoie le temps (0xA1), 4 octets codant le temps suivit de 4 octets codant le numéro de sécance.*/
  /**@param time Timestamp de réception codé sur 4 octets */
  /**@param timeNb Numéro de sécance codé sur 4 octets*/
  void sendTime(unsigned long int time, unsigned long int timeNb);
  /**@brief À lancer dans le setup() pour initialiser le XBee*/
  void begin(long baud);
  /**@brief Permet d'initialiser le t0 pour calculer les deltatT avec la balise principal */
  void sendTop();
 
  
 private:
  /**@brief xBee est un objet XBee permettant d'utiliser le module xBee*/
  XBee xBee;
  /**@brief address contient l'adresse de la destination du message*/
  uint16_t address;
  /**@brief payload est un pointeur vers la tableau d'octee qu'on souhaite transmettre*/
  uint8_t* payload;
  /**@brief lengthPayload contient la taille de en octet de la payload */
  unsigned int lengthPayload;
  /**@brief tx est un objet de type Tx16Request qui sera envoyé par l'objet xBee*/
  Tx16Request tx;
  /**@brief txStatus est un objet de type TxStatusResponse permettant de reçevoir l'aquitement de notre message*/
  TxStatusResponse txStatus;
  
  int nbSecance;
  
};





#endif
