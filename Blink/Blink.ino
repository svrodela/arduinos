void setup()
   {  pinMode(2, OUTPUT); // Onboard LED
      //Serial.begin(9600);
   }

void loop()
   { digitalWrite(2, HIGH);  // turn on LED with voltage HIGH
     delay(500);                      // wait one second
     digitalWrite(2, LOW);   // turn off LED with voltage LOW
     delay(500);                      // wait one second
    // Serial.println(BUILTIN_LED);
   }
