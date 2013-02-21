#include "DHT.h"
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include <SPI.h>
#include <Ethernet.h>

// *** ETHERNET SHIELD e CONNETTIVITA'
  EthernetClient client;
  
  byte mac[] = {  0x90, 0xA2, 0xDA, 0x0D, 0xD3, 0x5C };
  IPAddress ip(192,168,1,94);
  String ipLocale="";
  char serverName[] = "www.serrarduino.altervista.org";
  String postString="password=serrarduino1994&local_ip=";
  int postLength=0; 
  
  EthernetServer server(1994);
  char c;
// *** FINE ETHERNET SHIELD

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
  
  //### tenta l'assegnazione di indirizzo IP
  
 // Ethernet.begin(mac,ip);
 // Serial.println(ip);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");}
    else Serial.println("Indirizzo ottenuto correttamente dal DHCP");
    
    
   //### salvo stringa con ip
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    ipLocale+=String(Ethernet.localIP()[thisByte], DEC);
    ipLocale+="."; 
  }
   ipLocale=ipLocale.substring(0, ipLocale.length()-1);
  //###
  
  //### aggiungo local ip a stringa per POST e la misuro
    postString+=ipLocale;
    postLength=postString.length();
  //###
    delay(1000);
    //### si connete al server e comunica gli indirizzi
    
  if (client.connect(serverName, 80)) {
    Serial.println("Connected with your SerrArduino Server");
    
    // HTTP request for set IP address
    client.println("POST /ip_getter.php HTTP/1.1");
    client.println("Host: www.serrarduino.altervista.org");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: "+String(postLength,DEC));
    client.println();
    client.println(postString);
    client.println();
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("Connection failed, IP address not sent.");
  }
  //###
  
  //### inizializzazione come server
  server.begin();
}

void loop() {
  
  
  //### stampa la risposta HTTP dell'invio IP
  
 /* if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    client.stop();
  }*/
  
  //### legge la temperatura dell'ambiente
  
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
     /*   time = rtc.time();
       if(time==corrente && digitalRead(POMPA)){
         digitalWrite(POMPA,HIGH);
        // corrente=irrigazione[i].spegni;
       }
       if(time==corrente && !digitalRead(POMPA)){
         digitalWrite(POMPA,LOW);
        // corrente=irrigazione[++i].accendi;
       }*/
       
    //### controlla se ha ricevuto una richiesta dal client
  
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

          // output the page
            client.println("<h1>Pannello di controllo</h1>");
            client.println("<p>Questa pagina rappresenta il pannello di controllo della serra.</p>");
          
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}
