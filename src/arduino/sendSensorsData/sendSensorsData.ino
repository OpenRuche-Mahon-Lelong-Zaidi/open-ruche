#include <MKRWAN.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HX711.h>
#include <ArduinoLowPower.h>

LoRaModem modem;

String appEui = "1322144234234235";
String appKey = "A01DC8F9E363C86A883E41A6817427A5";

// MKRWAN 1310 connections
int DHT2_PIN = 5;
int DHT3_PIN = 2;
int DHT3_TYPE = DHT22;
int DOUT_PIN = 13;
int CLK_PIN = 14;
int photoresistorPin = A1;
int BUZZER_PIN = 3;
int ONE_WIRE_BUS = 9; // Pin commun pour les deux DS18B20
int batteryVoltagePin = A3;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT dht2(DHT2_PIN, DHT3_TYPE); // DHT 22
DHT dht3(DHT3_PIN, DHT3_TYPE); // DHT 22
HX711 scale;

// global variables
bool connected = false;
int err_count = 0;
short con = 0;
const float CALIBRATION_FACTOR = 1.045;

// Définition des durées pour le Morse de la LED pour dire "BEE" -> −··· · · 
const int dotDuration = 150;  // Durée d'un point
const int dashDuration = dotDuration * 3;  // Durée d'un trait (trois fois un point)
const int elementSpace = dotDuration;  // Espace entre éléments d'une lettre
const int letterSpace = dotDuration * 3;  // Espace entre lettres
const int wordSpace = dotDuration * 7;  // Espace entre mots

float readBatteryPercentage(){
    int sensorValue = analogRead(batteryVoltagePin);
    float batteryVoltage = (sensorValue / 1023.0) * 3.3 * ((100000.0 + 100000.0) / 100000.0); // Pont diviseur de tension R1 -> 100KOhms et R2 -> 100KOhms.
    float batteryPercentage = (batteryVoltage - 3.7) / (4.2 - 3.7) * 100;
    Serial.println("BATTERY VOLTAGE " + String(batteryVoltage) + " V");
    batteryPercentage = constrain(batteryPercentage, 0, 100);
    return batteryPercentage;
}

void setup() {
    initSound();
    initSerial();
    initModem();
    initSensors();
    initLoraConnection();
}

void toggleBuzzer(int duration) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
}

void initSound() {
    // Son buzzer en Morse pour dire "BEE"
    Serial.println("INITIALISATION... BEE");
    pinMode(BUZZER_PIN, OUTPUT);

    // Lettre B: "-..."
    toggleBuzzer(dashDuration);
    delay(elementSpace);
    toggleBuzzer(dotDuration);
    delay(elementSpace);
    toggleBuzzer(dotDuration);
    delay(elementSpace);
    toggleBuzzer(dotDuration);
    delay(letterSpace);

    // Lettre E: "."
    toggleBuzzer(dotDuration);
    delay(letterSpace);

    // Lettre E: "."
    toggleBuzzer(dotDuration);
}


void loop() {
    displayWeight();
    displayTemperatures();
    displayBatteryPercentage();
    handleLoRaConnection();
    //LowPower.deepSleep(120000); // Mise en veille 2 min
    
}

void initSerial() {
    Serial.begin(115200);
    //while (!Serial);
    Serial.println("Carte MKRWAN n°11 connectée !\nTentative de connexion à l'application TTN...");
}

void initLoraConnection(){
  while(!connected){
      Serial.print("Join test : ");
      Serial.println(++con);
      int ret = modem.joinOTAA(appEui, appKey);
      if (ret) {
          connected = true;
          modem.minPollInterval(60);
          Serial.println("Connected");
          modem.dataRate(5);
          delay(2000);
          err_count = 0;
      }
  }
    if (connected) {
        toggleBuzzer(1500);
    }
}

void initSensors() {
    sensors.begin();
    scale.begin(DOUT_PIN, CLK_PIN);
    scale.set_scale();
    scale.tare();
    scale.set_scale(CALIBRATION_FACTOR);
    dht2.begin();
    dht3.begin();
}

void initModem() {
    modem.begin(EU868);
}

void displayWeight() {
    Serial.print("[INFO] ");
    float weight_units = scale.get_units(10);
    if (weight_units < 0) weight_units = 0.00;
    float ounces = weight_units * 0.035274;
    long weight_grams = (long)(ounces * 100); // Multiplier par 100 pour une précision au dixième de gramme
    Serial.println("Poids mesuré = " + String(weight_grams / 100.0) + " grammes");
}

void displayTemperatures() {
    sensors.requestTemperatures();
    float ds18b20Temp1 = sensors.getTempCByIndex(0);
    float ds18b20Temp2 = sensors.getTempCByIndex(1);
    short dht2Temp = short(dht2.readTemperature());
    short dht3Temp = short(dht3.readTemperature());
    short dht2Humidity = short(dht2.readHumidity());
    short dht3Humidity = short(dht3.readHumidity());
    Serial.println("[INFO] Temperature DHT11 2 = " + String(dht2Temp) + " °C");
    Serial.println("[INFO] Temperature DHT11 3 = " + String(dht3Temp) + " °C");
    Serial.println("[INFO] Humidite DHT11 2 = " + String(dht2Humidity) + " %");
    Serial.println("[INFO] Humidite DHT11 3 = " + String(dht3Humidity) + " %");
    Serial.println("[INFO] Temperature DS18B20 (1) = " + String(short(ds18b20Temp1)) + " °C");
    Serial.println("[INFO] Temperature DS18B20 (2) = " + String(short(ds18b20Temp2)) + " °C");
}

void displayBatteryPercentage() {
    float batteryPercentage = readBatteryPercentage();
    Serial.println("[INFO] Pourcentage de batterie = " + String(batteryPercentage) + " %");
}

void handleLoRaConnection() {
    if (connected) {
        toggleBuzzer(1);
        int err = sendLoRaPacket();
        if (err <= 0) {
            handleLoRaError(err);
        } else {
            err_count = 0;
            delay(20000);
            Serial.println("Message envoyé");
        }
    }
}

int sendLoRaPacket() {
    sensors.requestTemperatures();
    float batteryPercentage = readBatteryPercentage();
    short batteryPercentageShort = static_cast<short>(batteryPercentage);
    float ds18b20Temp1 = sensors.getTempCByIndex(0);
    float ds18b20Temp2 = sensors.getTempCByIndex(1);
    short dht2Temp = short(dht2.readTemperature());
    short dht3Temp = short(dht3.readTemperature());
    short dht2Humidity = short(dht2.readHumidity());
    short dht3Humidity = short(dht3.readHumidity());
    int luminosityValue = analogRead(photoresistorPin);
    short shortLuminosityValue = (short)luminosityValue;
    float weight_units = scale.get_units(10);
    if (weight_units < 0) weight_units = 0.00;
    short ounces = (weight_units * 0.035274) / 10;
    Serial.println("poids envoyé : " + String(ounces) + " g");
    modem.beginPacket();
    modem.write(shortLuminosityValue);
    modem.write((short)ds18b20Temp1);
    modem.write((short)ds18b20Temp2);
    modem.write((short)ounces);
    modem.write(dht2Humidity);
    modem.write(dht3Humidity);
    modem.write(dht2Temp);
    modem.write(dht3Temp);
    modem.write(batteryPercentageShort);
    return modem.endPacket();
}

void handleLoRaError(int err) {
    Serial.print("Error : ");
    Serial.println(err);
    err_count++;
    if (err_count > 50) {
        connected = false;
    }
    for (int i = 0; i < 120; i++) {
        delay(1000);
    }
}
