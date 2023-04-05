#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <HTTPClient.h>
#include <DHT.h> //https://www.arduinolibraries.info/libraries/dht-sensor-library
#include <TM1638plus.h> [ver 1.9.1]

// Replace with your API endpoint
const char* serverName = "xxxxxx";

#define DHT_SENSOR_PIN  15 // ESP32 pin GIOP15 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22
DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

#define WebHooksKey "xxxxxx" //Your Webhookskey
#define WebHooksEvent1 "xxxxxx"

#define Brd_STB 18 // strobe  = GPIO connected to str0be line of module
#define Brd_CLK 19 // clock = GPIO connected to clock line of module
#define Brd_DIO 21 // data = GPIO connected to data line of module
bool high_freq = true; // default , if using high freq CPU > 100 MHz set to true

TM1638plus tm(Brd_STB, Brd_CLK, Brd_DIO, high_freq);


void disPlay(float tempp, float humi) {
  if ( isnan(tempp) || isnan(humi)) {
    tm.displayHex(0, 0);
    tm.displayASCIIwDot(1, 0 + '0'); //turn on dot
    tm.displayHex(2, 0);
    tm.display7Seg(3, B01011000);

    tm.displayHex(4, 0);
    tm.displayASCIIwDot(5, 0 + '0'); //turn on dot
    tm.displayHex(6, 0);
    tm.display7Seg(7, B01110100);
  } else {
    tm.displayHex(0, int(tempp / 10));
    tm.displayASCIIwDot(1, int(int(tempp) % 10) + '0'); //turn on dot
    tm.displayHex(2, int(int(tempp * 10)) % 10);
    tm.display7Seg(3, B01011000);

    tm.displayHex(4, int(humi / 10));
    tm.displayASCIIwDot(5, int(int(humi) % 10) + '0'); //turn on dot
    tm.displayHex(6, int(int(humi * 10)) % 10);
    tm.display7Seg(7, B01110100);

  }
}

void sendData2Spreadsheet(float tempp, float humi) {
  // Create JSON object
  String jsonString = " {\"Test1\":\"" + String(tempp) + " ºC\"" + ",\"Test2\":\"" + String(humi) + " %\"" + "}";
  Serial.print(jsonString);

  // Send HTTP POST request with JSON data
  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonString);

  // Check if POST request was successful
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}



void setup() {

  dht_sensor.begin(); // initialize the DHT sensor
  tm.displayBegin(); // initialize the TM1638
  Serial.begin(115200);
  delay(1000);

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;
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
  }

  delay(1000);
}

void loop() {

  // read humidity
  float humi  = dht_sensor.readHumidity();
  // read temperature in Celsius
  float tempC = dht_sensor.readTemperature();
  // read temperature in Fahrenheit
  float tempF = dht_sensor.readTemperature(true);

  disPlay(tempC, humi);
  sendData2Spreadsheet(tempC, humi);


  if (tempC > 28.00) {
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEvent1) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String(tempC) + String(" ºC High Temperature");
    Serial.println("Server Name :" + serverName);
    Serial.println("json httpRequestData :" + httpRequestData);
    if (WiFi.status() == WL_CONNECTED)
    { HTTPClient http;
      http.begin(serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpResponseCode = http.POST(httpRequestData);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      if (httpResponseCode == 200)
        Serial.println("Successfully sent");
      else
        Serial.println("Failed!");
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }

    Serial.println(" >> Ready");
  }

  delay(5000);
}
