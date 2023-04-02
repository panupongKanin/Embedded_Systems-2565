# Module1-IOT (Part 2)

### แนวทางการใช้งานอินเทอร์เน็ตของสรรพสิ่งในระบบการผลิต IoT Approaches to Manufacturing System
### ขื่อ-สกุล : B6304577 นายภานุพงศ์ แคนอินทร์

* [__Quiz_201 – Web Control 2 LED__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%202)%20/Quiz_201)
  - อยากได้ปุ่มสำหรับคุมปิด-เปิด หลอดไฟ LED 2 ดวง
  - [โค้ดสี](https://www.colorhexa.com/008cba?fbclid=IwAR3dIZ_gRgDWmREmnzuknLbMxV3pOHy4YIPuLEz8-ZzTOX2VhWxcH2QjLGk)


  [![2566-04-02-20-16-19.png](https://i.postimg.cc/KjM8ZJf7/2566-04-02-20-16-19.png)](https://postimg.cc/zHqr7w93)

  
  
  __Code__

  ```C++
  #include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
  #include <WiFi.h>

  WiFiServer server(80);

  #define LED1 18
  #define LED2 19

  void setup() {
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

    pinMode(LED1, OUTPUT); // set the LED pin mode
    pinMode(LED2, OUTPUT);

  }

  bool LED1_Status, LED2_Status, LED3_Status, LED4_Status = LOW;
  void loop() {
    // put your main code here, to run repeatedly:
    WiFiClient client = server.available();
    digitalWrite(LED1, LED1_Status);
    digitalWrite(LED2, LED2_Status);
    if (client) {
      Serial.println("New Client.");
      String currentLine = "";
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.write(c);
          if (c == '\n') {
            if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.println("<html>");
              client.println("<body>");
              client.println("<h1>LED Status</h1>");

              client.println("<p>");
              if (LED1_Status == HIGH & LED2_Status == HIGH)
                client.println("LED1-On,LED2-On");
              else if (LED1_Status == HIGH & LED2_Status == LOW)
                client.println("LED1-On,LED2-Off");
              else if (LED1_Status == LOW & LED2_Status == HIGH)
                client.println("LED1-Off,LED2-On");
              else
                client.println("LED1-Off,LED2-Off");

              client.println("<p>");
              client.println("<h1>LED Control</h1>");
              client.println("<p>");
              client.println("<a href=\"/led1on\"><button style = \"background-color: #f44336;\">LED1 On</button></a>");
              client.println("<a href=\"/led2on\"><button style = \"background-color: #f44336;\">LED2 On</button></a>");
              client.println("</p>");
              client.println("<a href=\"/led1off\"><button style = \"background-color: #008CBA;\">LED1 Off</button></a>");
              client.println("<a href=\"/led2off\"><button style = \"background-color: #008CBA;\">LED2 Off</button></a>");

              client.println("<body>");
              client.println("<html>");
              break;
            } else {
              currentLine = "";
            }
          } else if (c != '\r') {
            currentLine += c;
          }
          if (currentLine.endsWith("GET /led1on")) LED1_Status = HIGH;
          if (currentLine.endsWith("GET /led1off")) LED1_Status = LOW;
          if (currentLine.endsWith("GET /led2on")) LED2_Status = HIGH;
          if (currentLine.endsWith("GET /led2off")) LED2_Status = LOW;
        }
      }
      client.stop();
      Serial.println("Client Disconnected.");
    }
  }
  ```

  __รูปการต่อวงจร – 1__
  
  [![01.jpg](https://i.postimg.cc/Gm3yMhjs/01.jpg)](https://postimg.cc/pp7rrv42)
  [![dszd.jpg](https://i.postimg.cc/kgRjgckc/dszd.jpg)](https://postimg.cc/YvkNX12G)
  
  __รูปการต่อวงจร – 2__
  
  [![2566-04-02-20-23-30.jpg](https://i.postimg.cc/vHBfQZpL/2566-04-02-20-23-30.jpg)](https://postimg.cc/jCpLctqL)

  __รูปการต่อวงจร – 3__
  
  [![IMG-0430.jpg](https://i.postimg.cc/QN6jr8g3/IMG-0430.jpg)](https://postimg.cc/z3RsC1Pt)

  __หน้าจอ Web Control__
  
  [![2566-04-02-20-37-46.png](https://i.postimg.cc/qMD3B5pn/2566-04-02-20-37-46.png)](https://postimg.cc/JGJnPKD4)

* [__Quiz_202 – Web Control 4 LED and Monitor Humid/Temperature__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%202)%20/Quiz_202)
  - เพิ่มเติมจาก Q202 อยากได้ปุ่มสำหรับคุมปิด-เปิด หลอดไฟ LED 4 ดวง
  - อยากมีกด Link ไปที่หน้า FB ของตัวเอง


  [![2566-04-02-22-00-45.jpg](https://i.postimg.cc/85mzqxDn/2566-04-02-22-00-45.jpg)](https://postimg.cc/WFtVZWdM)

    
  __Code__
  ส่วนที่ 1 ```Quiz_202.ino```

  ```C++
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
  ```

  ส่วนที่ 2 ```index.h```

  ```
  const char MAIN_page[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <body>
  <div id="demo">
  <h1>The ESP-32 Update web page without refresh</h1>
  <button type="button" onclick="sendData(11)" style="background: rgb(202, 60, 60); height: 40px; width: 100px">LED1 ON</button>
  <button type="button" onclick="sendData(21)" style="background: rgb(202, 60, 60); height: 40px; width: 100px">LED2 ON</button>
  <button type="button" onclick="sendData(31)" style="background: rgb(202, 60, 60); height: 40px; width: 100px">LED3 ON</button>
  <button type="button" onclick="sendData(41)" style="background: rgb(202, 60, 60); height: 40px; width: 100px">LED4 ON</button><br><br>
  <button type="button" onclick="sendData(10)" style="background: rgb(100,116,255); height: 40px; width: 100px">LED1 OFF</button>
  <button type="button" onclick="sendData(20)" style="background: rgb(100,116,255); height: 40px; width: 100px">LED2 OFF</button>
  <button type="button" onclick="sendData(30)" style="background: rgb(100,116,255); height: 40px; width: 100px">LED3 OFF</button>
  <button type="button" onclick="sendData(40)" style="background: rgb(100,116,255); height: 40px; width: 100px">LED4 OFF</button><br><br>
  State of [LED1, LED2, LED3, LED4] is >> <span id="LEDState">NA</span><br>
  </div>
  <div>
  <br>DHT-22 sensor : <span id="ADCValue">0</span><br>
  </div>
  <script>
  function sendData(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
  document.getElementById("LEDState").innerHTML =
  this.responseText;
  }
  };
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  xhttp.send();
  }
  setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
  }, 2000); 
  function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
  if (this.readyState == 4 && this.status == 200) {
  document.getElementById("ADCValue").innerHTML =
  this.responseText;
  }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
  }
  </script>
  <br><a href="https://www.facebook.com/profile.php?id=100006222361707">By Panupong Kaenin</a>
  <br><a href="https://github.com/panupongKanin">Github By Panupong Kaenin</a>
  </body>
  </html>
  )=====";
  ```

  __รูปการต่อวงจร – 1__
  
  [![01.jpg](https://i.postimg.cc/Gm3yMhjs/01.jpg)](https://postimg.cc/pp7rrv42)
  [![dszd.jpg](https://i.postimg.cc/kgRjgckc/dszd.jpg)](https://postimg.cc/YvkNX12G)
  
  __รูปการต่อวงจร – 2__
  
  [![2566-04-02-22-08-20.png](https://i.postimg.cc/Hk3wwvfH/2566-04-02-22-08-20.png)](https://postimg.cc/Sn2YqdSt)

  __รูปการต่อวงจร – 3__
  
  [![IMG-0431.jpg](https://i.postimg.cc/Sx50xdDQ/IMG-0431.jpg)](https://postimg.cc/5XwKPwhD)

  __หน้าจอ Web Control__
  
  [![2566-04-02-22-13-04.jpg](https://i.postimg.cc/90SP7DS9/2566-04-02-22-13-04.jpg)](https://postimg.cc/gLV692Gc)
