#include "EspMQTTClient.h"
#include <string.h>
#include <HX711.h>

EspMQTTClient client(
  "virus.exe",
  "border!9",
  "192.168.68.122",  // MQTT Broker server ip
  "mqttava",   // Can be omitted if not needed
  "mqttpass",   // Can be omitted if not needed
  "SHELF1",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

  String mySensor = "SHELF1";

void setup()
{
  Serial.begin(115200);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("EVENT", "Offline!");  // You can activate the retain flag by setting the third parameter to true
  randomSeed(analogRead(0));

}



int read_average(int num)
{
  // offset is the tare value (# read from hx711 w/o any weight)
  // gReading is the calibration value (# read from hx711 w/ 1000g)
  int offset = 15000;
  int gReading = 25000;
  int unit = 1000; // 1000 for 1000g
  int m = (unit-offset)/gReading;
  num = num - offset;
  return num;
}


// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  client.publish("EVENT","SHELF1 is ONLINE");
  Serial.print("shelf1 has reported to MQTT broker.");
  // assume jeans weigh 0.4 kg on average
  // assume shirts weigh 0.1 kg on average
  int jeansW = 400;
  int shirtsW = 100;

  // Publish a message to "mytopic/test"
  for (int i=0; i<20; i++)
  {
    long randNumber = random(15000,250000);
    int temp = read_average(randNumber);
    String s = String(temp);
    
    Serial.println(mySensor+" "+s);
    client.publish(mySensor,s);  
    delay(5000);
  }
}

void loop()
{
  client.loop();
}
