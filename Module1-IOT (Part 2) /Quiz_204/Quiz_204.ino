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
#define SW1 4
#define SW2 5




void callback(char* topic, byte* payload, unsigned int length)
{ char myPayLoad[50];
  Serial.print("Message arrived [");
  Serial.print(topic1);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  { Serial.print((char)payload[i]);
    myPayLoad[i] = payload[i];
    myPayLoad[i + 1] = '\0'; // End of String
  }
  Serial.print("\n ---> "); Serial.println(myPayLoad);
  myPayLoad[4] = '\0'; // String lessthan 4 Charector
  if ((String)myPayLoad == "ON")
  { digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }
  if ((String)myPayLoad == "ON1") {
    digitalWrite(LED1, HIGH);
  }
  if ((String)myPayLoad == "ON2") {
    digitalWrite(LED2, HIGH);
  }
  if ((String)myPayLoad == "ON3") {
    digitalWrite(LED3, HIGH);
  }
  if ((String)myPayLoad == "ON4") {
    digitalWrite(LED4, HIGH);
  }
  if ((String)myPayLoad == "OFF")
  { digitalWrite(LED1, LOW); digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW); digitalWrite(LED4, LOW);
  }
  if ((String)myPayLoad == "OFF1") {
    digitalWrite(LED1, LOW);
  }
  if ((String)myPayLoad == "OFF2") {
    digitalWrite(LED2, LOW);
  }
  if ((String)myPayLoad == "OFF3") {
    digitalWrite(LED3, LOW);
  }
  if ((String)myPayLoad == "OFF4") {
    digitalWrite(LED4, LOW);
  }
}

void reconnect()
{
  while (!client.connected()) // Loop until we're reconnected
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
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

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
  client.setCallback(callback);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) reconnect();
  { client.loop();
    if (digitalRead(SW1) == 0)
    { client.loop();
      snprintf (msg, 75, "Overheat Alarm!!!");
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish(topic1, msg);
      while (digitalRead(SW1) == 0);
      delay(100);
    }
    if (digitalRead(SW2) == 0)
    { client.loop();
      snprintf (msg, 75, "Intruders Alarm!!!");
      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish(topic1, msg);
      while (digitalRead(SW2) == 0);
      delay(100);
    }
  }
  long now = millis();
  if (now - lastMsg > 5000)
  { lastMsg = now;
    // read humidity
    float humi  = dht_sensor.readHumidity();
    // read temperature in Celsius
    float tempC = dht_sensor.readTemperature();
    // read temperature in Fahrenheit
    float tempF = dht_sensor.readTemperature(true);
    snprintf (msg, 75, "Tempp: %.2f'C Humid: %.2f%%", tempC, humi);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic1, msg);
  }
}
