#include "DHT.h"
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
//#include <Ethernet.h>

// *** SENSORE TEMPERATURA 
    #define DHTPIN 2     // what pin we're connected to
    
    #define DHTTYPE DHT22   // DHT 22  (AM2302)
    
    // Connect pin 1 (on the left) of the sensor to +5V
    // Connect pin 2 of the sensor to whatever your DHTPIN is
    // Connect pin 4 (on the right) of the sensor to GROUND
    // Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
    
    DHT dht(DHTPIN, DHTTYPE);
    float h,t;
// *** FINE SENSORE TEMPERATURA

// *** DISPOSITIVO RTC
  // Set the appropriate digital I/O pin connections
    uint8_t CE_PIN   = 5;
    uint8_t IO_PIN   = 6;
    uint8_t SCLK_PIN = 7;
    
   // Create a DS1302 object
      DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
      Time time;
// *** FINE DISPOSITIVO RTC

// *** IRRIGAZIONE
  // dato un vettore ordinato di irrigazioni, l'ora corrente è quella che deve essere effettuata. Tipo "sveglia" in Assembly
    Time corrente;
// *** FINE IRRIGAZIONE

#define VENTOLA_1 22 //pin della ventola 1
#define VENTOLA_2 23 //pin della ventola 2
//#define OROLOGIO 24 //pin dell'RTC
#define UMIDIFICATORE 25 //pin dell'umidificatore
#define POMPA 26//pin della pompa (o del relè associato)
#define RISCALDAMENTO 27 //pin della resistenza riscaldante (o relè associato)
#define LIVELLO 28//pin del sensore di livello serbatoio

float tAmb=20;
float hMax=70;
float hMin=30;


void setup() {
  Serial.begin(9600);  
  dht.begin();
  
}

void loop() {
  
  //### legge la temnperatura dell'ambiente
  
   h = dht.readHumidity();
   t = dht.readTemperature();
   
   //### valuta come agire per stabilizzare il microclima
           if(h>hMax || t > tAmb){
              digitalWrite(VENTOLA_1,HIGH);
              digitalWrite(VENTOLA_2,HIGH);
              digitalWrite(UMIDIFICATORE,LOW);
           }
              
           if(t<=tAmb){
             digitalWrite(VENTOLA_1,LOW);
             digitalWrite(VENTOLA_2,LOW);
           }
           if(t+3<=tAmb){
             digitalWrite(VENTOLA_1,LOW);
             digitalWrite(VENTOLA_2,LOW);
             digitalWrite(RISCALDAMENTO,HIGH);
           }
             
           if(h<hMin){
               digitalWrite(UMIDIFICATORE,HIGH);
               digitalWrite(VENTOLA_1,LOW);
               digitalWrite(VENTOLA_2,LOW);
           }
   
   //### invia al sito dell'applicazione le variazioni dell'ambiente
       
   //### legge l'ora attuale dal dispositivo RTC e controlla la schedulazione delle irrigazioni
        time = rtc.time();
       if(time==corrente && digitalRead(POMPA)){
         digitalWrite(POMPA,HIGH);
        // corrente=irrigazione[i].spegni;
       }
       if(time==corrente && !digitalRead(POMPA)){
         digitalWrite(POMPA,LOW);
        // corrente=irrigazione[++i].accendi;
       }
       
     
} 
