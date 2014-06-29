/*
http://primo.io

This sketch is part of the Primo Prototype Documentation.
http://docs.primo.io

Tested on the Arduino Mega 2560.
Load this into the Interface Board.

ANALOG VALUES FOR DIFFERENT RESISTORS:
10KΩ = 500
100KΩ = 920
4.7KΩ = 319
220Ω = 20
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

// radio setup
int msg[1];
RF24 radio(42,53);
const uint64_t pipe = 0xE8E8F0F0E1LL;

//4.7kΩ
int forwardVal = 320; //326;
//10kΩ
int leftVal = 930; //511;
//220Ω
int rightVal = 51; //22;
//100kΩ
int functionVal = 470; //931;
//range 
int gap = 50;

int buttonPin = 40;
int butVal, pButVal;

boolean isExecuting = false;

int vals[16];

void setup() {  
  //led init
  for (int i = 22; i < 38; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  //Serial1.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {
  
  //turn on LEDs if a block is inserted
  for(int i = 0; i < 16; i++) {
    int led = i+22;
    
    int val = analogRead(i);

    //Serial.print(i);
    //Serial.print(": ");
    //Serial.println(val);
    
    //fix this 
    if (val < 950) {
      digitalWrite(led, HIGH);
   //   Serial.print("Turn on LED ");
   //   Serial.println(led);
    } 
    else {
      digitalWrite(led, LOW);
   //   Serial.print("Turn off LED ");
   //   Serial.println(led);
    }    
  }

  int b = digitalRead(buttonPin);
  butVal = b;
  //Serial.print("Button: ");
  //Serial.println(b);
  
  //if button press & not executing
  if(butVal == HIGH && pButVal == LOW && isExecuting == false) {
    isExecuting = true;
  }

  if(isExecuting) {
    readPins();

    for ( int i = 0; i < 12; i++) {
      if (vals[i] < 950) {
        route(i);
      }
      else {
        break;
      }
    }    
  }  
  
  isExecuting = false;
  pButVal = butVal;

  //Serial.println(analogRead(0));
  delay(30);
}

