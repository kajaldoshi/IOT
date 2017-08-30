
const int trigPin = 7;
const int echoPin = 8;
int ledPin = 4;
long duration;

int distance;
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //clears the trigPin
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

//sets teh trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  //reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

//calculating distance
  distance = duration *0.034/2;

  if(distance < 10){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
  
  Serial.print("Distance is: ");
  Serial.print(distance);
  Serial.print(" cm");
  delay(1000);
 }
