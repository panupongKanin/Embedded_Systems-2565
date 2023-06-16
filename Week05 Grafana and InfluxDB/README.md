### Visualize Sensor data using Grafana and InfluxDB
##### ขั้นตอนการอ่านข้อมูล จาก Sensor มาเก็บไว้ที่ InfluxDB แล้ว ใช้ Grafana ในการ monitor ข้อมูล
#### Step-1: Test DHT-22 Sensor

1. DHT-22 : https://www.cybertice.com/p/697 >> Read Temperature >> Read Humidity

#### Code ที่ใช้
```
#include "DHT.h"

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

```

#### ผลการทดสอบ 1
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-1_Test%20DHT-22%20and%20BMP-280%20Sensor/DHT-22%20/s01-0101.png" />

#### ผลการทดสอบ 2
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-1_Test%20DHT-22%20and%20BMP-280%20Sensor/DHT-22%20/s01-0102.png" />

2. How to use BMP-280  https://www.circuitschools.com/interfacing-bmp280-with-esp-32-on-i2c-with-errors-and-solutions/ >> Read Temperature >> Read Pressure >> Read Altitude	

#### Code ที่ใช้
```

#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void setup() {
  Serial.begin(9600);
  Serial.println(F("BMP280 Forced Mode Test."));

  //if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  // must call this to wake sensor up and get new measurement data
  // it blocks until measurement is complete
  if (bmp.takeForcedMeasurement()) {
    // can now print out the new measurements
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);
  } else {
    Serial.println("Forced measurement failed!");
  }


}

```
#### ผลการทดสอบ 1
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-1_Test%20DHT-22%20and%20BMP-280%20Sensor/BMP-280%20/s01-0201.png" />

#### ผลการทดสอบ 2
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-1_Test%20DHT-22%20and%20BMP-280%20Sensor/BMP-280%20/s01-0202.png" />

!!! But unfortunately, we got an error, saying, “Could not find a valid bmp 280 sensor, check wiring.”

To solve this, first we need to find the, i2c address of the bmp sensor, with i2c scanner, like our previous tutorials, link for the code here. upload the code, and open serial monitor, to check the i2c address, where it was 0x76. note it down, and get back to our previous sample code, and type the address, in the sensor initialization line, as shown.

#### Code ที่ใช้

```
#include <Wire.h> //include Wire.h library
 
void setup()
{
  Wire.begin(); // Wire communication begin
  Serial.begin(9600); // The baudrate of Serial monitor is set in 9600
  while (!Serial); // Waiting for Serial Monitor
  Serial.println("\nI2C address Scanner");
}
 
void loop()
{
  byte error, address; //variable for error and I2C address
  int devicecount;
 
  Serial.println("Scanning...");
 
  devicecount = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      devicecount++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (devicecount == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000); // wait 5 seconds for the next I2C scan
}
```
#### ผลการทดสอบ 1
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-1_Test%20DHT-22%20and%20BMP-280%20Sensor/BMP-280%20/s01-0203.png" />


#### Step-2: InfluxDB → Bucket Name = “B6304577”
1. https://www.influxdata.com/get-influxdb/ : Login to influxDB Clound 2.0
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0101.png" />

2. Register InfluxDB
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0102.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0104.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0105.png" />

3. Create Bucket
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0106.png" />

2. Register InfluxDB
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0107.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0108.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0109.png" />

4. Create Tokenkey
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0110.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0111.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0112.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-2_InfluxDB%20/s02-0113.png" />

#### Step-3: ESP32 Code
1. Add Library
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-3_ESP32%20Code/s03-0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-3_ESP32%20Code/s03-0102.png" />

2. Code write data to InfluxDB
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-3_ESP32%20Code/s03-0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-3_ESP32%20Code/s03-0104.png" />

3. Monitor
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-3_ESP32%20Code/s03-0105.png" />

#### Step-4: Grafana → Dashboard Name = “01”
1. https://grafana.com/	 Create free account (or Sign in)
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0101.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0102.png" />

2. Import Data
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0103.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0104.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0105.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0106.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0107.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0108.png" />

3. Create Dashboard
<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0109.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0110.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0111.png" />

<img src= "https://github.com/panupongKanin/Embedded_Systems-2565/blob/main/image/Week05%20Grafana%20and%20InfluxDB/Step-4_Grafana%20/s04-0112.png" />

