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
