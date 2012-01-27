#include <XBee.h>
#include "Recepteur.h"
#include "RecepteurUS.h"

int statusLed = 12;
int errorLed = 12;
int dataLed = 10;
int UsLed = 11;

Recepteur recepteur = Recepteur();
RecepteurUS recepteurUS = RecepteurUS();

void flashLed(int pin, int times, int wait) {
    
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
  pinMode(dataLed,  OUTPUT);
  pinMode(UsLed, OUTPUT);
  
  // start serial
  recepteur.begin(9600);
  recepteurUS.setPin(A0);
  flashLed(statusLed, 3, 50);
}

// continuously reads packets, looking for RX16 or RX64
void loop() {
  recepteur.readPacket();
  if(recepteur.responseIsAvailable())
  {
    if (recepteur.traitementReponse()==1)
    {
      flashLed(statusLed, 1, 10);
/*      Serial.println("Time : ");
      Serial.print("timestamp : ");
      Serial.println((int) recepteur.time);
      Serial.print("Numero de secance : ");
      Serial.println((int) recepteur.timeNb);
      Serial.println("-----------");
*/
    }
    else if(recepteur.traitementReponse()==2)
    {
      recepteurUS.setTop();
     if (recepteurUS.readPacket(10000))
      {
        flashLed(statusLed, 1, 10);
        unsigned long dt = recepteurUS.dt();
        flashLed(UsLed, 1, 10);
        Serial.print((unsigned long int)recepteur.timeNb,DEC);
        Serial.print(" ");
        Serial.print((double) (dt*340./1000000.),3);
        Serial.print(" ");
       }
       else
       {
         flashLed(statusLed, 5, 10);
         Serial.println(">>");
       }
    }
    else
    {
        flashLed(errorLed, 10, 50);
    }
  }
  else
  {
   // flashLed(dataLed,2,50);
  }
  delay(100);

}
