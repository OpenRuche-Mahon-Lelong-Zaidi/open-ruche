#include <MKRWAN.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HX711.h>
#include <ArduinoLowPower.h>

// Initialize LoRa modem with application unique identifiers
LoRaModem modem;
String appEui = "1322144234234235";
String appKey = "A01DC8F9E363C86A883E41A6817427A5";

// Define connection pins for various sensors
int DHT2_PIN = 3;
int DHT3_PIN = 2;
int DHT3_TYPE = DHT22;
int DOUT_PIN = 13;
int CLK_PIN = 14;
int photoresistorPin = A1;
int BUZZER_PIN = 5;
int ONE_WIRE_BUS = 9; // Shared pin for DS18B20 sensors
int batteryVoltagePin = A6;

// Initialize sensors
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT dht2(DHT2_PIN, DHT3_TYPE);
DHT dht3(DHT3_PIN, DHT3_TYPE);
HX711 scale;

// Global variables for connectivity and calibration
bool connected = false;
int err_count = 0;
short con = 0;
const float CALIBRATION_FACTOR = 1.095; // 1.045

// Morse code durations for LED signaling
const int dotDuration = 150; // Dot duration
const int dashDuration = dotDuration * 3; // Dash duration (three times a dot)
const int elementSpace = dotDuration; // Space between elements of a letter
const int letterSpace = dotDuration * 3; // Space between letters
const int wordSpace = dotDuration * 7; // Space between words

// Function to calculate battery percentage
float readBatteryPercentage() {
    int sensorValue = analogRead(batteryVoltagePin);
    float batteryVoltage = (sensorValue / 1023.0) * 3.3 * ((100000.0 + 100000.0) / 100000.0);
    float batteryPercentage = (batteryVoltage - 3.7) / (4.2 - 3.7) * 100;
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

// Toggle buzzer function
void toggleBuzzer(int duration) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
}

void initModem() {
    modem.begin(EU868);
}

// Initialize sound function with Morse code for "BEE"
void initSound() {
    Serial.println("INITIALISATION... BEE");
    pinMode(BUZZER_PIN, OUTPUT);
    toggleBuzzer(dashDuration); delay(elementSpace); // Morse code for B
    toggleBuzzer(dotDuration); delay(elementSpace);
    toggleBuzzer(dotDuration); delay(elementSpace);
    toggleBuzzer(dotDuration); delay(letterSpace);
    toggleBuzzer(dotDuration); delay(letterSpace); // Morse code for E
    toggleBuzzer(dotDuration); // Morse code for E
}

void loop() {
    displayWeight();
    displayTemperatures();
    displayBatteryPercentage();
    handleLoRaConnection();
    // Uncomment to enable deep sleep mode
    //LowPower.deepSleep(120000);
}

void initSerial() {
    Serial.begin(115200);
    Serial.println("Carte MKRWAN n°11 connectée !\nTentative de connexion à l'application TTN...");
}

void initLoraConnection() {
    while (!connected) {
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
    //scale.tare();
    scale.set_scale(CALIBRATION_FACTOR);
    dht2.begin();
    dht3.begin();
}

void displayWeight() {
    float weight_units = scale.get_units(10);
    if (weight_units < 0) weight_units = 0.00;
    float ounces = weight_units * 0.035274;
    long weight_grams = (long)(ounces * 100);
    // Displaying the weight measured by the HX711 load cell
    Serial.println("Poids mesuré = " + String(weight_grams / 100.0) + " grammes");
}

void displayTemperatures() {
    // Requesting temperature readings from both DS18B20 sensors
    sensors.requestTemperatures();
    float ds18b20Temp1 = sensors.getTempCByIndex(0);
    float ds18b20Temp2 = sensors.getTempCByIndex(1);
    // Reading temperatures and humidity from DHT sensors
    short dht2Temp = short(dht2.readTemperature());
    short dht3Temp = short(dht3.readTemperature());
    short dht2Humidity = short(dht2.readHumidity());
    short dht3Humidity = short(dht3.readHumidity());
    // Displaying the temperature and humidity readings
    Serial.println("[INFO] Temperature DHT22 2 = " + String(dht2Temp) + " °C");
    Serial.println("[INFO] Temperature DHT22 3 = " + String(dht3Temp) + " °C");
    Serial.println("[INFO] Humidite DHT22 2 = " + String(dht2Humidity) + " %");
    Serial.println("[INFO] Humidite DHT22 3 = " + String(dht3Humidity) + " %");
    Serial.println("[INFO] Temperature DS18B20 (1) = " + String(short(ds18b20Temp1)) + " °C");
    Serial.println("[INFO] Temperature DS18B20 (2) = " + String(short(ds18b20Temp2)) + " °C");
}

void displayBatteryPercentage() {
    // Calculating and displaying the battery percentage
    float batteryPercentage = readBatteryPercentage();
    Serial.println("[INFO] Pourcentage de batterie = " + String(batteryPercentage) + " %");
}

void handleLoRaConnection() {
    // Handling the LoRa connection and sending data packets
    if (connected) {
        toggleBuzzer(1); // Buzzer signal for successful connection
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
    // Preparing and sending a data packet via LoRa
    sensors.requestTemperatures();
    float batteryPercentage = readBatteryPercentage();
    short batteryPercentageShort = static_cast<short>(batteryPercentage);
    short tempDS18B20_1 = (short)(sensors.getTempCByIndex(0) * 100);
    short tempDS18B20_2 = (short)(sensors.getTempCByIndex(1) * 100);
    short tempDHT22_2 = (short)(dht2.readTemperature() * 100);
    short tempDHT22_3 = (short)(dht3.readTemperature() * 100);
    short dht2Humidity = short(dht2.readHumidity() * 100);
    short dht3Humidity = short(dht3.readHumidity() * 100);
    int luminosityValue = analogRead(photoresistorPin);
    short shortLuminosityValue = (short)luminosityValue;
    float weight_units = scale.get_units(10);
    if (weight_units < 0) weight_units = 0.00;
    short ounces = (weight_units * 0.035274) / 10;
    // Sending all sensor data in a single LoRa packet
    modem.beginPacket();
    modem.write(shortLuminosityValue);
    modem.write((short)tempDS18B20_1);
    modem.write((short)tempDS18B20_2);
    modem.write((short)ounces);
    modem.write(dht2Humidity);
    modem.write(dht3Humidity);
    modem.write(tempDHT22_2);
    modem.write(tempDHT22_3);
    modem.write(batteryPercentageShort);
    return modem.endPacket();
}

void handleLoRaError(int err) {
    // Handling errors in LoRa communication
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
