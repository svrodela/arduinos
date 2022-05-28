const int pin = 11; // Analog output pin
byte valor = 0;        // valor del PWM

void setup() {
  Serial.begin(9600);
}

void loop() {
  analogWrite(pin, valor);
  Serial.println(valor);
  delay(200);
  valor++;
}
