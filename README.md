# open-ruche

## Overview
"Open Ruche" is an academic university project at Polytech Sorbonne, focusing on developing an IoT system for real-time beehive monitoring. It aims to support beekeepers and environmental researchers with vital data on beehive conditions.

## Features
- Real-time monitoring of temperature, humidity, and weight inside the beehive.
- Efficient data transmission to a cloud server for analysis and storage.
- User-friendly interface for data visualization and alerts.

## Technical Details
- Utilizes Arduino-based sensors including DallasTemperature sensors for accurate temperature readings, DHT22 sensors for humidity, and HX711 for weight measurement.
- Incorporates a LoRa communication module (MKRWAN) for long-range, low-power data transmission.
- Includes a photoresistor for ambient light measurement, enhancing data context.
- Employs a solar-powered system, ensuring sustainable and continuous operation.

## Code Overview
- `sendSensorsData.ino` script handles sensor data collection and LoRa communication.
- Implements a power-efficient design with deep sleep capabilities and efficient LoRa data transmission.
- Features a Morse code buzzer system for initial diagnostics and connection status indication.

## Library Requirements for Open Ruche Project

### Sensor Libraries
- **DHT sensor library** - v1.4.0: For DHT22 temperature and humidity sensor
- **OneWire** - v2.3.5: For digital communication with temperature sensors
- **Dallas Temperature Control Library** - v3.9.0: For interfacing with Dallas temperature sensors
- **HX711 Arduino Library** - v0.7.4: For HX711 load cell interface

### Communication Libraries
- **MKRWAN** - v1.0.18: For LoRaWAN communication

### Power Management Libraries
- **ArduinoLowPower** - v1.2.2: For managing low power modes in Arduino

**Note:** These libraries can be installed via the Arduino Library Manager or downloaded directly from their respective GitHub repositories. Ensure to use the specified versions or later for compatibility.

## Acknowledgements
This is a collaborative effort by [@wolfyc](https://github.com/wolfyc), [@A-LELONG](https://github.com/A-LELONG), [@gregoiremahon](https://github.com/gregoiremahon), and Chahine BL.

## Contact
For more information or inquiries, please contact us.
