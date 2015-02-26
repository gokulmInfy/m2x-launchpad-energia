#include <WiFi.h>
#include <Wire.h>
#include <BMA222.h>
#include "SPI.h"

#include <jsonlite.h>
#include "M2XStreamClient.h"

char ssid[] = "<ssid>"; //  your network SSID (name)
char pass[] = "<WPA password>";    // your network password (use for WPA, or use as key for WEP)
//int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char deviceId[] = "<device id>"; // Device you want to push to
char streamName[] = "<stream name>"; // Stream you want to push to
char m2xKey[] = "<M2X access key>"; // Your M2X access key

BMA222 mySensor;

WiFiClient client;

M2XStreamClient m2xClient(&client, m2xKey);

void setup() {

  Serial.begin(115200);

  mySensor.begin();
  uint8_t chipID = mySensor.chipID();
  Serial.print("chipID: ");
  Serial.println(chipID);

  delay(10);
  
  // Connect to an AP with WPA/WPA2 security
  Serial.println("Connecting to WiFi....");
  WiFi.begin(ssid, pass); // Use this if your wifi network requires a password
  // WiFi.begin(ssid);    // Use this if your wifi network is unprotected.

  Serial.println("Connect success!");
  Serial.println("Waiting for DHCP address");
  // Wait for DHCP address
  delay(5000);
  
  IPAddress empty(0,0,0,0);
  while (WiFi.localIP() == empty);
  // Print WiFi status
  printWifiStatus();
  
}

void loop() {

  float x = mySensor.readXData()/65.0;
  Serial.print("Accel X: ");
  Serial.print(x);

  float y = mySensor.readYData()/65.0;
  Serial.print(", Y: ");
  Serial.print(y);

  float  z = mySensor.readZData()/65.0;
  Serial.print(", Z: ");
  Serial.println(z);

  // Calculate pitch and roll. Find the maximum tilt angle.
  float pitch = atan(x / sqrt(y * y + z * z))*180;
  float roll = atan(y / sqrt(x * x + z * z))*180;
  float maxTilt =
    max(abs(roll), abs(pitch)) / 3.14159;
  Serial.print("pitch: ");
  Serial.print(pitch);
  Serial.print(" roll: ");
  Serial.print(roll);
  Serial.print(" maxTilt: ");
  Serial.println(maxTilt);


  // If the maximum tilt is over 20 degrees, then send
  // data to stream
  if (maxTilt > 20) {
    int response = m2xClient.updateStreamValue(deviceId, streamName, maxTilt);
    Serial.print("M2x client response code: ");
    Serial.println(response);

    if (response == -1)
      while (1)
        ;

    delay(500);
  }



}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


