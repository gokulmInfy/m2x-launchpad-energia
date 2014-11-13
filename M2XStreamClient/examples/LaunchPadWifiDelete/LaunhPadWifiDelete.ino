#include "SPI.h"
#include "WiFi.h"
#include <jsonlite.h>

#include "M2XStreamClient.h"

char ssid[] = "<ssid>"; //  your network SSID (name)
char pass[] = "<WPA password>";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char feedId[] = "<feed id>"; // Feed you want to receive values
char streamName[] = "<stream name>"; // Stream you want to receive values
char m2xKey[] = "<M2X access key>"; // Your M2X access key

char fromTime[] = "<from date/time>"; // yyyy-mm-ddTHH:MM:SS.SSSZ
char endTime[] = "<end date/time>"; // yyyy-mm-ddTHH:MM:SS.SSSZ

WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void on_data_point_found(const char* at, const char* value, int index, void* context, int type) {
  Serial.print("Found a data point, index:");
  Serial.println(index);
  Serial.print("Type:");
  Serial.println(type);
  Serial.print("At:");
  Serial.println(at);
  Serial.print("Value:");
  Serial.println(value);
}

void setup() {
  Serial.begin(115200);

  // Setup pins of CC3000 BoosterPack
  WiFi.setCSpin(18);  // 18: P2_2 @ F5529, PE_0 @ LM4F/TM4C
  WiFi.setENpin(2);   //  2: P6_5 @ F5529, PB_5 @ LM4F/TM4C
  WiFi.setIRQpin(19); // 19: P2_0 @ F5529, PB_2 @ LM4F/TM4C

  delay(10);
  // Connect to an AP with WPA/WPA2 security
  Serial.println("Connecting to WiFi....");
  WiFi.begin(ssid, pass); // Use this if your wifi network requires a password
  // WiFi.begin(ssid);    // Use this if your wifi network is unprotected.

  Serial.println("Connect success!");
  Serial.println("Waiting for DHCP address");
  // Wait for DHCP address
  delay(5000);
  // Print WiFi status
  printWifiStatus();
  
  // Delete values
  int response = m2xClient.deleteValues(feedId, 
                                        streamName,
                                        fromTime,
                                        endTime);
  Serial.print("M2x client response code: ");
  Serial.println(response);
  
}

void loop() {
  // Do nothing

  delay(5000);
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