#include <SPI.h>
#include <Adafruit_CC3000.h>
#include <IPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>

#define MS_PROXY                "quickstart.messaging.internetofthings.ibmcloud.com"
#define MQTT_PORT               1883
#define MQTT_MAX_PACKET_SIZE    100

//#define AUTHMETHOD              "use-token-auth"
//#define AUTHTOKEN               "Xd_p0uHNnELdK3?XR"

int echoPin=8;
int trigPin=7;

int echoPin1=6;
int trigPin1=4;

long duration;
long duration1;
int distance;
int distance1;
// Update these with values suitable for your network.
byte mac[] = { 0x08, 0x00, 0x28, 0x57, 0x28, 0xC1 };

//The convention to be followed is d:quickstart:iotsample-arduino:<MAC Address>
#define MQTT_CLIENTID           "d:quickstart:iotsample-arduino:00a7f1d92a82"
#define MQTT_TOPIC              "iot-2/evt/status/fmt/json"
  
Adafruit_CC3000_Client c;
IPStack ipstack(c);

MQTT::Client<IPStack, Countdown, 100, 1> client = MQTT::Client<IPStack, Countdown, 100, 1>(ipstack);

String deviceEvent;

// Wifi/WLAN
#define WLAN_SSID       "linksys"
#define WLAN_PASS       "admin@123"
#define WLAN_SECURITY   WLAN_SEC_WPA2                           // Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

// CC3000
#define ADAFRUIT_CC3000_IRQ     3                               // MUST be an interrupt pin!
#define ADAFRUIT_CC3000_VBAT    5                               // Can be any pin
#define ADAFRUIT_CC3000_CS      10                              // Can be any pin
// Use hardware SPI for the remaining pins, for UNO, SCK = 13, MISO = 12, MOSI = 11
Adafruit_CC3000                 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER); // you can change this clock speed but DI


void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
 
  if (!cc3000.begin())
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    while (1);
  }
  displayMACAddress();

  // connect to Wifi
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  while (!cc3000.checkDHCP())                                 
    delay(100);
  displayConnectionDetails();
}


void loop() {
  int rc = -1;
  delay(1000);
  if (!client.isConnected()) {
    Serial.println("Connecting to IoT Foundation for publishing Temperature");
    while (rc != 0) {
      rc = ipstack.connect(MS_PROXY, MQTT_PORT);
    }
    Serial.print(F("After ipstack"));
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = MQTT_CLIENTID;
    rc = -1;
    while ((rc = client.connect(data)) != 0)
    ;
    Serial.println("Connected successfully\n");
    Serial.println("Distance\tDevice Event (JSON)");
    Serial.println("____________________________________________________________________________");
  }

  MQTT::Message message;
  message.qos = MQTT::QOS0;
  message.retained = false;
  deviceEvent = String("{\"d\":{\"Distance\":");
  char buffer[60];
  dtostrf(getDistance(),1,2, buffer);
  deviceEvent += buffer;
  deviceEvent +=",\"Distance1\":";

  dtostrf(getDistance1(),1,2, buffer);
  deviceEvent += buffer;
  deviceEvent += "}}";
  Serial.print("\t");
  Serial.print(buffer);
  Serial.print("\t\t");
  deviceEvent.toCharArray(buffer, 60);
  Serial.println(buffer);
  message.payload = buffer;
  message.payloadlen = strlen(buffer);
  rc = client.publish(MQTT_TOPIC, message);

  if (rc != 0) {
    Serial.print("return code from publish was ");
    Serial.println(rc);
  }
  client.yield(1000);
}

double getDistance(void) {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = duration*0.034/2;
	return (distance);
}


double getDistance1(void) {
	digitalWrite(trigPin1, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin1, HIGH);
	delayMicroseconds(10);  
	digitalWrite(trigPin1, LOW);
	duration1 = pulseIn(echoPin1, HIGH);
	distance1 = duration1*0.034/2;
	return (distance1);
}

void displayMACAddress(void)
{
  uint8_t macAddress[6];

  if(!cc3000.getMacAddress(macAddress))
  {
    Serial.println(F("Unable to retrieve MAC Address!\r\n"));
  }
  else
  {
    Serial.print(F("MAC Address : "));
    cc3000.printHex((byte*)&macAddress, 6);
  }
}

bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println("\n");
    return true;
  }
}
