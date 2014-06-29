void route(int i) {

  int led = i + 22;

  //forward
  if (vals[i] > (forwardVal - gap) && vals[i] < (forwardVal + gap)) {
    //Serial1.print('F');
    radio.write("F",1);
    Serial.println('F');
    digitalWrite(led, LOW);
    delay(1500);
  }

  //left
  if (vals[i] > (leftVal - gap) && vals[i] < (leftVal + gap)) {
    radio.write("L",1);
    //Serial1.print('L');
    Serial.println('L');
    digitalWrite(led, LOW);
    delay(1000);
  }


  //right
  if (vals[i] > (rightVal - gap) && vals[i] < (rightVal + gap)) {
    radio.write("R",1);
    //Serial1.print('R');
    Serial.println('R');
    digitalWrite(led, LOW);
    delay(1000);
  }

  //function
  if (vals[i] > (functionVal - gap) && vals[i] < (functionVal + gap)) {
    
    Serial.println("FNC");
    //radio.write("N",1);

    //route function line
    for ( int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        //INFINITE LOOP FOR THE WIN!!
        route(i);
      }
      else {
        break;
      }
    }
    
    //turn function leds back on
    for (int i = 12; i < 16; i++) {
      if (vals[i] < 1023) {
        digitalWrite(i + 22, HIGH);
      }
    }
    delay(500);
  }
}



