void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  

}

void loop() {
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  delay(500);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  delay(500);
  digitalWrite(2,HIGH);
  delay(50);
  digitalWrite(2,LOW);
  delay(50);
  digitalWrite(2,HIGH);
  delay(50);
  digitalWrite(2,LOW);
  delay(50);

}
