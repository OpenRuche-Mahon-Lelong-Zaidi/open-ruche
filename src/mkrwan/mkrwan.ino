#include <MKRWAN.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LoRaModem modem;

String appEui = "1322144234234235";
String appKey = "A01DC8F9E363C86A883E41A6817427A5";

#define DHTPIN 4
#define DHTTYPE DHT11
#define ONE_WIRE_BUS_1 10
#define ONE_WIRE_BUS_2 9

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);
DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DHT dht(DHTPIN, DHTTYPE);

bool connected;
int err_count;
short con;

void setup() {
   Serial.begin(115200);
   sensors1.begin(); // Init DS18B20 temp sensor n1
   sensors2.begin(); // Init DS18B20 temp sensor n2
   while (!Serial);
   Serial.println("Carte MKRWAN n°11 connectée !\nTentative de connexion à l'application TTN...");
   modem.begin(EU868);
   dht.begin();
   delay(1000);      // apparently the murata dislike if this tempo is removed...
   connected=false;
   err_count=0;
   con =0;
}

void loop() {
   sensors1.requestTemperatures();
   sensors2.requestTemperatures();
   float ds18b20Temperature_1 = sensors1.getTempCByIndex(0);
   float ds18b20Temperature_2 = sensors2.getTempCByIndex(0);
   short dhtTemperature;
   short dhtHumidity;
   if ( !connected ) {
    Serial.print("Join test : ");
    Serial.println(++con);
    int ret=modem.joinOTAA(appEui, appKey);
    
    if ( ret ) {
      connected=true;
      modem.minPollInterval(60);
      Serial.println("Connected");
      modem.dataRate(5);   // switch to SF7
      delay(2000);          // because ... more stable -> 100
      err_count=0;
    }
  }

  if ( connected ) {
    int err=0;
    dhtTemperature = short(dht.readTemperature());
    dhtHumidity = short(dht.readHumidity());
    modem.beginPacket();
    Serial.println("Temperature DHT11 = " + String(dhtTemperature) +" °C");
    Serial.println("Humidite DHT11 = " + String(dhtHumidity) +" %");
    Serial.println("Temperature DS18B20 (1) = " + String(short(ds18b20Temperature_1)) + " °C");
    Serial.println("Temperature DS18B20 (2) = " + String(short(ds18b20Temperature_2)) + " °C");
    modem.write(dhtTemperature);
    modem.write(dhtHumidity);   
    modem.write((short)ds18b20Temperature_1);
    modem.write((short)ds18b20Temperature_2);
    err = modem.endPacket();
    
    if ( err <= 0 ) {
      Serial.print("Error : ");
      Serial.println(err);
      // Confirmation not received - jam or coverage fault
      err_count++;
      if ( err_count > 50 ) {
        connected = false;
      }
      // wait for 2min for duty cycle with SF12 - 1.5s frame
      for ( int i = 0 ; i < 120 ; i++ ) {
        delay(1000);
      }
    } else {
      err_count = 0;
      // wait for 20s for duty cycle with SF7 - 55ms frame
      delay(20000);
      Serial.println("Message envoyé");   
    }
  }
}
