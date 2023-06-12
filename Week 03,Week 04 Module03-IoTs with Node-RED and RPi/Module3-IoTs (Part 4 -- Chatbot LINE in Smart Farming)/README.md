### Quiz_401 – RPi Smart Farm
##### • แสดงรูป โปรแกรม ของผลการทำงานตามหัวข้อ การสร้าง UI ด้วย Node-RED สำหรับฟาร์มอัจฉริยะ
#### โปรแกรมที่ใช้ทดสอบ
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%204%20--%20Chatbot%20LINE%20in%20Smart%20Farming)/Q401/RPi%20Smart%20Farm/w03-w04-Quiz_401_0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%204%20--%20Chatbot%20LINE%20in%20Smart%20Farming)/Q401/RPi%20Smart%20Farm/w03-w04-Quiz_401_0102.png" />

#### code สำหรับ ESP32 ที่ใช้
```
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h> //https://www.arduinolibraries.info/libraries/dht-sensor-library
#define DHT_SENSOR_PIN  4 // ESP32 pin GIOP4 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22
#include <ArduinoJson.h>

#define LED0_Pin 2
#define SW0_Pin  15

int SW0_Status = 99;
unsigned long lastMsg = 0;
char msg[50];

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

const char* ssid = "KOi";
const char* password = "13062544";
const char *mqtt_broker = "192.168.0.31";
const char *mqtt_username = "mymqtt";
const char *mqtt_password = "mymqtt";
const int mqtt_port = 1883;



WiFiClient espClient;
PubSubClient client(espClient);

void connectToWiFi() {
  byte mac[6];
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }

  WiFi.macAddress(mac);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToMQTTBroker() {
  byte mqttFailCount = 0;
  byte tooManyFailures = 10;
  // Loop until we're reconnected
  while (!client.connected()) {
    if (mqttFailCount <= tooManyFailures) {
      String client_id = "esp32-client-";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect("9z5srmKS2WAoFGYQaam1Py", mqtt_username, mqtt_password)) {
        Serial.println("Public Homezassistant mqtt broker connected");
        // Subscribe
        client.subscribe("feedback/status");
        client.subscribe("control/leds");
        delay(100);
      } else {
        mqttFailCount ++;
        Serial.print("Failed. Count = ");
        Serial.println(mqttFailCount);
        Serial.println("...trying again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
}

void MqttReceiverCallback(char* topic, byte * payload, unsigned int length) {
  char myPayLoad[50];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  { Serial.print((char)payload[i]);
    myPayLoad[i]    = payload[i];
    myPayLoad[i + 1]  = '\0'; // End of String
  }
  Serial.print("\n ---> ");   Serial.println(myPayLoad);
  myPayLoad[4] = '\0';  // String lessthan 4 Charector
  if ((String)myPayLoad == "ON1")    digitalWrite(LED0_Pin, HIGH);
  if ((String)myPayLoad == "OFF1")   digitalWrite(LED0_Pin, LOW);
}



void setup() {
  Serial.begin(115200);
  pinMode(LED0_Pin, OUTPUT);
  connectToWiFi();
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(MqttReceiverCallback);
  dht_sensor.begin(); // initialize the DHT sensor
}

void loop() {

  if (!client.connected()) {
    connectToMQTTBroker();
  }
  client.loop();

  if (digitalRead(SW0_Pin) != SW0_Status) {
    SW0_Status = digitalRead(SW0_Pin);
    Serial.println(SW0_Status == HIGH ? "Status Switch = OFF" : "Status Switch = ON");
    client.publish("feedback/switch", (SW0_Status == HIGH ? "SW_OFF" : "SW_ON"));
    delay(100);
  }

  unsigned long now = millis();
  if (now - lastMsg > 1000) {

    // read humidity
    float humi  = dht_sensor.readHumidity();
    // read temperature in Celsius
    float tempC = dht_sensor.readTemperature();
    // read temperature in Fahrenheit
    float tempF = dht_sensor.readTemperature(true);

    // check whether the reading is successful or not
    if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      snprintf (msg, 50, "Tempp=%0.2f,Humid=%0.2f", tempC, humi);


      if (client.connected()) {
        client.publish("feedback/sensors", msg);
        Serial.println(msg);
        Serial.println("MQTT: Send Data!!!");
        Serial.println();
      }
    }
    lastMsg = millis();
  }
}
```

