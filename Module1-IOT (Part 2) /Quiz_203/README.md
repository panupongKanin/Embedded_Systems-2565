* [__Quiz_203 – Publish__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%202)%20/Quiz_203)
  - อ่านค่า DHT-22 แล้วส่งไปยัง MQTT Broker ทุกๆ 5 วินาที 
  - ควบคุมการแสดงผลให้ 4 LED แสดงผลตามข้อกำหนดดังนี้
  [![1-ST3e-Skg3mqbl-Bc-ZTkpvyyw.webp](https://i.postimg.cc/SQwp0vRd/1-ST3e-Skg3mqbl-Bc-ZTkpvyyw.webp)](https://postimg.cc/0rd4DZpK)

  [![2566-04-03-17-29-09.png](https://i.postimg.cc/8kLZ5Kwt/2566-04-03-17-29-09.png)](https://postimg.cc/bdNxVR7t)

  __Code__

  ```C++
  #include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
  #include <PubSubClient.h>
  #include <WiFi.h>
  #include <DHT.h> //https://www.arduinolibraries.info/libraries/dht-sensor-library
  #define DHT_SENSOR_PIN  15 // ESP32 pin GIOP21 connected to DHT22 sensor
  #define DHT_SENSOR_TYPE DHT22

  DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

  const char* mqtt_server = "test.mosquitto.org";
  const char* topic1 = "HomeArm1234";

  WiFiClient espClient;
  PubSubClient client(espClient);

  long lastMsg = 0;
  char msg[50];
  #define LED1 18
  #define LED2 19
  #define LED3 22
  #define LED4 23



  void LED_state(float tempp)
  { if (tempp < 24)
    { digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
    }
    else if (tempp >= 24 && tempp < 26)
    { digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
    }
    else if (tempp >= 26 && tempp < 28)
    { digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
    }
    else if (tempp >= 28 && tempp < 30)
    { digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
    }
    else if (tempp >= 30)
    { digitalWrite(LED1, HIGH); digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH); digitalWrite(LED4, HIGH); delay(250);
      digitalWrite(LED1, LOW); digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW); digitalWrite(LED4, LOW); delay(250);
    }
    else
    { digitalWrite(LED1, HIGH); delay(250);
      digitalWrite(LED1, LOW); delay(250);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
    }
  }

  void reconnect()
  { while (!client.connected()) // Loop until we're reconnected
    { Serial.print("Attempting MQTT connection...");
      String clientId = "ESP32 Client-";
      clientId += String(random(0xffff), HEX); // Create a random client ID
      if (client.connect(clientId.c_str())) // Attempt to connect
      { Serial.println("connected"); // Once connected, publish an announcement...
        client.publish(topic1, "Hello"); // ... and resubscribe
        client.subscribe(topic1);
      } else
      { Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        delay(5000);
      }
    }
  }

  void setup() {

    dht_sensor.begin(); // initialize the DHT sensor
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

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
    client.setServer(mqtt_server, 1883);

  }

  void loop() {
    // put your main code here, to run repeatedly:
    if (!client.connected()) reconnect();
    client.loop();
    long now = millis();
    // read humidity
    float humi  = dht_sensor.readHumidity();
    // read temperature in Celsius
    float tempC = dht_sensor.readTemperature();
    // read temperature in Fahrenheit
    float tempF = dht_sensor.readTemperature(true);

    LED_state(tempC);
    if (now - lastMsg > 5000)
    { lastMsg = now;
      snprintf (msg, 75, "Tempp: %.2f'C Humid: %.2f%%", tempC, humi);
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish(topic1, msg);
    }
  }
  ```

  __รูปการต่อวงจร – 1__
  
  [![01.jpg](https://i.postimg.cc/Gm3yMhjs/01.jpg)](https://postimg.cc/pp7rrv42)
  [![dszd.jpg](https://i.postimg.cc/kgRjgckc/dszd.jpg)](https://postimg.cc/YvkNX12G)
  [![2566-04-03-17-33-40.png](https://i.postimg.cc/rpWfrfMV/2566-04-03-17-33-40.png)](https://postimg.cc/t1qd0tsw)
  
  __รูปการต่อวงจร – 2__
  
  [![2566-04-03-17-35-41.png](https://i.postimg.cc/gk7JwDgB/2566-04-03-17-35-41.png)](https://postimg.cc/JGbmvbVb)

  __รูปการต่อวงจร – 3__
  
  [![IMG-0440.jpg](https://i.postimg.cc/1X9HqP3P/IMG-0440.jpg)](https://postimg.cc/njP7yymw)
  
  __ผลการทดลอง__
  
  * __หากการอ่านค่าแล้วเป็น null, หรือไม่มีเซ็นเซอร์__<br><br>
  ![bloggif_642abafb2d691](https://user-images.githubusercontent.com/111270076/229499035-bd1c65cc-1a57-45e1-b7fe-0fa595bc8814.gif)<br>
  * __ช่วงของอุณหภูมิ (-9999, 24)__<br><br>
  ![bloggif_642abcf830155](https://user-images.githubusercontent.com/111270076/229501599-dff9d06a-cba3-46b3-a9bc-938aea5a0cc9.gif)<br>
  * __ช่วงของอุณหภูมิ [24,26)__<br><br>
  ![bloggif_642abd6759c53](https://user-images.githubusercontent.com/111270076/229501640-286d0cc5-cf14-470e-afc0-29d73ca701fc.gif)<br>
  * __ช่วงของอุณหภูมิ [26,28)__<br><br>
  ![bloggif_642abda9db7db](https://user-images.githubusercontent.com/111270076/229501704-1c284b1e-e528-4276-be0a-cdea4df75693.gif)<br>
  * __ช่วงของอุณหภูมิ [28,30)__<br><br>
  ![bloggif_642abdeee2f03](https://user-images.githubusercontent.com/111270076/229501517-942147ec-4851-4c34-a071-f72356247e9d.gif)<br>
  * __ช่วงของอุณหภูมิ [30,9999)__<br><br>
  ![bloggif_642abead762e7](https://user-images.githubusercontent.com/111270076/229502004-60c1ccbc-3451-4d02-97ec-5acb863faab4.gif)<br>

  __หน้าจอ MQTT Lens__
  
  [![2566-04-03-17-32-21.png](https://i.postimg.cc/BbcWBq3v/2566-04-03-17-32-21.png)](https://postimg.cc/JHnd1CGw)