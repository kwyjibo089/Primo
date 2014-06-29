/*
http://primo.io

This sketch is part of the Primo Prototype Documentation.
http://docs.primo.io

Tested on the Arduino UNO.
Load this into Cubetto, the little cube robot.
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define FORWARD 1
#define BACKWARD 0

#define MAX_DURATION_TURN 500
#define MAX_DURATION_STRAIGHT 1400

//serial protocol
#define STOP 'O'
#define LEFT 'L'
#define RIGHT 'R'
#define FORWARD 'F'
#define INIT 'I'

//left motor
const int leftEnable = 8;//13;
const int leftForward = 3;//10;
const int leftReverse = 5;//11;

//right motor
const int rightEnable = 2;//12;
const int rightForward = 6;
const int rightReverse = 9;

//encoders
const int leftEncoder = A1;
const int rightEncoder = A3;

char instruction = 'O';

// radio
int msg[1];
RF24 radio(4,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {

  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  //initialize left
  pinMode(leftEnable, OUTPUT);
  pinMode(leftReverse, OUTPUT);
  pinMode(leftForward, OUTPUT);

  //initialize right
  pinMode(rightEnable, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(rightReverse, OUTPUT);

  //enable motors
  digitalWrite(leftEnable, HIGH);
  digitalWrite(rightEnable, HIGH);

  Serial.println("b4 init");
  //initialize aligns the wheels
//  initialize();
  Serial.println("init done");

  delay(2000);
}

void loop() {

  /*
  //read rom the xbee
  if (Serial.available() > 0) {
    instruction = Serial.read();
  }
  */
  if (radio.available())
  {
    bool done = false;    
    while (!done)
    {
      done = radio.read(msg, 1);      

/*
      instruction = (char)msg[0];
      Serial.print("instruction: ");
      Serial.println(instruction);*/
      
      delay(10);
      
      instruction = (char)msg[0];
            
      decode();    
      
    }
    radio.startListening();

  }
  /*
  else
  {
    Serial.println("No radio available");
  }
  */
}

int t;
void decode()
{
    //decode instruction
  switch (instruction) {    

    case FORWARD:
      Serial.println("f");
//      initialize();
//      digitalWrite(leftReverse, HIGH);
      t = millis();
      forward(180, 22);
      Serial.print("duration: ");
      Serial.println(millis()-t);
      break;

    case LEFT:
      Serial.println("l");
      //initialize();
      t = millis();
      left(180, 5);
      Serial.print("duration: ");
      Serial.println(millis()-t);
      break;

    case RIGHT:
      Serial.println("r");
      //initialize();
      t = millis();
      right(180, 7);
      Serial.print("duration: ");
      Serial.println(millis()-t);
      break;

    case INIT:
      initialize();
      break;
  
    case STOP:
      stop();
      break;

    default:
      stop();
      break;
  }

}





