#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <ElegantOTA.h>

#include "function.h"

// Replace with your network credentials
const char *ssid = "Cindy";
const char *password = "Cindy2001s";

// Motor pins
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

AsyncWebServer server(80);

void initLittleFS()
{
  if (!LittleFS.begin(true))
  {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  else
  {
    Serial.println("LittleFS mounted successfully");
  }
}

void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  delay(2000);
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);
  initWiFi();
  initLittleFS();

  // Motor pin modes
  motor_setup();
  motor_stop();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(LittleFS, "/index.html", "text/html"); });

  server.serveStatic("/", LittleFS, "/");

  server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Xe tiến");
    moveForward();
    request->send(200, "text/plain", "OK"); });

  server.on("/backward", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Xe lùi");
    moveBackward();
    request->send(200, "text/plain", "OK"); });

  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Rẽ trái");
    moveLeft();
    request->send(200, "text/plain", "OK"); });

  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Rẽ phải");
    moveRight();
    request->send(200, "text/plain", "OK"); });

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Dừng xe");
    motor_stop();
    request->send(200, "text/plain", "OK"); });

  server.begin();
  ElegantOTA.begin(&server);
  // mpu6050_init();
  // task_read_mpu6050();
  // vl53l0x_init();
  // task_read_vl53l0x();
}

void loop()
{
  ElegantOTA.loop();
}