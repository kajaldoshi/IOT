#include <dht11.h>
#include <LiquidCrystal.h>

dht11 DHT11;
LiquidCrystal lcd(8,9,4,5,6,7);

#define DHT11PIN 2

void setup() {
  // put your setup code here, to run once:
lcd.begin(16, 2);
Serial.begin(115200);
Serial.println("Temperature sensor using");
Serial.println(DHT11LIB_VERSION);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  DHT11.read(DHT11PIN);
 Serial.print("Humidity %");
 Serial.print((float)DHT11.humidity,1);
 lcd.print("Humidity %:");
  lcd.print((float)DHT11.humidity);
  //delay(5000);
 lcd.setCursor(0,1);
  Serial.print("Temperature:");
  Serial.println((float)DHT11.temperature,1);
  lcd.print("Temperature");
  lcd.print((float)DHT11.temperature);
  delay(5000);
  lcd.clear();
}
