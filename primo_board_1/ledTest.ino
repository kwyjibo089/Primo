void ledTest() {
  for (int i = 22; i < 38; i++) {
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
  }
}

