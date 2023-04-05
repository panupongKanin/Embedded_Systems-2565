#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <HTTPClient.h>

#define WebHooksKey "xxxxxx" //Your Webhookskey
#define WebHooksEvent1 "xxxxxx"

#define sw1 4
#define sw2 5

#define LED_Green_Stastus 22
#define LED_Red_Stastus 23

void setup() {
  Serial.begin(115200);
  pinMode(LED_Green_Stastus, OUTPUT);
  pinMode(LED_Red_Stastus, OUTPUT);
  

  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  WiFiManager wm;
  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("ESP32AutoConnectAP", "12345678"); // password protected ap

  if (!res) {
    digitalWrite(LED_Red_Stastus, HIGH);
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    digitalWrite(LED_Green_Stastus, HIGH);
  }
}

void loop() {

  if (digitalRead(sw1) == LOW) {
    digitalWrite(LED_Green_Stastus, LOW);
    digitalWrite(LED_Red_Stastus, HIGH);
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEvent1) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" + String("Door Open Alarm!!!");
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
    Serial.print(" >> Wait for 5 Sec --> ");
    for (int i = 5; i > 0; i--)
    { Serial.print(i);
      delay(1000);
    }
    digitalWrite(LED_Green_Stastus, HIGH);
    digitalWrite(LED_Red_Stastus, LOW);
    Serial.println(" >> Ready");
  }

  if (digitalRead(sw2) == LOW)
  {
    digitalWrite(LED_Green_Stastus, LOW);
    digitalWrite(LED_Red_Stastus, HIGH);
    String serverName = "http://maker.ifttt.com/trigger/" + String(WebHooksEvent1) + "/with/key/" + String(WebHooksKey);
    String httpRequestData = "value1=" +  String("Intruders Alarm!!!");
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
      if (httpResponseCode == 200) Serial.println("Successfully sent");
      else Serial.println("Failed!");
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    Serial.print(" >> Wait for 5 Sec --> ");
    for (int i = 5; i > 0; i--)

    { Serial.print(i);
      delay(1000);
    }
    digitalWrite(LED_Green_Stastus, HIGH);
    digitalWrite(LED_Red_Stastus, LOW);
    Serial.println(" >> Ready");
  }
}
