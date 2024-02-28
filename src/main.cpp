#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to GPIO15
#define ONE_WIRE_BUS 18
// Setup a oneWire instance to communicate with a OneWire device
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

DeviceAddress sensor1 = {0x28, 0xDF, 0x2F, 0x57, 0x4, 0xE1, 0x3C, 0x5};
DeviceAddress sensor2 = {0x28, 0x4D, 0x3E, 0x57, 0x4, 0xE1, 0x3C, 0x6B};
DeviceAddress sensor3 = {0x28, 0xD4, 0x17, 0x57, 0x4, 0xE1, 0x3C, 0x47};

void setup(void)
{
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);
  Serial.begin(115200);
  sensors.begin();
}

void loop(void)
{
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");

  //Serial.print("Sensor 1(*C): ");
  //Serial.println(sensors.getTempC(sensor1));
  //Serial.print(" Sensor 1(*F): ");
  //Serial.println(sensors.getTempF(sensor1));

  //Serial.print("Sensor 2(*C): ");
  //Serial.println(sensors.getTempC(sensor2));
  //Serial.print(" Sensor 2(*F): ");
  //Serial.println(sensors.getTempF(sensor2));

  //Serial.print("Sensor 3(*C): ");
  //Serial.println(sensors.getTempC(sensor3));
  //Serial.print(" Sensor 3(*F): ");
  //Serial.println(sensors.getTempF(sensor3));
  float t1 = sensors.getTempC(sensor1);
  float t2 = sensors.getTempC(sensor2);
  float t3 = sensors.getTempC(sensor3);
  Serial.printf("%3.1f\t%3.1f\t%3.1f \n", t1, t2, t3);
  delay(1000);
}

/*
 * Rui Santos
 * Complete Project Details https://randomnerdtutorials.com


// Based on the OneWire library example

OneWire ds (18); // data wire connected to GPIO15

void setup(void)
{
  pinMode(18, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop(void)
{
  byte i;
  byte addr[8];

  if (!ds.search(addr))
  {
    Serial.println(" No more addresses.");
    Serial.println();
    ds.reset_search();
    delay(250);
    return;
  }

  Serial.print(" ROM =");
  for (i = 0; i < 8; i++)
  {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }
}
*/