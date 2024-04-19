#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the I2C address if needed

void setup() {
    Serial.begin(115200);
    dht.begin();
    lcd.init();
    lcd.backlight();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Read MQ2 sensor data and take appropriate actions (e.g., send alerts)
    // For example, if alcohol content is detected, display a warning on the LCD
    int alcoholValue = analogRead(A0);
    if (alcoholValue > 200) {
        lcd.setCursor(0, 0);
        lcd.print("ALERT: Alcohol detected");
    } else {
        lcd.setCursor(0, 0);
        lcd.print("No alcohol detected");
    }

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("C Hum: ");
    lcd.print(humidity);
    lcd.print("%");

    delay(5000); // Wait for 5 seconds before reading again
}
