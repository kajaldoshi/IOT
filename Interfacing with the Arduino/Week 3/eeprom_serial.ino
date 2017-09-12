#include <EEPROM.h>

String val;
int value;

void setup() {
  Serial.begin(9600);
}

void loop() {
if(Serial.available()){
  val = Serial.readString();

  if(val.startsWith("read")){
    String address = val.substring(5);
    value = EEPROM.read(address.toInt());
    Serial.print(value);
  }
  else if(val.startsWith("write")){
    val = val.substring(6);
    int index = val.indexOf(" ");
    String address = val.substring(0,index);
    String ent = val.substring(index+1);
    EEPROM.write(address.toInt(), ent.toInt());
  }
} 
}
