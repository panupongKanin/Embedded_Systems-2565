
#include <TM1638plus.h> [ver 1.9.1]
#include <DHT.h> //https://www.arduinolibraries.info/libraries/dht-sensor-library [ver 1.4.4]
#define DHT_SENSOR_PIN  15 // ESP32 pin GIOP21 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22

#define Brd_STB 18 // strobe  = GPIO connected to str0be line of module
#define Brd_CLK 19 // clock = GPIO connected to clock line of module
#define Brd_DIO 21 // data = GPIO connected to data line of module
bool high_freq = true; // default , if using high freq CPU > 100 MHz set to true

TM1638plus tm(Brd_STB, Brd_CLK, Brd_DIO, high_freq);


DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
  Serial.begin(9600);
  dht_sensor.begin(); // initialize the DHT sensor
  tm.displayBegin(); // initialize the TM1638
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

    tm.displayHex(0,int(tempC/10));
    tm.displayASCIIwDot(1,int(int(tempC)%10)+'0'); //turn on dot
    tm.displayHex(2,int(int(tempC*10))%10);
    tm.display7Seg(3,B01011000);

    tm.displayHex(4,int(humi/10));
    tm.displayASCIIwDot(5,int(int(humi)%10)+'0'); //turn on dot
    tm.displayHex(6,int(int(humi*10))%10);
    tm.display7Seg(7,B01110100);


  }

  // wait a 2 seconds between readings
  delay(2000);
}
