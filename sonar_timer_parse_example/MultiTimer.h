/*
 *  Multi-Timer
 * 
 *  Ken Frederick
 *  ken.frederick@gmx.de
 *
 *  http://cargocollective.com/kenfrederick/
 *  http://kenfrederick.blogspot.com/
 *
 *  simple multi-timer for Arduino
 * 
 */


//-----------------------------------------------------------------------------
//  includes
//-----------------------------------------------------------------------------
#include "Arduino.h"
// use: Wprogram.h for Arduino versions prior to 1.0



#ifndef _MULTI_TIMER
#define _MULTI_TIMER



class MultiTimer {
private:
  //-----------------------------------------------------------------------------
  //  properties
  //-----------------------------------------------------------------------------
  float startTime;
  float freq;

  float interval[2];

  bool firstCall;
  bool trigger;

public:
  int index;

  //-----------------------------------------------------------------------------
  //  constructor
  //-----------------------------------------------------------------------------
  MultiTimer();



  //-----------------------------------------------------------------------------
  //  methods
  //-----------------------------------------------------------------------------
  void start();
  void stop();



  //-----------------------------------------------------------------------------
  //  sets
  //-----------------------------------------------------------------------------
  void setFreq(float _interval);
  void setFreq(float _interval[2]);



  //-----------------------------------------------------------------------------
  //  gets
  //-----------------------------------------------------------------------------
  bool getTrigger();
  int  getTriggerCount();
  int  getTriggerNum();

};



//-----------------------------------------------------------------------------
//  constructor
//-----------------------------------------------------------------------------
MultiTimer::MultiTimer() {
  firstCall = true;
}



//-----------------------------------------------------------------------------
//  methods
//-----------------------------------------------------------------------------
void MultiTimer::start() {
  startTime = millis();  
  firstCall = false;
}

void MultiTimer::stop() {
  firstCall = true;
  index++;
}



//-----------------------------------------------------------------------------
//  sets
//-----------------------------------------------------------------------------
void MultiTimer::setFreq(float _interval) {
  interval[0] = _interval;
  interval[1] = 0;
}

void MultiTimer::setFreq(float _interval[2]) {
  interval[0] = _interval[0];
  interval[1] = _interval[1];
}



//-----------------------------------------------------------------------------
//  gets
//-----------------------------------------------------------------------------
bool MultiTimer::getTrigger() {
  if(firstCall) start();
  freq = interval[ getTriggerNum() ];

  Serial.print( (millis() - startTime) );
  Serial.print( " < " );
  Serial.print( freq );
  Serial.print( " --- " );
  Serial.print( index );
  Serial.print( " --- " );
  Serial.println( index % 2 );
  
  if( (millis() - startTime) < freq ) {
    return false;
  }
  else {
    stop();
    return true;
  }  
  
  return trigger;
}


//-----------------------------------------------------------------------------
int MultiTimer::getTriggerCount() {
  return index;
}

//-----------------------------------------------------------------------------
int MultiTimer::getTriggerNum() {
  return (index % 2);
}

#endif


