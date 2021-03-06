/*
 *  Timer
 * 
 *  Ken Frederick
 *  ken.frederick@gmx.de
 *
 *  http://cargocollective.com/kenfrederick/
 *  http://kenfrederick.blogspot.com/
 *
 *  simple timer for Arduino
 * 
 */


//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include "Arduino.h"
// use: Wprogram.h for Arduino versions prior to 1.0



#ifndef _TIMER
#define _TIMER



class Timer {
private:
  //-----------------------------------------------------------------------------
  //  properties
  //-----------------------------------------------------------------------------
  float startTime;
  float freq;

  bool trigger;
  bool firstCall;



public:
  //-----------------------------------------------------------------------------
  //  constructor
  //-----------------------------------------------------------------------------
  Timer();



  //-----------------------------------------------------------------------------
  //  methods
  //-----------------------------------------------------------------------------
  void start();
  void stop();



  //-----------------------------------------------------------------------------
  //  sets
  //-----------------------------------------------------------------------------
  void setFreq(float _freq);



  //-----------------------------------------------------------------------------
  //  gets
  //-----------------------------------------------------------------------------
  bool getTrigger();

};



//-----------------------------------------------------------------------------
//  constructor
//-----------------------------------------------------------------------------
Timer::Timer() {
  firstCall = true;
}



//-----------------------------------------------------------------------------
//  methods
//-----------------------------------------------------------------------------
void Timer::start() {
  startTime = millis();  
  firstCall = false;
}

void Timer::stop() {
  firstCall = true;
}



//-----------------------------------------------------------------------------
//  sets
//-----------------------------------------------------------------------------
void Timer::setFreq(float _freq) {
  freq = _freq;
}



//-----------------------------------------------------------------------------
//  gets
//-----------------------------------------------------------------------------
bool Timer::getTrigger() {
  if(firstCall) start();
  
  Serial.print( (millis() - startTime) );
  Serial.print( " < " );
  Serial.println( freq );

  if( (millis() - startTime) < freq ) {
    return false;
  }
  else {
    stop();
    return true;
  }  
  
}



#endif


