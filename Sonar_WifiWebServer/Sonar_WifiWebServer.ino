/*
  WiFi Web Server
 
 A simple web server that shows the value of the analog input pins.
 using a WiFi shield.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 Circuit:
 * WiFi shield attached
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <WiFi.h>
#include <TextFinder.h>


char ssid[] = "Apparat";      //  your network SSID (name) 
char pass[] = "Jint.Ernk";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char endOfHeaders[] = "\r\n\r\n";
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF }; // CHANGE THIS IF YOU'VE GOT MORE THAN ONE Arduino

int MESSAGE[5] = { 2, 5, 7, 8 };
byte buff[8];
byte data[8] = {0, 0, 0, 0, 0, 0, 0, 0};

WiFiServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  
  if (client &&  client.connected()) 
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    //while (client.connected())
   
      if (client.available()) 
      {
        TextFinder finder(client);
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
    
       if (requestMethod.equals("GET") && !requestUri.equals(""))
       {
          convertStringToByteArray(requestUri);
    
         // printing the byte array 
         for(int i=0; i<8; i++) 
         {
              Serial.print(i);
              Serial.print(" - ");
              Serial.println(data[i]);
         } 
         
         sendResponse(client, data);
       }

    }
    else
    {
      Serial.println("Client not available");
    }
    
    Serial.println("client disonnected");

  }
  else
  {
    //Serial.println("Client not connected...");
  }

  // give the web browser time to receive the data
  delay(1);
  // close the connection:
  client.stop();
    
}




//------------------------------------------------------------------------



//------------------------------------------------------------------------
// From Yaler request functions
// Date: 20 / 5 / 2013
// Author: Marc Pous
//------------------------------------------------------------------------

void sendResponse(WiFiClient client, byte buff[]) 
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<h1>One chair away</h1>");

  
  Serial.println("Processing the signal");
  /*
  for(int i=0; i<8; i++) 
  {
    Serial.print(i);
    Serial.print(" - ");
    Serial.println(parameter[i]);
    buff[i] = parameter[i];
  }
  */
  
    /*
     *  Output signal
     */
    Serial.println("Output");
    for(int i=0; i<8; i++) 
    { 
      Serial.print(i);
      Serial.print(" - ");
      Serial.println(buff[i]);
      
      // TODO @Simo
      // Apply PWM here!

      if(buff[i] == 0) 
      {
        digitalWrite( MESSAGE[i], HIGH );
        Serial.print(MESSAGE[i]);
        Serial.println(" sensor LOW");
      }
      else if(buff[i] == 1) 
      {
        digitalWrite( MESSAGE[i], LOW );
        Serial.print(MESSAGE[i]);
        Serial.println(" sensor HIGH");
      }
    }

    Serial.println("Done");  

}


//------------------------------------------------------------------------
// Converting requestUri string into Byte Array
// Date: 20 / 5 / 2013
// Author: Marc Pous
//------------------------------------------------------------------------

void convertStringToByteArray(String str)
{
  int numArgs = 0;
  char charBuffer[16];
  int beginIdx = 1;
  
  String arg;
  
  int idx = str.indexOf("-");

   while (idx != -1)
   {
    arg = str.substring(beginIdx, idx);
    Serial.println(arg);
    arg.toCharArray(charBuffer, 16);
  
   // add error handling for atoi:
    data[numArgs++] = (byte) atoi(charBuffer);
    beginIdx = idx + 1;
    idx = str.indexOf("-", beginIdx);
   }

   data[numArgs++] = (byte) str.substring(beginIdx).toInt();
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

