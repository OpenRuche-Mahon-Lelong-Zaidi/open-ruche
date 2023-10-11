#include <MKRWAN.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HX711.h>

LoRaModem modem;

String appEui = "1322144234234235";
String appKey = "A01DC8F9E363C86A883E41A6817427A5";

int DHT_PIN = 4;
int DHT_TYPE = DHT11;
int ONE_WIRE_BUS_1 = 10;
int ONE_WIRE_BUS_2 = 9;
int DOUT_PIN = 13;
int CLK_PIN = 14;

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);
DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DHT dht(DHT_PIN, DHT_TYPE);
HX711 scale;

bool connected = false;
int err_count = 0;
short con = 0;
const float CALIBRATION_FACTOR = 1.045;

void setup() {
    initSerial();
    initSensors();
    initModem();
}

void loop() {
    displayWeight();
    displayTemperatures();
    handleLoRaConnection();
}

void initSerial() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("Carte MKRWAN n°11 connectée !\nTentative de connexion à l'application TTN...");
}

void initSensors() {
    sensors1.begin();
    sensors2.begin();
    scale.begin(DOUT_PIN, CLK_PIN);
    scale.set_scale();
    scale.tare();
    scale.set_scale(CALIBRATION_FACTOR);
    dht.begin();
}

void initModem() {
    modem.begin(EU868);
    delay(1000);
}

void displayWeight() {
    Serial.print("[INFO] ");
    float weight_units = scale.get_units(10);
    if (weight_units < 0) weight_units = 0.00;
    long weight_grams = (long)(weight_units * 10); // Precision de 100g
    Serial.println("Poids mesuré = " + String(weight_grams) + " grammes x 100 (en float : " + String(weight_units) + " g).");
}

void displayTemperatures() {
    sensors1.requestTemperatures();
    sensors2.requestTemperatures();
    float ds18b20Temp1 = sensors1.getTempCByIndex(0);
    float ds18b20Temp2 = sensors2.getTempCByIndex(0);
    short dhtTemp = short(dht.readTemperature());
    short dhtHumidity = short(dht.readHumidity());
    Serial.println("[INFO] Temperature DHT11 = " + String(dhtTemp) + " °C");
    Serial.println("[INFO] Humidite DHT11 = " + String(dhtHumidity) + " %");
    Serial.println("[INFO] Temperature DS18B20 (1) = " + String(short(ds18b20Temp1)) + " °C");
    Serial.println("[INFO] Temperature DS18B20 (2) = " + String(short(ds18b20Temp2)) + " °C");
}

void handleLoRaConnection() {
    if (!connected) {
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
    float ds18b20Temp1 = sensors1.getTempCByIndex(0);
    float ds18b20Temp2 = sensors2.getTempCByIndex(0);
    short dhtTemp = short(dht.readTemperature());
    short dhtHumidity = short(dht.readHumidity());
    float weight_units = scale.get_units(10);
    if (weight_units < 0) weight_units = 0.00;
    long weight_grams = (long)(weight_units * 10); // 100g precision
    modem.beginPacket();
    modem.write(dhtTemp);
    modem.write(dhtHumidity);
    modem.write((short)ds18b20Temp1);
    modem.write((short)ds18b20Temp2);
    modem.write((weight_grams >> 24) & 0xFF);   // octet le plus significatif
    modem.write((weight_grams >> 16) & 0xFF);   // deuxième octet le plus significatif
    modem.write((weight_grams >> 8) & 0xFF);    // troisième octet le plus significatif
    modem.write(weight_grams & 0xFF);           // octet le moins significatif
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
