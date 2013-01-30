#include "DHT.h"
#include <stdio.h>
#include <string.h>
#include <DS1302.h>


#define DHTPIN 2     // what pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
float h,t;

#define VENTOLA 3;
#define PL 4;
#define T_AMB 20;
#define H_MAX 70;
#define H_MIN 30;
#define OROLOGIO 4;


void setup() {
  Serial.begin(9600);  
  dht.begin();
}

void loop() {
  
   h = dht.readHumidity();
   t = dht.readTemperature();
   
   if(h>H_MAX || t > T_AMB){
      digital.write(VENTOLA,HIGH);
      pausaLavoro(LOW);
   }
      
   if(t<=T_AMB)
     digital.write(VENTOLA,LOW);
     
   if(h<H_MIN)
       pausaLavoro(HIGH);
   
   delay(5000);
  }
  
 void pausaLavoro(int stato){
   if(stato==HIGH)
   digital.write(PL,HIGH);
   else
   digital.write(PL,LOW);
   
 }
}
