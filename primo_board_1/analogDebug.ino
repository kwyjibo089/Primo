void analogDebug() {
    for (int i = 0; i < 15; i++) {
    Serial.print(analogRead(i));
    Serial.print(", ");
  }
  
  Serial.println(analogRead(15));
}
