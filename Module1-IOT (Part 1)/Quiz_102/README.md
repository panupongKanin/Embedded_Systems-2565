* __Quiz_102 – ปรับการแสดงผลที่ Serial Monitor เป็นดังนี้__

  [![2566-04-01-19-11-49.png](https://i.postimg.cc/4nC3C0f7/2566-04-01-19-11-49.png)](https://postimg.cc/N24tmprB)
  __Code__
  
  
```c++
#include <DHT.h> //https://www.arduinolibraries.info/libraries/dht-sensor-library
#define DHT_SENSOR_PIN  21 // ESP32 pin GIOP21 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
  Serial.begin(9600);
  dht_sensor.begin(); // initialize the DHT sensor
}

void loop() {
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

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.print("°F");
    

    Serial.print(" | ");

    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.println("%");

    
  }

  // wait a 2 seconds between readings
  delay(2000);
}

```

  __รูปการต่อวงจร – 1__
   
   [![IMG-0413.jpg](https://i.postimg.cc/3wy3MGSP/IMG-0413.jpg)](https://postimg.cc/Y4w5Yvw3)
   
   __รูปการต่อวงจร – 2__
   
   [![IMG-0414.jpg](https://i.postimg.cc/vm6w2sDy/IMG-0414.jpg)](https://postimg.cc/B8sztRx7)
   
   __รูปการต่อวงจร – 3__
   
   [![2566-04-01-22-44-43.png](https://i.postimg.cc/VsgpR64M/2566-04-01-22-44-43.png)](https://postimg.cc/NLydGQ3f)