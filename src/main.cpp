
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESPAsyncWebServer.h>

#define ONE_WIRE_BUS 15 //esp-32
#include <WiFi.h>
#include <AsyncUDP.h>
AsyncUDP udp;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
AsyncWebServer server(80);
const uint32_t __PORT = 12345;

DeviceAddress TS1 = {0x28, 0xDF, 0x2F, 0x57, 0x4, 0xE1, 0x3C, 0x5};
DeviceAddress TS2 = {0x28, 0x4D, 0x3E, 0x57, 0x4, 0xE1, 0x3C, 0x6B};
DeviceAddress TS3 = {0x28, 0xD4, 0x17, 0x57, 0x4, 0xE1, 0x3C, 0x47};
DeviceAddress TS4 = {0x28, 0xD4, 0x17, 0x57, 0x4, 0xE1, 0x3C, 0x47};/////////////////////////////

#include "index.h"

void indexHandler(AsyncWebServerRequest *request)
{
  request->send(200, "text/html", INDEX_HTML);
  // request->send(SPIFFS, "/index.html", "text/html");
  // request->send(SPIFFS, "/index.html", String(), false);
}

void setup(void)
{
  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);
  Serial.begin(115200);
  sensors.begin();

  server.on("/", HTTP_GET, indexHandler);
  //server.on("/status", HTTP_GET, statusHandler);
  //server.on("/action", HTTP_GET, commandHandler);
  //server.on("/status", HTTP_OPTIONS, preflight);

  WiFi.setHostname("LOGGER");
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin("HOR", "123456789");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi Ready! Go to: http://");
  Serial.println(WiFi.localIP()); 

  if (udp.listen(__PORT))
  {
    Serial.print("UDP Listening on IP: ");
    Serial.println(WiFi.localIP());
    //udp.onPacket(onPacketEvent);
  }

  server.begin();
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

    char buf[32];

    snprintf(buf, sizeof(buf), "%d\t%3.1f\t%3.1f\t%3.1f\t%3.1f", 1, t1, t2, t3, t4);
    Serial.println(buf);     
    udp.broadcast(buf);
  }
}

/*
#include <Arduino.h>
#include <OneWire.h>
// Rui Santos
// Complete Project Details https://randomnerdtutorials.com


// Based on the OneWire library example

OneWire ds(15); // data wire connected to GPIO15

void setup(void)
{
  pinMode(15, INPUT_PULLUP);
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