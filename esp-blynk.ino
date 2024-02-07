#define BLYNK_TEMPLATE_ID "TMPL6Ovill_dX"
#define BLYNK_TEMPLATE_NAME "DHT22"
#define BLYNK_AUTH_TOKEN "GHaG7DtSNGfY57fDpZfznkzfJoX_wgXj"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
char ssid[] = "Hocche Na Shona";
char pass[] = "TkNaiKen";

 // Pin connected to the DHT sensor
#define DHTPIN 2
#define DHTTYPE DHT22

BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);

  unsigned status;
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    while (1) delay(10);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}

void loop()
{
  Blynk.run();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float pressure = bmp.readPressure()/1000;
  float altitude = bmp.readAltitude(1013.25);
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0,temperature);
  Blynk.virtualWrite(V1,humidity);
  Blynk.virtualWrite(V2,pressure);
  Blynk.virtualWrite(V3,altitude);
  delay(10000);
}
