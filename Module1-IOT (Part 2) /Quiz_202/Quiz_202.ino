#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WiFiClient.h>
#include <WebServer.h>
#include <DHT.h> //https://www.arduinolibraries.info/libraries/dht-sensor-library
#include "index.h"


#define DHT_SENSOR_PIN  15 // ESP32 pin GIOP15 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22
#define LED1 18
#define LED2 19
#define LED3 22
#define LED4 23

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
WebServer server(80);

String ledState1 = "NA";
String ledState2 = "NA";
String ledState3 = "NA";
String ledState4 = "NA";

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}
void handleADC() {
  // read humidity
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float tempC = dht_sensor.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht_sensor.readTemperature(true);

  String tmpValue = "Temp = ";
  tmpValue += String(tempC) + " C, Humidity = ";
  tmpValue += String(humi) + " %";
  server.send(200, "text/plane", tmpValue);
}
void handleLED() {
  String t_state = server.arg("LEDstate"); //Refer xhttp.open("GET", "setLED?LEDstate="+led, true);
  Serial.println(t_state);
  if (t_state == "11") {
    digitalWrite(LED1, HIGH);
    ledState1 = "ON";
  }
  if (t_state == "10") {
    digitalWrite(LED1, LOW);
    ledState1 = "OFF";
  }
  if (t_state == "21") {
    digitalWrite(LED2, HIGH);
    ledState2 = "ON";
  }
  if (t_state == "20") {
    digitalWrite(LED2, LOW);
    ledState2 = "OFF";
  }
  if (t_state == "31") {
    digitalWrite(LED3, HIGH);
    ledState3 = "ON";
  }
  if (t_state == "30") {
    digitalWrite(LED3, LOW);
    ledState3 = "OFF";
  }
  if (t_state == "41") {
    digitalWrite(LED4, HIGH);
    ledState4 = "ON";
  }
  if (t_state == "40") {
    digitalWrite(LED4, LOW);
    ledState4 = "OFF";
  }
  server.send(200, "text/plane", ledState1 + ", " + ledState2 + ", " + ledState3 + ", " + ledState4);
}

void setup() {

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  dht_sensor.begin(); // initialize the DHT sensor

  // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.

  // put your setup code here, to run once:
  Serial.begin(115200);

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  // wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("ESP32AutoConnectAP", "12345678"); // password protected ap

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    Serial.println(res);
  }
  server.begin();
  server.on("/", handleRoot);
  server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);
  Serial.println("HTTP server started");



}

bool LED1_Status, LED2_Status, LED3_Status, LED4_Status = LOW;
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
