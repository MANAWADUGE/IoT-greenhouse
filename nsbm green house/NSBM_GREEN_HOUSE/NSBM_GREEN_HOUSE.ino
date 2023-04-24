#define BLYNK_TEMPLATE_ID "TMPL6f9G-D5n9"
#define BLYNK_TEMPLATE_NAME "Green House"
#define BLYNK_AUTH_TOKEN "8Is7kmBmVarzaHQJQvXJUUDHSlvZ0RgU"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

constexpr uint8_t RST_PIN = 22;
constexpr uint8_t SS_PIN = 21;
#define I2C_SDA 33
#define I2C_SCL 32
#define DS18B20PIN 13
#define DHTPIN 25
#define DHTTYPE DHT11
#define soil 34
#define pump 16
#define mist 17
#define buzzer 15
#define led_blue 26
#define led_green 27

MFRC522 mfrc522(SS_PIN, RST_PIN);
OneWire oneWire(DS18B20PIN);
DallasTemperature sensor(&oneWire);
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

String s1;
int water_temp, h, t, soil_data, Pressure, stt;
String door_st = "CLOSE";
String pump_st = "OFF";
String mist_st = "OFF";

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SLT FIBRE1";
char pass[] = "dilshan21";

String serverName = "http://192.168.43.181/nsbm_green_house/history.php";

unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

void myTimerEvent() {

  Blynk.virtualWrite(V2, water_temp);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V3, soil_data);
}
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
}
BLYNK_WRITE(V4) {
  int button = param.asInt();
  Serial.print("BUTTON PUMP:  ");
  Serial.println(button);
  if (button == HIGH) {
    digitalWrite(pump, LOW);
    pump_st = "ON";
  } else {
    digitalWrite(pump, HIGH);
    pump_st = "OFF";
  }
}
BLYNK_WRITE(V5) {
  int button = param.asInt();
  Serial.print("BUTTON MIST:  ");
  Serial.println(button);
  if (button == HIGH) {
    digitalWrite(mist, LOW);
    mist_st = "ON";
  } else {
    digitalWrite(mist, HIGH);
    mist_st = "OFF";
  }
}

void setup() {

  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  pinMode(mist, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_green, OUTPUT);
  digitalWrite(led_blue, HIGH);
  digitalWrite(led_green, LOW);
  digitalWrite(pump, HIGH);
  digitalWrite(mist, HIGH);
  Blynk.begin(auth, ssid, pass);
  pinMode(soil, INPUT);
  pinMode(buzzer, OUTPUT);

  SPI.begin();
  Wire.begin(I2C_SDA, I2C_SCL);
  sensor.begin();
  dht.begin();
  mfrc522.PCD_Init();

  if (!bmp.begin(0x77)) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
  }

}

void loop() {
  Blynk.run();
  myTimerEvent();

  rfidprocess();
  bmpRead();
  rd18b20();
  tempRead();
  historyReq();
  soilRead();

}
void rfidprocess() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) { // Look for new cards
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {  // Select one of the cards
    return;
  }
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  String s = content.substring(1);
  s1 = s;
  s1.replace(" ", "");
  Serial.println("CardID: " + s1);

  if (s1 == "D71FBEB4" && stt == 0) {
    digitalWrite(led_blue, LOW);
    digitalWrite(buzzer, HIGH);
    digitalWrite(led_green, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    door_st = "OPEN";
    stt = 1;

  } else if (s1 == "D71FBEB4" && stt == 1) {
    digitalWrite(led_blue, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(led_green, LOW);
    delay(500);
    digitalWrite(buzzer, LOW);
    door_st = "CLOSE";
    stt = 0;
  }

}
void bmpRead() {
  Serial.print("Pressure = ");
  Pressure = bmp.readPressure();
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
}
void rd18b20() {
  sensor.requestTemperatures();
  Serial.print("Temperature is: ");
  Serial.println(sensor.getTempCByIndex(0));
  water_temp = sensor.getTempCByIndex(0);

}
void tempRead() {
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

}
void soilRead() {
  soil_data = analogRead(soil);
  soil_data = map(soil_data, 0, 4095, 0, 100);
  Serial.print("soil_data: ");
  Serial.println(soil_data);
}
void historyReq() {

  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      WiFiClient client;

      String serverPath = serverName + "?api_key=tPmAT5Ab3j7F9&Pressure=" + Pressure + "&Water_Temperature=" + water_temp + "&Humidity=" + h + "&Temperature=" + t + "&Soil=" + soil_data + "%&Pump_status=" + pump_st + "&Mist_status=" + mist_st + "&Door_status=" + door_st + "";
      Serial.println(serverPath);
      http.begin(client, serverPath.c_str());
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
