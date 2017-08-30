#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 2

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println("Temperature sensor using");
Serial.println(DHT11LIB_VERSION);
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT11.read(DHT11PIN);
  Serial.print("Humidity %");
  Serial.print((float)DHT11.humidity,1);
  Serial.print(".\t");
  Serial.print("Temperature %");
  Serial.println((float)DHT11.temperature,1);
  delay(1000);
}
