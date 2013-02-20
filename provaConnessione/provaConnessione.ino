/*
  DNS and DHCP-based Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 modified 12 April 2011
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0x90, 0xA2, 0xDA, 0x0D, 0xD3, 0x5C };
char serverName[] = "www.serrarduino.altervista.org";
String ipLocale="";
String postString="password=serrarduino1994&local_ip=";
int postLength=0;

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // start the serial library:
  Serial.begin(9600);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }
  
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  
  
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
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  
  if (client.connect(serverName, 80)) {
    Serial.println("connected");
    
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
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while(true);
  }
}

