int duracion;
int distancia;
int trig= 2;//disparo
int echo=3;
int rele=5;
int pot=1;
int tiempo=5000;
void setup() 
{
  pinMode(A7,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  pot = (analogRead(A7)*10000)/1023;
  tiempo=tiempo+pot;
  pinMode(rele,OUTPUT);
  pinMode(trig,OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig,LOW);
  pinMode(echo,INPUT);
  duracion= pulseIn(echo,HIGH);
  distancia = duracion / 58;
 // Serial.println(distancia);
  Serial.println(pot);
 if(distancia <= 40 && distancia >= 10)
 {
  digitalWrite(rele,HIGH);
  
  delay(tiempo);
  digitalWrite(rele,LOW);
  Serial.println("APAGADO");
  Serial.println("ESPERANDO 5 SEG");
  delay(tiempo);
  
  }


}
