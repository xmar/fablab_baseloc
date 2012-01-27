#include <XBee.h>
#include "Emetteur.h"


unsigned long start = millis();

int statusLed = 11;
int errorLed = 12;
int usLed = 10;


// Initialisation de l'emetteur
Emetteur emetteur = Emetteur();






void flashLed(int pin, int times, int wait)
{
    
    for (int i = 0; i < times; i++) {
      digitalWrite(pin, HIGH);
      delay(wait);
      digitalWrite(pin, LOW);
      
      if (i + 1 < times) {
        delay(wait);
      }
    }
}


void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(usLed, OUTPUT);
  
 emetteur.setAddress( 0xABC1 );  
 emetteur.begin(9600);
}


void loop() {
   
   // start transmitting after a startup delay.  Note: this will rollover to 0 eventually so not best way to handle
     if (millis() - start > 5000) {


      emetteur.sendTop();
      flashLed(statusLed, 1, 100);
     tone(usLed,40000);
     delay(500);
     noTone(usLed);
     
    }
  
    delay(500);
}
