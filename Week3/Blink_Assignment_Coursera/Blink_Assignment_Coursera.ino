/*
 * Program that causes the built-in LED connected to pin 13 on the Arduino to blink, alternating between fast blinks and slow blinks. 
 * The LED should blink 5 times, once every half second, and then it should blink 5 more times, once every two seconds. 
 * The LED should continue to blink in this alternating fashion for as long as the Arduino receives power.
 * 
 * Kajal Doshi
 */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
//Blink LED 5 times, once every half second  
  for(int x=0;x<5;x++){
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(250);                       
    digitalWrite(LED_BUILTIN, LOW);   
    delay(250);                      
  }
//Blink LED 5 times, once every two seconds
  for(int y=0;y<5;y++){
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(1000);                       
    digitalWrite(LED_BUILTIN, LOW);    
    delay(1000);                         }
}
