/*
 *  Sonar Simple MultiTimer Example
 * 
 *  Ken Frederick
 *  ken.frederick@gmx.de
 *
 *  http://cargocollective.com/kenfrederick/
 *  http://kenfrederick.blogspot.com/
 *
 *  This is a simple example of how the
 *  a MultoTimer works
 *
 *  |-----|--------|-----|--------|
 *  |     |        |     |        |
 *  tick  tick     tick  tick     tick 
 *
 *  there are two different intervals
 *  which allows for more complicated 
 *  timing
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
// the output pins for the motors
int VMOTORS[2] = { 12,8 };

// the timer intervals
float INTERVALS[2][2] = { {100,600}, {300,2100} };

// the timer (should match the number of motors)
MultiTimer mtimer[2];



//------------------------------------------------------------------------
//  Methods
//------------------------------------------------------------------------
void setup() {                
  Serial.begin(9600);

  for( int i=0; i<2; i++) {
    /*
     *  setup output pins for vibration motors
     */
    pinMode(VMOTORS[i], OUTPUT);     


    /*
     *  setup timer
     */
    mtimer[i].setFreq( INTERVALS[i] );
  }


}

//------------------------------------------------------------------------
void loop() {
  
  for( int i=0; i<2; i++) {

     /*
      *  this configuration will turn on
      *  the motor for exactly 1 "frame"
      *  and keep the motor OFF for the
      *  length set in the interval
      */
//    if( mtimer[i].getTrigger() ) {
//      digitalWrite(VMOTORS[i], HIGH);
//    }
//    else {
//      digitalWrite(VMOTORS[i], LOW);
//    }


     /*
      *  this configuration will turn off
      *  the motor for exactly 1 "frame"
      *  and keep the motor ON for the
      *  length set in the interval
      */
    if( !mtimer[i].getTrigger() ) {
      digitalWrite(VMOTORS[i], HIGH);
    }
    else {
      digitalWrite(VMOTORS[i], LOW);
    }


  }


}
