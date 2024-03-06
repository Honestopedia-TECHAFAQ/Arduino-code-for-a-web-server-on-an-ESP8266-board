#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const int webServerPort = 80;

ESP8266WebServer server(webServerPort);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupWiFi() {
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void handleRoot() {
  float temperature = 25.5;
  float humidity = 60.0;
  int gas_ppm = 100;
  float ph_value = 7.0;
  String sensorData = "Temperature: " + String(temperature) + " C, Humidity: " + String(humidity) + " %, Gas: " + String(gas_ppm) + " ppm, pH: " + String(ph_value);
  server.send(200, "text/plain", sensorData);
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  setupWiFi();
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  float temperature = readTemperatureSensor();
  float humidity = readHumiditySensor();
  int gas_ppm = readGasSensor();
  float ph_value = readPhSensor();
  
  updateLCD(temperature, humidity, gas_ppm, ph_value);
  server.handleClient();
  delay(1000);
}

float readTemperatureSensor() {
  // Code to read temperature sensor
  return 25.5;
}

float readHumiditySensor() {
  // Code to read humidity sensor
  return 60.0;
}

int readGasSensor() {
  // Code to read gas sensor
  return 100;
}

float readPhSensor() {
  // Code to read pH sensor
  return 7.0;
}

void updateLCD(float temperature, float humidity, int gas_ppm, float ph_value) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C  Humidity: ");
  lcd.print(humidity);
  lcd.setCursor(0, 1);
  lcd.print("Gas: ");
  lcd.print(gas_ppm);
  lcd.print(" ppm  pH: ");
  lcd.print(ph_value);
}
