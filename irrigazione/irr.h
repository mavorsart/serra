/*
irr.h
*/
#ifndef irr_included
#define irr_included

#include <Arduino.h>
#include <Print.h> //the Arduino print class
#include <Time.h>//o anche ds1302

class irrClass : public Print
{
 private:
  Time orarioAvvio;
  Time orarioFine;
 public:
  irrClass();
  boolean begin(Time t1,Time t2); 
};

extern irrClass irr; //the irr object
#endif
