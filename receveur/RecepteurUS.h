#ifndef RECEPTEURUS
#define RECEPTEURUS

#include "Arduino.h"


/**@brief Classe permettant d'emettre des paquets contenant les infos qu'on veut transmettre avec le module xBee */
class RecepteurUS 
{
 public:
 
  /**@brief constructeur de la classe */
  RecepteurUS();
  /**@brief déstructeur de la classe */
  ~RecepteurUS();
  /**@brief Fixe le numéro de la pin utilisée */
  void setPin(uint8_t pinAnalog);
  /**@brief Permet de demander au recepteur d'écouter */
  void readPacket();
  /**@brief Permet de demander au recepteur d'écouter pendant un temps waitTime en microseconde */
  /**@return Returne un booléen indiquant si un paquet a été reçu ou non */
  bool readPacket(unsigned long waitTime);
  /**@brief Returne le temps de propagation de l'onde*/
  unsigned long dt();  
// private:
  /**@brief pinAnalogique utilisée pour connecter le recepteur US*/
  uint8_t pinAnalog;
  /**@brief timestamps d'arrivé de l'onde US en microseconde*/
  unsigned long time1;
  /**@brief timestamps d'arrivé de l'onde HF en microseconde*/
  unsigned long time0;
  /**@brief Définie le top départ */
  void setTop();
};


//TODO Ajouter le numéro de la balise qui émet

#endif
