# Module1-IOT (Part 2)

### แนวทางการใช้งานอินเทอร์เน็ตของสรรพสิ่งในระบบการผลิต IoT Approaches to Manufacturing System
### ขื่อ-สกุล : B6304577 นายภานุพงศ์ แคนอินทร์

* [__Quiz_201 – Web Control 2 LED__](https://github.com/panupongKanin/Embedded_Systems-2565/tree/main/Module1-IOT%20(Part%202)%20/Quiz_201)
  - อยากได้ปุ่มสำหรับคุมปิด-เปิด หลอดไฟ LED 2 ดวง
  - [โค้ดสี](https://www.colorhexa.com/008cba?fbclid=IwAR3dIZ_gRgDWmREmnzuknLbMxV3pOHy4YIPuLEz8-ZzTOX2VhWxcH2QjLGk)


  [![2566-04-02-20-16-19.png](https://i.postimg.cc/KjM8ZJf7/2566-04-02-20-16-19.png)](https://postimg.cc/zHqr7w93)

  
  
  __Code__

  ```c++
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
  
  [![2566-04-02-20-39-42.jpg](https://i.postimg.cc/SskYHS69/2566-04-02-20-39-42.jpg)](https://postimg.cc/LqQs1M04)
  
  __รูปการต่อวงจร – 2__
  
  [![2566-04-02-20-23-30.jpg](https://i.postimg.cc/vHBfQZpL/2566-04-02-20-23-30.jpg)](https://postimg.cc/jCpLctqL)

  __รูปการต่อวงจร – 3__
  
  [![IMG-0430.jpg](https://i.postimg.cc/QN6jr8g3/IMG-0430.jpg)](https://postimg.cc/z3RsC1Pt)

  __หน้าจอ Web Control__
  
  [![2566-04-02-20-37-46.png](https://i.postimg.cc/qMD3B5pn/2566-04-02-20-37-46.png)](https://postimg.cc/JGJnPKD4)

