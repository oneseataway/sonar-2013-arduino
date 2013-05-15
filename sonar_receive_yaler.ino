/*
 *  Sonar Receive Test
 * 
 *  Ken Frederick
 *  ken.frederick@gmx.de
 *
 *  http://cargocollective.com/kenfrederick/
 *  http://kenfrederick.blogspot.com/
 *
 *  receive messages from processing
 * 
 */

//------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------
#include "MultiTimer.h"
#include "Timer.h"

// Yaler includes
#include <SPI.h>
#include <Ethernet.h>
#include <TextFinder.h>
#include <YalerEthernetServer.h>
#include <stdlib.h>


//------------------------------------------------------------------------
//  Properties
//------------------------------------------------------------------------
int MESSAGE[4] = { 2,4,7,12 };

// buffer should be long enough to hold the desired values
// as well as the starter marker
//i.e. M00000
byte buff[5] = { 'M', 0,0,0,0 };

MultiTimer mtimer;
//Timer timer;

// Yaler stuff

char endOfHeaders[] = "\r\n\r\n";
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF }; // CHANGE THIS IF YOU'VE GOT MORE THAN ONE Arduino
YalerEthernetServer server("try.yaler.net", 80, "gsiot-ypf7-s06d");



//------------------------------------------------------------------------
//  Methods
//------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Acquiring IP address...");
  
  for(int i=0; i<4; i++) pinMode(MESSAGE[i], OUTPUT);     
  
  // Yaler stuff
  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP failed.");
  } else {
    Serial.println(Ethernet.localIP());
    server.begin();
  }
  
  /*
   *  timer
   */
  float interval[2] = { 1000, 500 };
  mtimer.setFreq( interval );
}

//------------------------------------------------------------------------
void loop() {
  // Yaler stuff
  EthernetClient client = server.available();

  if (client && client.connected()) 
  {
    TextFinder finder(client); // helper to read request
    // Receive first line of HTTP request, which looks like this:
    // Request-Line = Method SP Request-URI SP HTTP-Version CRLF
    // see http://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
    char requestMethodBuffer[8];
    char requestUriBuffer[64];
    finder.getString("", " ", requestMethodBuffer, 8); // read to first SP
    finder.getString("", " ", requestUriBuffer, 64); // read on, to second SP
    String requestMethod = String(requestMethodBuffer);
    String requestUri = String(requestUriBuffer);
    Serial.print(requestMethod);
    Serial.print(" ");
    Serial.println(requestUri); 
    // receive HTTP request headers, ignore all except "Content-Length"
    int contentLength = 0;
    if(finder.findUntil("Content-Length", endOfHeaders)) 
    {
      contentLength = finder.getValue();
      finder.find("\n\r\n");
    }
    
     if (requestMethod.equals("GET") && requestUri.equals("/")) 
     {
        sendResponse(client, 10);
     }
     else if (requestMethod.equals("GET") && requestUri.equals("/test")) 
     {
        sendResponse(client, 5);
     }
     
  }
  else 
  {
    Serial.println("Error with the connection");
    Serial.println("disconnecting.");
    client.stop();
  }
  
  

}


//------------------------------------------------------------------------
void nightProgram() {



}

//------------------------------------------------------------------------
// Yaler request functions
//------------------------------------------------------------------------

void sendResponse(EthernetClient client, int parameter) 
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<h1>One chair away</h1>");
  
   //------------------------------------------------------------
   // TODO
   //------------------------------------------------------------
   
    switch( byte(parameter) ) {
      
      case 'M': //starter marker
        buff[0] = parameter;
        for(int i=1; i<5; i++) buff[i] = parameter-i;

      break;
    }
 
  
    /*
     *  Output
     */
    for(int i=0; i<4; i++) {
      if(buff[i] == 0) digitalWrite( MESSAGE[i], LOW );
      else if(buff[i] == 1) digitalWrite( MESSAGE[i], HIGH );
    }
   
   //------------------------------------------------------------
   // TODO
   //------------------------------------------------------------
  
  
}

