const int pin = 11; // pin de salida para analogo
byte valor = 0;        // valor del PWM 0-256

void setup() {
  Serial.begin(9600); //inicializamos el puerto serial
}

void loop() {
  analogWrite(pin, valor);
  Serial.println(valor);
  delay(100);
  valor++; //aumenta el valor
}
