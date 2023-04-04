#define BLYNK_PRINT Serial


/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <BlynkSimpleEsp32.h>


char ssid[50] = ""; // increase the size of the character array to fit the maximum length of a WiFi SSID
char pass[50] = ""; // increase the size of the character array to fit the maximum length of a WiFi password


#define LED1 18
#define LED2 19
#define LED3 22
#define LED4 23
int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;
int ledState4 = LOW;

BLYNK_WRITE(V18) {
  ledState1 = param.asInt();
  digitalWrite(LED1, ledState1);
}
BLYNK_WRITE(V19) {
  ledState2 = param.asInt();
  digitalWrite(LED2, ledState2);
}
BLYNK_WRITE(V22) {
  ledState3 = param.asInt();
  digitalWrite(LED3, ledState3);
}
BLYNK_WRITE(V23) {
  ledState4 = param.asInt();
  digitalWrite(LED4, ledState4);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);

  ssid[0] = '\0'; // null-terminate the character array to avoid garbage values
  pass[0] = '\0'; // null-terminate the character array to avoid garbage values

  
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
    Serial.println(res);
  }
  
  // use strcpy() to copy the String values into the character arrays
  strcpy(ssid, wm.getWiFiSSID().c_str());
  strcpy(pass, wm.getWiFiPass().c_str());
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
