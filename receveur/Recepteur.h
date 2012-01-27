#ifndef RECEPTEUR
#define RECEPTEUR

#include <XBee.h>
#include "Arduino.h"


/**@brief Classe permettant d'emettre des paquets contenant les infos qu'on veut transmettre avec le module xBee */
class Recepteur 
{
 public:
 
  /**@brief constructeur de la classe */
  Recepteur();
  /**@brief déstructeur de la classe */
  ~Recepteur();
  /**@brief À lancer dans le setup() pour initialiser le XBee*/
  void begin(long baud);
  /**@brief Permet de demander au recepteur d'écouter */
  void readPacket();
  /**@brief Permet d'indiquer si une réponse est disponible */
  /**@return Retourne true si un paquet est disponible en lecture, false sinon */
  bool responseIsAvailable();
  /**@brief Traite la réponse et met les resultats dans la bonne variable*/
  /**@return 0 si erreur, 1 si reception d'un Temps*/
  unsigned int traitementReponse();
  /**@brief Contient le dernier temps reçu */
  unsigned long int time;
  /**@brief Contient le dernier numéro de sécance du temps reçu */
  unsigned long int timeNb;
  
 private:
  /**@brief xBee est un objet XBee permettant d'utiliser le module xBee*/
  XBee xBee;
  XBeeResponse response;
  Rx16Response rx16;
  uint8_t* data;
};


//TODO Ajouter le numéro de la balise qui émet

#endif
