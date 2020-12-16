#include "WiFiEsp.h"

const int pinSound = A0;

//Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include <SoftwareSerial.h>
SoftwareSerial Serial1(10, 11); // RX | TX
#endif

//Change to your own wifi ssid and password
char ssid[] = "dd-wrt";
char pass[] = "password";
int status = WL_IDLE_STATUS;
char server[] = "3.134.252.150";

char var[15] = "";
char get_request[200];

//Initialize the Ethernet client object
WiFiEspClient client;


void setup() {
  // put your setup code here, to run once:
  //Initial Serial for Debugging
  Serial.begin(115200); // communication with the host computer

  //Initalize Serial communication for ESP Module
  Serial1.begin(115200);

  //Initialize ESP Module
  WiFi.init(&Serial1);

  //Check for presence of WiFi shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while(true);
  } 

  //Attempt to connect to network
  while (status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to WPA SSID:");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("You're connected to the network");
  printWifiStatus();

}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println();
  if (!client.connected())
  {
    Serial.println("Starting connection to server ...");
    client.connect(server, 80);
  }

  Serial.println("Connected to server");
  int sensorValue = analogRead(pinSound);
  String temp_str = String(sensorValue);
  temp_str.toCharArray(var, 15);
  
  //itoa(sensorValue, var, 10);
  Serial.println(var);
  
  httpRequestCustom(var);

}

void httpRequestCustom(char data[])
{
  //Make a HTTP request
  sprintf(get_request, "GET /iot_sensor/add_data.php?data=%s HTTP/1.1\r\nHost: 3.134.252.150\r\nConnection: close\r\n\r\n", data);
  Serial.print(get_request);
  client.print(get_request);
  delay(500);
  while (client.available())
  {
    char c = client.read();
    Serial.write(c);
  }
  delay(10000);
}


void printWifiStatus()
{
  //Print SSID of attached network
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  //Print WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  //Print recieved signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");
}
