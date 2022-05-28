#include <Servo.h>
//pin PWM para el servo
int pinServo = 3;
//declaración del objeto
Servo servo;
void setup() {
  Serial.begin(9600);
  //iniciar el servo 
  servo.attach(pinServo);
}
void loop() {
servo.write(0);
delay(1000);
Serial.println(servo.read()); 
servo.write(90);
delay(1000);
Serial.println(servo.read());
servo.write(180);
delay(1000);
Serial.println(servo.read());
servo.write(0);
delay(1000);
Serial.println(servo.read());

}
