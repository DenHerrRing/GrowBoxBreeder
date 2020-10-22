/*
 * -----------------------------------------------------------------------
 * GrowBox Breeder V1.0
 * GIT:     https://github.com/DenHerrRing/GrowBoxBreeder.git
 * ISSUES:  https://github.com/DenHerrRing/GrowBoxBreeder/issues
 * Lizenz:  OpenSource
 * Author:  Dennis Hering 
 * -----------------------------------------------------------------------
 * Werte - Wasserstände, welche ich mit meinem Sensor gemessen habe.
 * 0/4 -> < 10
 * 1/4 -> 11 - 785 
 * 2/4 -> 786 - 835
 * 3/4 -> 836 - 900
 * 4/4 -> > 900
 * -----------------------------------------------------------------------
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <html.h>

DHT dht1(5, DHT22);         // D1 -> 5
DHT dht2(4, DHT22);         // D2 -> 4
DHT dht3(0, DHT22);         // D3 -> 0
const int sensorPin = A0;   //Sensor pin connected to analog pin A0

// Replace with your network credentials
// const char* ssid = "REPLACE_WITH_YOUR_SSID";
// const char* password = "REPLACE_WITH_YOUR_PASSWORD";
const char *ssid = "DerSchwarm";
const char *password = "FamilieHering07072017";

int liquid_level;
int level;

float temp1 = 0.0;
float hum1 = 0.0;

float temp2 = 0.0;
float hum2 = 0.0;

float temp3 = 0.0;
float hum3 = 0.0;

// AsyncWebServer on port 80
AsyncWebServer server(80);

// will store last time DHT was updated
unsigned long previousMillis = 0;

// Updates DHT readings every 10 seconds
const long interval = 10000;

// Replaces placeholder with DHT values
String processor(const String &var)
{
  //Serial.println(var);
  if (var == "TEMPERATURE1")
  {
    return String(temp1);
  }
  else if (var == "HUMIDITY1")
  {
    return String(hum1);
  }
  else if (var == "TEMPERATURE2")
  {
    return String(temp2);
  }
  else if (var == "HUMIDITY2")
  {
    return String(hum2);
  }
  else if (var == "TEMPERATURE3")
  {
    return String(temp3);
  }
  else if (var == "HUMIDITY3")
  {
    return String(hum3);
  }
  else if (var == "LIQUIDLEVEL")
  {
    return String(level);
  }
  return String();
}

void readWaterSensor()
{
  liquid_level = analogRead(sensorPin);
  Serial.print("Wasserstand: ");

  if (liquid_level >= 12)
    level = 0;
  if (liquid_level >= 785)
    level = 1;
  if (liquid_level >= 835)
    level = 2;
  if (liquid_level >= 900)
    level = 3;

  Serial.print(level);
  Serial.println("/4");
}

void readDHTsensors()
{
  float newT1 = dht1.readTemperature();
  float newH1 = dht1.readHumidity();
  float newT2 = dht2.readTemperature();
  float newH2 = dht2.readHumidity();
  float newT3 = dht3.readTemperature();
  float newH3 = dht3.readHumidity();

  if (isnan(newT1) || isnan(newT1))
  {
    Serial.println("Failed to read from DHT1 sensor!");
  }
  else
  {
    temp1 = newT1;
    hum1 = newH1;
    Serial.print("DHT1: T=");
    Serial.print(temp1);
    Serial.print(" - H=");
    Serial.println(hum1);
  }

  if (isnan(newT2) || isnan(newT2))
  {
    Serial.println("Failed to read from DHT2 sensor!");
  }
  else
  {
    temp2 = newT2;
    hum2 = newH2;
    Serial.print("DHT2: T=");
    Serial.print(temp2);
    Serial.print(" - H=");
    Serial.println(hum2);
  }

  if (isnan(newT3) || isnan(newT3))
  {
    Serial.println("Failed to read from DHT3 sensor!");
  }
  else
  {
    temp3 = newT3;
    hum3 = newH3;
    Serial.print("DHT3: T=");
    Serial.print(temp3);
    Serial.print(" - H=");
    Serial.println(hum3);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("GrowBoxBreeder V1.0");

  pinMode(sensorPin, INPUT);
  dht1.begin();
  dht2.begin();
  dht3.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address on Serial
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/1/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(temp1).c_str());
  });
  server.on("/1/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(hum1).c_str());
  });
  server.on("/2/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(temp2).c_str());
  });
  server.on("/2/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(hum2).c_str());
  });
  server.on("/3/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(temp3).c_str());
  });
  server.on("/3/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(hum3).c_str());
  });
  server.on("/liquidlevel", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", String(level).c_str());
  });

  // Start server
  server.begin();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;

    readDHTsensors();
    readWaterSensor();
  }
}