#define RED_LED 5

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "TN_private_PH3RKN";
const char* password = "TRV9RA4JRJAPM";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back


void setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(RED_LED, OUTPUT);
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(400);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}


void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();

    digitalWrite(RED_LED, HIGH); // LED off
    delay(200);
    digitalWrite(RED_LED, LOW); // LED on
    delay(200);
    digitalWrite(RED_LED, HIGH); // LED off
    delay(200);
    digitalWrite(RED_LED, LOW); // LED on
    delay(200);
    digitalWrite(RED_LED, HIGH); // LED off
    delay(200);
    digitalWrite(RED_LED, LOW); // LED on
    delay(200);

  
  }
}
