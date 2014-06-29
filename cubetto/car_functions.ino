//one wheel is composed of 32 slices
//16 black and 16 white.

//rotate wheels until the next sign
void initialize() {
  int vl = digitalRead(leftEncoder);

  //forward left
  analogWrite(leftForward, 88);
  digitalWrite(leftReverse, LOW);

  while (digitalRead(leftEncoder) == vl){
  }

  stopLeft();

  delay(100);

  int vr = digitalRead(rightEncoder);

  //forward right
  analogWrite(rightForward, 88);
  digitalWrite(rightReverse, LOW);


  while (digitalRead(rightEncoder) == vr){
  }

  stopRight();
}

/* MOTION FUNCTIONS */

//not used
void backward(int speed, int steps) {
  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL, counterR = 0;

  //right backward
  digitalWrite(rightForward, LOW);
  analogWrite(rightReverse, speed);

  //left backward
  digitalWrite(leftForward, LOW);
  analogWrite(leftReverse, speed);


  while (counterL <= steps && counterR <= steps) {
    if (counterL <= steps) {
      vL = digitalRead(leftEncoder);
      if (vL != pvL) counterL++;
      pvL = vL;
    }
    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);
      if (vR != pvR) counterR++;
      pvR = vR;
    }
  }

  stop();
}

void forward(int speed, int steps) {
  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL, counterR = 0;

  //right forward
  analogWrite(rightForward, speed);
  digitalWrite(rightReverse, LOW);

  //left forward
  analogWrite(leftForward, speed);
  digitalWrite(leftReverse, LOW);

  long t = millis();
  while ((counterL <= steps && counterR <= steps) 
    || (millis()-t)<MAX_DURATION_STRAIGHT) {
    if (counterL <= steps) {
      vL = digitalRead(leftEncoder);
      if (vL != pvL) counterL++;
      pvL = vL;
    }
    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);
      if (vR != pvR) counterR++;
      pvR = vR;
    }
  }

  stop();
}

void left(int speed, int steps) {
  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL, counterR = 0;

  //right forward
  analogWrite(rightForward, speed);
  digitalWrite(rightReverse, LOW);

  //left backward
  digitalWrite(leftForward, LOW);
  analogWrite(leftReverse, speed);

  long t = millis();
  //count rotation
  while ((counterL <= steps && counterR <= steps)
      || (millis()-t)<MAX_DURATION_TURN) {
    if (counterL <= steps) {
      vL = digitalRead(leftEncoder);
      if (vL != pvL) counterL++;
      pvL = vL;
    }
    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);
      if (vR != pvR) counterR++;
      pvR = vR;
    }
  }

  stop();
}

void right(int speed, int steps) {

  int vL, pvL = 0;
  int vR, pvR = 0;

  int counterL = 0, counterR = 0;

  pvL = digitalRead(leftEncoder);
  pvR = digitalRead(rightEncoder);

  //right reverse
  digitalWrite(rightForward, LOW);
  analogWrite(rightReverse, speed);

  //left forward
  digitalWrite(leftReverse, LOW);
  analogWrite(leftForward, speed);

  long t = millis();
  //count rotation
  while ((counterL <= steps || counterR <= steps)
      && (millis()-t)<MAX_DURATION_TURN) {
    if (counterL <= steps) {
      vL = digitalRead(leftEncoder);
      if (vL != pvL) counterL++;
      pvL = vL;
    }
    if (counterR <= steps) {
      vR = digitalRead(rightEncoder);
      if (vR != pvR) counterR++;
      pvR = vR;
    }
  }

  stop();
}

/* STOP FUNCTIONS */
void stopLeft() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, LOW);
}

void stopRight() {
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, LOW);
}

void stop() {
  stopLeft();
  stopRight();
}

void hardStop() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftReverse, HIGH);

  digitalWrite(rightForward, HIGH);
  digitalWrite(rightReverse, HIGH);
}



