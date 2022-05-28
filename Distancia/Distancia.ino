int tiempo;
int centimetros;
int trig = 12;
int echo = 13;
int piezo = 5;

void setup()
{
  Serial.begin (9600);
}

void loop()
{
  pinMode (trig, OUTPUT);
  digitalWrite (trig, LOW);
  delayMicroseconds (3);
  digitalWrite (trig, HIGH);
  delayMicroseconds (15);
  digitalWrite (trig, LOW);
  pinMode (echo, INPUT);
  tiempo = pulseIn (echo, HIGH);
  centimetros = tiempo / 58;
  Serial.println(centimetros);
}
