/*
 *  Sonar Timer Parse Example
 * 
 *  Ken Frederick
 *  ken.frederick@gmx.de
 *
 *  http://cargocollective.com/kenfrederick/
 *  http://kenfrederick.blogspot.com/
 *
 *  This is an example of loading a string (i.e. packet from Max)
 *  and parsing the values into strength and interval values
 *
 */


//------------------------------------------------------------------------
//  Includes
//------------------------------------------------------------------------
#include "Timer.h"



//------------------------------------------------------------------------
//  Properties
//------------------------------------------------------------------------
// the output pins for the motors
// 11 = PWM
// 9  = PWM
int VMOTORS[2] = { 11,9 };

// the timer (should match the number of motors)
Timer timer[2];


/*
 * Fake Max Output
 */
// a max packet has to be made of the following
// this represents a "500ms" block of values being transmitted
//
// ^1   = which motor marker (a number 0-3) -- not used in this example
// $5   = packet size
// #1   = component marker
// %1   = value of motor strength (a number 1-5)
// %100 = value of time interval
// repeat...
//
String FROM_MAX[2] = {
  "$6#%1%500#%2%1000#%3%1500#%4%2000#%5%2500#%3%3000",  // motor 1
  "$9#%1%2500#%2%2000#%3%1500#%4%1000#%5%500#%4%1000#%3%1500#%2%2000#%1%2500"   // motor 2
  // and so on...
};


/*
 *  Max Packet Handling
 */
// this is a holder for a component of
// the string from max ie( "#1%100" )
// the array length should match the number of motors
String COMP[2];
// the component index to be read
int COMP_INDEX[2] = { 1,1 };

// the size of the packet (i.e. the number of different rhythms)
int COMP_SIZE[2] = { 6,9 };

// this is a holder for the motor strength
// the array length should match the number of motors
int STRENGTH[2] = { 0,0 };

// this is a holder for time interval
// the array length should match the number of motors
float INTERVAL[2] = { 500,2500 };



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


    // check for the comp packet size
    // on initialization
    String compSizeStr = split( FROM_MAX[i], '$', 1 );
    Serial.println( compSizeStr );
    COMP_SIZE[i] = compSizeStr.toInt();
    Serial.println( COMP_SIZE[i] );


    /*
     *  setup timer
     */
    timer[i].setFreq( INTERVAL[i] );
  }



}

//------------------------------------------------------------------------
void loop() {
  
//    int i = 1;  
  for( int i=0; i<2; i++) {
      
     /*
      *  this configuration will turn off
      *  the motor for exactly 1 "frame"
      *  and keep the motor ON for the
      *  length set in the interval
      */
    if( !timer[i].getTrigger() ) {
      
//        if( timer[i].getTriggerNum() == 0 ) {
        analogWrite(VMOTORS[i], STRENGTH[i]);
//        } 
//        else {
//          analogWrite(VMOTORS[i], 10);
//        }
    }
    else {
      // if the trigger has been flipped
      // we assume the COMP packet has been
      // read so increment up for the next one
      COMP_INDEX[i]++;
      // if the COMP_INDEX is greater than
      // the number of components, reset back to 1
      if( COMP_INDEX[i] > COMP_SIZE[i] ) {
        // in this example we jsut reset the 
        // index value so it loops
        COMP_INDEX[i] = 1;
        
        // this is where you might add the code to
        // check for a new packet
        // checkServer()
        
        // if we were getting a new packet
        // this is where we sould check for 
        // the size of the new packet
        Serial.println( i + ": RESET " + COMP_SIZE[i] );
//        String compSizeStr = split( FROM_MAX[i], '$', 1 );
//        Serial.println( compSizeStr );
//        COMP_SIZE[i] = compSizeStr.toInt();
//        Serial.println( i + ": NEW PACKET SIZE: " + COMP_SIZE[i] );
      }


      // get COMP
      // split on the '#'
      COMP[i] = split( FROM_MAX[i], '#', COMP_INDEX[i] );     

      // update motor strength
      // split on the '%' (the first one)
      String strengthStr = split( COMP[i], '%', 1 );
      STRENGTH[i] = (int)((strengthStr.toInt()*0.1)*255);
 
      // update interval value
      // split on the '%' (the second one)
      String intervalStr = split( COMP[i], '%', 2 );
      INTERVAL[i] = intervalStr.toInt();

      // set Timer with new interval
      timer[i].stop();
      timer[i].setFreq( INTERVAL[i] );
      
    }

  }


}

//------------------------------------------------------------------------
// http://stackoverflow.com/questions/9072320/arduino-split-string-into-string-array?utm_source=twitterfeed&utm_medium=twitter
String split(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}



