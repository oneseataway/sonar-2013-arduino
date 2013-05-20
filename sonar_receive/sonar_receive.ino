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



//------------------------------------------------------------------------
//  Properties
//------------------------------------------------------------------------
int MESSAGE[4] = { 2,5,7,8 };

// buffer should be long enough to hold the desired values
// as well as the starter marker
//i.e. M00000
byte buff[5] = { 'M', 0,0,0,0 };

MultiTimer mtimer;
//Timer timer;



//------------------------------------------------------------------------
//  Methods
//------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  for(int i=0; i<4; i++) pinMode(MESSAGE[i], OUTPUT);     
  
  /*
   *  timer
   */
  float interval[2] = { 1000, 500 };
  mtimer.setFreq( interval );
}

//------------------------------------------------------------------------
void loop() {
  while( Serial.available() >= 5 ) {
    switch( byte(Serial.read()) ) {
      
      case 'M': //starter marker
        buff[0] = Serial.read();
        for(int i=1; i<5; i++) buff[i] = Serial.read();

      break;
    }
  }

  /*
   *  Output
   */
  for(int i=0; i<4; i++) {
    if(buff[i] == 0) digitalWrite( MESSAGE[i], LOW );
    else if(buff[i] == 1) digitalWrite( MESSAGE[i], HIGH );
  }

}


//------------------------------------------------------------------------
void nightProgram() {



}

