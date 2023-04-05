# Module1-IOT (Part 3)

### แนวทางการใช้งานอินเทอร์เน็ตของสรรพสิ่งในระบบการผลิต IoT Approaches to Manufacturing System
### ขื่อ-สกุล : B6304577 นายภานุพงศ์ แคนอินทร์

* [__Quiz_301 – 4 External LED Control__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%203)/Quiz_301)

  [![2566-04-05-00-01-42.png](https://i.postimg.cc/mrS1YqNQ/2566-04-05-00-01-42.png)](https://postimg.cc/XZpv3sPJ)

  __Code__

  ```C++
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
  ```
  __รูปหน้าจอ Blynk__

  [![IMG-0-CAA8-F6-D46-CA-1.jpg](https://i.postimg.cc/c4bf5V3Z/IMG-0-CAA8-F6-D46-CA-1.jpg)](https://postimg.cc/568HXKpk)

  __รูปการต่อวงจร – 1__
  
  [![01.jpg](https://i.postimg.cc/Gm3yMhjs/01.jpg)](https://postimg.cc/pp7rrv42)
  [![dszd.jpg](https://i.postimg.cc/kgRjgckc/dszd.jpg)](https://postimg.cc/YvkNX12G)
  
  __รูปการต่อวงจร – 2__
  
  [![2566-04-05-00-08-47.png](https://i.postimg.cc/3RmGyRfx/2566-04-05-00-08-47.png)](https://postimg.cc/DJf0H2K9)

  __รูปการต่อวงจร – 3__
  
  [![IMG-0470.jpg](https://i.postimg.cc/Jz7KVF5c/IMG-0470.jpg)](https://postimg.cc/4mMppBMm)


* [__Quiz_302 – DHT22 + 4 LED + 2 Switch__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%203)/Quiz_302)

  [![2566-04-05-18-25-00.png](https://i.postimg.cc/m2hwqzQJ/2566-04-05-18-25-00.png)](https://postimg.cc/BX9HPv7B)

  __Code__

  ```C++
  #define BLYNK_PRINT Serial

  /* Fill-in information from Blynk Device Info here */
  #define BLYNK_TEMPLATE_ID "TMPxxxxxx"
  #define BLYNK_TEMPLATE_NAME "Device"
  #define BLYNK_AUTH_TOKEN "YourAuthToken"

  #include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
  #include <BlynkSimpleEsp32.h>
  #include <DHT.h> //https://www.arduinolibraries.info/libraries/dht-sensor-library
  #define DHT_SENSOR_PIN  15 // ESP32 pin GIOP21 connected to DHT22 sensor
  #define DHT_SENSOR_TYPE DHT22

  DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

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

  #define SW1 4
  #define SW2 5


  int lastSteadyState_SW1 = LOW;       // the previous steady state from the input pin
  int lastSteadyState_SW2 = LOW;       // the previous steady state from the input pin
  int lastFlickerableState_SW1 = LOW;  // the previous flickerable state from the input pin
  int lastFlickerableState_SW2 = LOW;  // the previous flickerable state from the input pin
  int currentState_SW1;                // the current reading from the input pin
  int currentState_SW2;                // the current reading from the input pin
  int SW1_state = 0;    // the current state of SW
  int SW2_state = 0;    // the current state of SW

  int n = 1;

  #define DEBOUNCE_TIME  50 // the debounce time in millisecond, increase this time if it still chatters
  unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

  BlynkTimer timer;

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

  void sendSensor()
  {
    float h = dht_sensor.readHumidity();
    float t = dht_sensor.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V5, t);
    Blynk.virtualWrite(V6, h);
  }

  //void sendFromBTN()
  //{
  //
  //  if (digitalRead(SW1) == 0) {
  //    Blynk.virtualWrite(V7, "0");
  //  } else {
  //    Blynk.virtualWrite(V7, "1");
  //  }
  //    if (digitalRead(SW2) == 0) {
  //      Blynk.virtualWrite(V8, "0");
  //    } else {
  //      Blynk.virtualWrite(V8, "1");
  //    }
  //}

  void sendFromSW1() {

    // read the state of the switch/button:
    currentState_SW1 = digitalRead(SW1);

    // If the switch/button changed, due to noise or pressing:
    if (currentState_SW1 != lastFlickerableState_SW1) {
      // reset the debouncing timer
      lastDebounceTime = millis();
      // save the the last flickerable state
      lastFlickerableState_SW1 = currentState_SW1;
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (lastSteadyState_SW1 == HIGH && currentState_SW1 == LOW) {
        SW1_state = n - SW1_state;
        n = 1;
        Serial.println(SW1_state);
      }

      // save the the last steady state
      lastSteadyState_SW1 = currentState_SW1;
    }
    if (SW1_state == 1) {
      Blynk.virtualWrite(V7, "SW1 is on !!!");
    } else {
      Blynk.virtualWrite(V7, "SW1 is off !!!");
    }
  }

  void sendFromSW2() {

    // read the state of the switch/button:
    currentState_SW2 = digitalRead(SW2);

    if (currentState_SW2 != lastFlickerableState_SW2) {
      // reset the debouncing timer
      lastDebounceTime = millis();
      // save the the last flickerable state
      lastFlickerableState_SW2 = currentState_SW2;
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:
      // if the button state has changed:
      if (lastSteadyState_SW2 == HIGH && currentState_SW2 == LOW) {
        SW2_state = n - SW2_state;
        n = 1;
        Serial.println(SW2_state);
      }
      // save the the last steady state
      lastSteadyState_SW2 = currentState_SW2;
    }
    if (SW2_state == 1) {
      Blynk.virtualWrite(V8, "SW2 is on !!!");
    } else {
      Blynk.virtualWrite(V8, "SW2 is off !!!");
    }

  }


  void setup()
  {
    // Debug console
    Serial.begin(9600);

    dht_sensor.begin(); // initialize the DHT sensor
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(SW1, INPUT_PULLUP);
    pinMode(SW2, INPUT_PULLUP);

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

    // Setup a function to be called every second
    timer.setInterval(1000L, sendSensor);
    timer.setInterval(100L, sendFromSW1);
    timer.setInterval(100L, sendFromSW2);

  }

  void loop()
  {
    Blynk.run();
    timer.run();
  }
  ```
  __รูปหน้าจอ Blynk__

  [![IMG-6707.png](https://i.postimg.cc/SRR02SH5/IMG-6707.png)](https://postimg.cc/XGR1tbjc)

  __รูปการต่อวงจร – 1__
  
  [![01.jpg](https://i.postimg.cc/Gm3yMhjs/01.jpg)](https://postimg.cc/pp7rrv42)
  [![dszd.jpg](https://i.postimg.cc/kgRjgckc/dszd.jpg)](https://postimg.cc/YvkNX12G)
  
  __รูปการต่อวงจร – 2__
  
  [![2566-04-05-00-08-47.png](https://i.postimg.cc/3RmGyRfx/2566-04-05-00-08-47.png)](https://postimg.cc/DJf0H2K9)

  __รูปการต่อวงจร – 3__
  
  [![IMG-0478.jpg](https://i.postimg.cc/q7Q64QrL/IMG-0478.jpg)](https://postimg.cc/cKgLcRrg)

* [__Quiz_303 – Social Alert__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%203)/Quiz_303)

  * กดปุ่ม B ที่ต่อกับ ESP32– ให้ส่งข้อความ “Door Open Alarm”
  * กดปุ่ม C ที่ต่อกับ ESP32– ให้ส่งข้อความ “Intruders Alarm”

  [![2566-04-05-20-48-55.png](https://i.postimg.cc/x105ybhh/2566-04-05-20-48-55.png)](https://postimg.cc/bsB1qdz9)

  __Code__

  ```C++
  ##include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
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
  ```

  __รูปการต่อวงจร – 1__
  
  [![01.jpg](https://i.postimg.cc/Gm3yMhjs/01.jpg)](https://postimg.cc/pp7rrv42)
  [![dszd.jpg](https://i.postimg.cc/kgRjgckc/dszd.jpg)](https://postimg.cc/YvkNX12G)
  
  __รูปการต่อวงจร – 2__
  
  [![2566-04-05-20-52-30.png](https://i.postimg.cc/HWFXk7TX/2566-04-05-20-52-30.png)](https://postimg.cc/V5Bd7vrk)

  __รูปการต่อวงจร – 3__
  
  [![IMG-0479.jpg](https://i.postimg.cc/cLH9GnhY/IMG-0479.jpg)](https://postimg.cc/PPgzmNBr)

    __รูปหน้าจอ LINE ผลการทดสอบ__

  [![IMG-6707.png](https://i.postimg.cc/SRR02SH5/IMG-6707.png)](https://postimg.cc/XGR1tbjc)
