#include <Servo.h>

Servo servo;

int ledPin = 11;
int potPin = 0; //for A0 -analog pin
int potReading = 0 ; //

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  Serial.println("Demo for potentiometer");
  servo.attach(ledPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  potReading = analogRead(potPin);
  //Serial.println(potReading);
  

  potReading = map(potReading,0,1023,0,180);
  Serial.println(potReading);

  if(potReading>2 ){
    if(servo.attached())
    {
        servo.write(potReading);
    }
    else{
        servo.attach(ledPin);    
        servo.write(potReading);
    }
  }
  else {
      servo.detach();
  }
  
  delay(1000);
}
