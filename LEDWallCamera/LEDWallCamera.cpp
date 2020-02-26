#include <Arduino.h>
#include <ESP32Lib.h>
#include <stdint.h>

#include <WiFi.h>
#include <WiFiUdp.h>

#include "camera.h"
#include "tools.h"
#include "config.h"
#include "effects.h"
#include "server.h"
#include "flut.h"


const char * networkName = "<wifi network>";
const char * networkPswd = "<wifi password>";

//Are we currently connected?
boolean connected = false;

// image setup
unsigned char image[displayX*displayY][3];
// SerialLED gfx;

int imageRes[] = {displayX, displayY};
int currentImage = 1;
// int calibration = 100;
volatile bool frameAvailable = false;


void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());
          //initializes the UDP state
          //This initializes the transfer buffer
          // udp.begin(WiFi.localIP(),udpPort);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
      default: break;
    }
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

void webTask(void *p)
{
  while(1)
  {
    handleServer();
    delay(10);
  }
}


void setup()
{
  Serial.begin(115200);

  connectToWiFi(networkName, networkPswd);

  cameraInit();
  setCameraParams();
  // initServer();
  // calculateSinTab();
  // calcRainbow();
  // gfx.setGamma(2.8f, 2.8f, 2.8f);
  // gfx.init(2, 1200, -1, -1);
  // initEffects();
  // TaskHandle_t xHandle = NULL;
  // xTaskCreatePinnedToCore(webTask, "web", 5000, 0,  ( 2 | portPRIVILEGE_BIT ), &xHandle, 0);
}


void loop()
{

if(connected){

  if(calibration)
  {
    calib();
    return;
  }

  camera_fb_t * fb = esp_camera_fb_get();
  if (fb)
  {
    downSample(fb->buf);  //fb->width, fb->height, fb->format, fb->buf, fb->len
    frameAvailable = true;
    esp_camera_fb_return(fb);
  };
  if(frameAvailable)
  {
    justShowImage();

    frameAvailable = false;

    // Serial.println("");
  }
  //Wait for 1 second
  delay(5);
  }
}
