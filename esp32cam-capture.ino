/*
 * esp32cam-capture
 * captures image by pressing push button, then uploads to server
 * 
 * Inspired from project by Rui Santos https://RandomNerdTutorials.com/esp32-cam-post-image-photo-server/
*/

#include <Arduino.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#include "credentials.h"

#ifndef CREDENTIALS_H
  #define WIFI_SSID "..."
  #define WIFI_PASS "..."
#endif

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

String serverName = "192.168.43.89";   // REPLACE WITH YOUR Raspberry Pi IP ADDRESS
//String serverName = "example.com";   // OR REPLACE WITH YOUR DOMAIN NAME

String serverPath = "/upload.php";     // The default serverPath should be upload.php
const int serverPort = 80;

WiFiClient client;

//=========================================
// CAMERA

#include "camera.h"
String sendPhoto();
void camera_setup();

//=========================================
// BUTTON

#define BUTTON_PIN 12 // using GPIO pin 12

bool capture = false;

void pin_ISR() {
  // if button pressed, capture is true
  if (digitalRead(BUTTON_PIN)) {
    capture = true;
  }
}

void button_setup() {
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(0, pin_ISR, CHANGE);
}

//=========================================
// WIFI

void wifi_setup() {
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP());
}

//=========================================
// MAIN

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
  Serial.begin(115200);

  wifi_setup();
  camera_setup();
  button_setup();
}

void loop() {
  // captures every time the interrupt from button press is triggered
  if (capture) {
    sendPhoto();
    capture = false;
  }
}
