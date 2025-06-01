#include "EspMQTTClient.h"
#include <string.h>
#include <HX711.h>

const char* Sensor = "SHELF2";  // WHAT SHELF IS THIS?

EspMQTTClient client(
  "virus.exe",
  "border!9",
  "192.168.68.122",  // MQTT Broker server ip
  "mqttava",   // Can be omitted if not needed
  "mqttpass",   // Can be omitted if not needed
  Sensor,     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

String mySensor = Sensor;  // code above requires const char* type, code below was coded for string type variable.

void setup()
{
  Serial.begin(115200);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("EVENT", "Sensor Offline!"); // You can activate the retain flag by setting the third parameter to true
  randomSeed(2);

}



int read_average(int num)
{
  // offset is the tare value (# read from hx711 w/o any weight)
  // gReading is the calibration value (# read from hx711 w/ 1000g)
  int offset = 1500;
  int gReading = 2500;
  int unit = 100; // 1000 for 1000g
  int m = (unit-offset)/gReading;
  // ignore above... simulated "calibration" of scale.
  num = num - offset;
  return num;
}

void numToUnits(int* num, String myType,int* calc)
{
  // assume jeans weigh 0.4 kg on average 
  // assume shirts weigh 0.1 kg on average
  // assume cologne weigh 0.2 kg on average
  int ans = 0;
  int units = 0;
  String ShelfType[4]  = {"jeans","shirts","cologne"};
  int ShelfFactor[4]  = {400,100,200};
  int maxStack[4] = {36,80,160};
  int temp = sizeof(ShelfType)/sizeof(ShelfType[0]);
  int foo = 0;
  int bar = 0;
  for (int i = 0; i<temp; i++)
  {
    if (ShelfType[i]==myType)
    {
      foo = ShelfFactor[i];
      bar = maxStack[i];
    }
  }
  temp = *num;
  ans = temp/foo;  // convert # reading to NUMBER OF UNITS in type of myType
  *calc = ans;
  ans = ans/bar;  // calculate % full by dividing # of units by maxstackValue
  temp = ans*100;
  *num = temp;
}

String myFun(String mySensor)
{

  String ans = "";
  String ShelfArray[4]  = {"SHELF1","SHELF2","SHELF3"};
  String ShelfType[4]  = {"jeans","shirts","cologne"};
  int temp = sizeof(ShelfArray)/sizeof(ShelfArray[0]);
  for (int i = 0; i<temp; i++)
  {
    if (ShelfArray[i]==mySensor)
    {
      ans = ShelfType[i];
    }
  }
  return ans;
}




// This function is called once everything is connected (Wifi and MQTT)
void onConnectionEstablished()      // look to both output % and unit #
{
  String initialized = mySensor + " is ONLINE";
  client.publish("EVENT",initialized);
  Serial.println(mySensor+" has reported to MQTT broker.");

  // Publish a message to declare status
  
  String myType = myFun(mySensor);
  String topic2 = mySensor+"units";
  int calc = 0;
  for (int i=0; i<20; i++)
  {
    long randNumber = random(1500,8000);  // Quick maths, 36*400=14400, 100*80=8000, so on. Look at lines 55-56
    int temp = read_average(randNumber);
	int temp2 = temp;
    numToUnits(&temp, myType, &calc);
    String s = String(temp2);
    // client.publish has issue with sending int instead of string.
    Serial.println(mySensor+" "+s);
    Serial.println(topic2+" "+calc+" units!");
    client.publish(mySensor,s);  
    client.publish(topic2,String(calc));
    delay(5000);
  }
}

void loop()
{
  client.loop();
}
