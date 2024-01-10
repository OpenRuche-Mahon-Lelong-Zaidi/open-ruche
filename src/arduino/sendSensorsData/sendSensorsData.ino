// OpenRuche Project
// Author: Grégoire MAHON
// Team: MAHON - LELONG - BOUKENHAISSI LAHRECHE - ZAIDI
// Project: OpenRuche
// Course: Polytech Sorbonne EI2I 4 II 2024

#include <MKRWAN.h>            // Library for LoRaWAN communication
#include <DHT.h>               // Library for DHT temperature and humidity sensors
#include <OneWire.h>           // Library for one-wire communication protocol
#include <DallasTemperature.h> // Library for Dallas temperature sensors
#include <HX711.h>             // Library for HX711 weight sensor
#include <ArduinoLowPower.h>   // Library for low-power management

// LoRa modem initialization with application unique identifiers
LoRaModem modem;
const String appEui = "1322144234234235";
const String appKey = "A01DC8F9E363C86A883E41A6817427A5";

// Pin assignments for sensors and actuators
const int DHT2_PIN = 3, DHT3_PIN = 2, DHT3_TYPE = DHT22;
const int DOUT_PIN = 13, CLK_PIN = 14, photoresistorPin = A1, BUZZER_PIN = 5;
const int ONE_WIRE_BUS = 9, batteryVoltagePin = A6; // Pin for DS18B20 sensors

// Sensor instances
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT dht2(DHT2_PIN, DHT3_TYPE), dht3(DHT3_PIN, DHT3_TYPE);
HX711 scale;

// Global variables for system state and calibration
bool connected = false;
int err_count = 0;
short con = 0;
const float CALIBRATION_FACTOR = 1.095; // Calibration factor for scale

// Morse code timings for LED signaling
const int dotDuration = 150, dashDuration = dotDuration * 3;
const int elementSpace = dotDuration, letterSpace = dotDuration * 3, wordSpace = dotDuration * 7;

// Function to calculate battery percentage
float readBatteryPercentage() {
    int sensorValue = analogRead(batteryVoltagePin);
    // Convert analog value to battery percentage
    float batteryVoltage = (sensorValue / 1023.0) * 3.3 * ((100000.0 + 100000.0) / 100000.0);
    return constrain((batteryVoltage - 3.7) / (4.2 - 3.7) * 100, 0, 100);
}

// System setup functions
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

void initModem() {
    modem.begin(EU868);
}

void initSound() {
    Serial.println("INITIALISATION... BEE");
    pinMode(BUZZER_PIN, OUTPUT);
    // Morse code for "BEE"
    toggleBuzzer(dashDuration); delay(elementSpace); // B
    toggleBuzzer(dotDuration); delay(elementSpace);
    toggleBuzzer(dotDuration); delay(elementSpace);
    toggleBuzzer(dotDuration); delay(letterSpace);
    toggleBuzzer(dotDuration); delay(letterSpace); // E
    toggleBuzzer(dotDuration); // E
}

void loop() {
    displayWeight();
    displayTemperatures();
    displayBatteryPercentage();
    handleLoRaConnection();
    // Uncomment for deep sleep mode: LowPower.deepSleep(120000);
}

void initSerial() {
    Serial.begin(115200);
    Serial.println("Carte MKRWAN n°11 connectée !\nTentative de connexion à l'application TTN...");
}

void initLoraConnection() {
    while (!connected) {
        Serial.print("Join test : ");
        Serial.println(++con);
        if (modem.joinOTAA(appEui, appKey)) {
            connected = true;
            modem.minPollInterval(60);
            Serial.println("Connected");
            modem.dataRate(5);
            delay(2000);
            err_count = 0;
        }
    }
    if (connected) toggleBuzzer(1500);
}

void initSensors() {
    sensors.begin();
    scale.begin(DOUT_PIN, CLK_PIN);
    scale.set_scale(CALIBRATION_FACTOR);
    dht2.begin();
    dht3.begin();
}

void displayWeight() {
    float weight_units = scale.get_units(10);
    if (weight_units < 0) weight_units = 0.00;
    long weight_grams = (long)(weight_units * 0.035274 * 100);
    Serial.println("Poids mesuré = " + String(weight_grams / 100.0) + " grammes");
}

void displayTemperatures() {
    sensors.requestTemperatures();
    // Temperature readings from DS18B20 and DHT sensors
    Serial.println("[INFO] Temperature DHT22 2 = " + String(short(dht2.readTemperature())) + " °C");
    Serial.println("[INFO] Temperature DHT22 3 = " + String(short(dht3.readTemperature())) + " °C");
    Serial.println("[INFO] Humidite DHT22 2 = " + String(short(dht2.readHumidity())) + " %");
    Serial.println("[INFO] Humidite DHT22 3 = " + String(short(dht3.readHumidity())) + " %");
    Serial.println("[INFO] Temperature DS18B20 (1) = " + String(short(sensors.getTempCByIndex(0))) + " °C");
    Serial.println("[INFO] Temperature DS18B20 (2) = " + String(short(sensors.getTempCByIndex(1))) + " °C");
}

void displayBatteryPercentage() {
    Serial.println("[INFO] Pourcentage de batterie = " + String(readBatteryPercentage()) + " %");
}

void handleLoRaConnection() {
    if (connected) {
        toggleBuzzer(1);
        if (sendLoRaPacket() <= 0) handleLoRaError();
        else {
            err_count = 0;
            delay(20000);
            Serial.println("Message envoyé");
        }
    }
}

int sendLoRaPacket() {
    // Prepare and send a data packet via LoRa
    sensors.requestTemperatures();
    // Data aggregation for packet
    modem.beginPacket();
    modem.write((short)analogRead(photoresistorPin));
    modem.write((short)(sensors.getTempCByIndex(0) * 100));
    modem.write((short)(sensors.getTempCByIndex(1) * 100));
    modem.write((short)(scale.get_units(10) * 0.035274 / 10));
    modem.write((short)(dht2.readHumidity() * 100));
    modem.write((short)(dht3.readHumidity() * 100));
    modem.write((short)(dht2.readTemperature() * 100));
    modem.write((short)(dht3.readTemperature() * 100));
    modem.write((short)readBatteryPercentage());
    return modem.endPacket();
}

void handleLoRaError() {
    Serial.print("Error : ");
    Serial.println(err);
    if (++err_count > 50) connected = false;
    delay(120000); // Error handling delay
}
