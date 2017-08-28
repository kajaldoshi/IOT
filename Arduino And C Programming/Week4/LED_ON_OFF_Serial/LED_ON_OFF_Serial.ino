
int val=0;
int ledPin =13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  if(Serial.available()){
    val = Serial.read();
    if(val == '0'){
      digitalWrite(ledPin,LOW);
    }
    else if(val == '1'){
      digitalWrite(ledPin, HIGH);
    }
    Serial.write(val);
  }
}
