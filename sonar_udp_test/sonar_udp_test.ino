/*
 *  Sonar UDP Test
 * 
 *  Ken Frederick
 *  ken.frederick@gmx.de
 *
 *  http://cargocollective.com/kenfrederick/
 *  http://kenfrederick.blogspot.com/
 *
 *  receive messages via UDP
 * 
 */

//------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "MultiTimer.h"
#include "Timer.h"



//------------------------------------------------------------------------
//  Properties
//------------------------------------------------------------------------
/*
 *  Ethernet
 */
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x19 };

IPAddress arduinoIP(192, 168, 1, 177); // desired IP for Arduino
unsigned int arduinoPort = 8888;       // port of Arduino

IPAddress receiverIP(192, 168, 1, 135); // IP of udp packets receiver
unsigned int receiverPort = 6000;       // port to listen on my PC

EthernetUDP Udp;
char packetBuffer[ UDP_TX_PACKET_MAX_SIZE ];
char replyBuffer[] = "acknowledged";


/*
 *  Timer
 */
MultiTimer mtimer;
//Timer timer;



//------------------------------------------------------------------------
//  Methods
//------------------------------------------------------------------------
void setup() {
  /*
   *  Serial
   */
  Serial.begin(9600);
  
  /*
   *  Ethernet
   */
  Ethernet.begin(mac, arduinoIP);
  Udp.begin(arduinoPort);


  /*
   *  timer
   */
  float interval[2] = { 1000, 500 };
  mtimer.setFreq( interval );
}

//------------------------------------------------------------------------
void loop() {

  int packetSize = Udp.parsePacket();
  if(packetSize) {
//
//    Serial.print("Received packet of size ");
//    Serial.println(packetSize);
//    Serial.print("From ");
//
//    IPAddress remote = Udp.remoteIP();
//    for (int i =0; i < 4; i++) {
//      Serial.print(remote[i], DEC);
//      if (i < 3) {
//        Serial.print(".");
//      }
//    }
//
//    Serial.print(", port ");
//    Serial.println(Udp.remotePort());
//
//    // read the packet into packetBufffer
//    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
//    Serial.println("Contents:");
//    Serial.println(packetBuffer);
//
//    // send a reply, to the IP address and port that sent us the packet we received
//    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//    Udp.write(replyBuffer);
//    Udp.endPacket();
  }
  else {
    nightProgram();
  }

  delay(500);
}


//------------------------------------------------------------------------
void nightProgram() {

  if( mtimer.getTrigger() ) {
    digitalWrite(8, HIGH);
  }
  else {
    digitalWrite(8, LOW);
  }

}