#### code สำหรับ ESP32 ที่ใช้
```
[
    {
        "id": "8982e95ddaea1943",
        "type": "tab",
        "label": "Q401-0101",
        "disabled": false,
        "info": ""
    },
    {
        "id": "287869c0be568bc8",
        "type": "function",
        "z": "8982e95ddaea1943",
        "name": "",
        "func": "//   Tempp=38.20,Humid=73.52 \n\nvar msg1   = {};\nvar msg2 = {};\n\nvar output =   msg.payload.split(\",\");\n\nvar sTempp = output[0].split(\"=\");\nmsg1.payload = sTempp[1];\nmsg1.topic = 'Temperature';\n\nvar   sHumid = output[1].split(\"=\");\nmsg2.payload = sHumid[1];\nmsg2.topic = 'Humidity';\n\nreturn   [msg1,msg2];",
        "outputs": 2,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 400,
        "y": 280,
        "wires": [
            [
                "314e6fc73de0b3b2",
                "ffdc2f39a719cb9f"
            ],
            [
                "922989963c892994",
                "c87d555924e87fbc"
            ]
        ]
    },
    {
        "id": "922989963c892994",
        "type": "ui_gauge",
        "z": "8982e95ddaea1943",
        "tab": "5ab59fbbd41d64e9",
        "name": "Humidity",
        "group": "Farm",
        "order": "3",
        "format": "{{value}}",
        "min": 0,
        "max": "100",
        "x": 780,
        "y": 300,
        "wires": []
    },
    {
        "id": "1ee84dc4716b94ae",
        "type": "ui_switch",
        "z": "8982e95ddaea1943",
        "tab": "5ab59fbbd41d64e9",
        "name": "LED1",
        "topic": "topic",
        "group": "Farm",
        "order": "0",
        "onvalue": "ON1",
        "offvalue": "OFF1",
        "x": 150,
        "y": 460,
        "wires": [
            [
                "172f630b25f47c66"
            ]
        ]
    },
    {
        "id": "271f9555b85e5f30",
        "type": "mqtt in",
        "z": "8982e95ddaea1943",
        "name": "",
        "topic": "feedback/sensors",
        "qos": "0",
        "datatype": "auto-detect",
        "broker": "d9b6929cc83977a5",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 190,
        "y": 280,
        "wires": [
            [
                "287869c0be568bc8"
            ]
        ]
    },
    {
        "id": "172f630b25f47c66",
        "type": "mqtt out",
        "z": "8982e95ddaea1943",
        "name": "",
        "topic": "control/leds",
        "qos": "0",
        "retain": "false",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "d9b6929cc83977a5",
        "x": 750,
        "y": 460,
        "wires": []
    },
    {
        "id": "c87d555924e87fbc",
        "type": "ui_chart",
        "z": "8982e95ddaea1943",
        "tab": "5ab59fbbd41d64e9",
        "name": "",
        "group": "Farm",
        "order": "4",
        "interpolate": "linear",
        "nodata": "No Data",
        "removeOlder": 1,
        "removeOlderUnit": "86400",
        "x": 770,
        "y": 340,
        "wires": [
            [],
            []
        ]
    },
    {
        "id": "314e6fc73de0b3b2",
        "type": "ui_chart",
        "z": "8982e95ddaea1943",
        "tab": "5ab59fbbd41d64e9",
        "name": "",
        "group": "Farm",
        "order": "2",
        "interpolate": "linear",
        "nodata": "No Data",
        "removeOlder": 1,
        "removeOlderUnit": "86400",
        "x": 770,
        "y": 200,
        "wires": [
            [],
            []
        ]
    },
    {
        "id": "ffdc2f39a719cb9f",
        "type": "ui_gauge",
        "z": "8982e95ddaea1943",
        "tab": "5ab59fbbd41d64e9",
        "name": "Temperature",
        "group": "Farm",
        "order": "1",
        "format": "{{value}}",
        "min": 0,
        "max": "100",
        "x": 790,
        "y": 240,
        "wires": []
    },
    {
        "id": "5ab59fbbd41d64e9",
        "type": "ui_tab",
        "name": "Farm",
        "icon": "dashboard",
        "order": "1"
    },
    {
        "id": "d9b6929cc83977a5",
        "type": "mqtt-broker",
        "name": "",
        "broker": "192.168.0.31",
        "port": "1883",
        "clientid": "",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": "4",
        "keepalive": "60",
        "cleansession": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthRetain": "false",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closeQos": "0",
        "closeRetain": "false",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willRetain": "false",
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": ""
    }
]
```

#### การต่อวงจร
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%204%20--%20Chatbot%20LINE%20in%20Smart%20Farming)/Q401/RPi%20Smart%20Farm/w03-w04-Quiz_401_0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%204%20--%20Chatbot%20LINE%20in%20Smart%20Farming)/Q401/RPi%20Smart%20Farm/w03-w04-Quiz_401_0104.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week03-Week04_Module03/Module3-IoTs%20(Part%204%20--%20Chatbot%20LINE%20in%20Smart%20Farming)/Q401/RPi%20Smart%20Farm/w03-w04-Quiz_401_0105.png" />
