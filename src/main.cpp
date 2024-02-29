#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 12 //wemos
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DeviceAddress TS1 = {0x28, 0xDF, 0x2F, 0x57, 0x4, 0xE1, 0x3C, 0x5};
DeviceAddress TS2 = {0x28, 0x4D, 0x3E, 0x57, 0x4, 0xE1, 0x3C, 0x6B};
DeviceAddress TS3 = {0x28, 0xD4, 0x17, 0x57, 0x4, 0xE1, 0x3C, 0x47};
DeviceAddress TS4 = {0x28, 0xD4, 0x17, 0x57, 0x4, 0xE1, 0x3C, 0x47};/////////////////////////////

void setup(void)
{
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);
  Serial.begin(115200);
  sensors.begin();
}

void loop(void)
{
  static uint32_t tmr = millis();
  if (millis() - tmr > 1000)
  {
    tmr = millis();
    sensors.requestTemperatures();
    float t1 = sensors.getTempC(TS1);
    float t2 = sensors.getTempC(TS2);
    float t3 = sensors.getTempC(TS3);
    float t4 = sensors.getTempC(TS4);
    Serial.printf("%3.1f\t%3.1f\t%3.1f\t%3.1f\n", t1, t2, t3, t4);
  }
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