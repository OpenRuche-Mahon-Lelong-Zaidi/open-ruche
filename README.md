# Open Ruche Project Guide

## Project Overview

The Open Ruche project represents an ambitious academic undertaking conducted at Polytech Sorbonne, specifically within the EI2I program during the 4th year of study. This multidisciplinary initiative at the intersection of technology, environmental science, and sustainability is dedicated to the development of a sophisticated IoT (Internet of Things) system meticulously designed for real-time monitoring of beehives.

### Mission and Significance

At its core, Open Ruche is on a mission to address the critical need for comprehensive and real-time beehive monitoring solutions. The world's honeybee populations are facing a multitude of challenges, including climate change, habitat loss, pesticide exposure, and diseases. The consequences of declining bee populations are profound, as they serve as vital pollinators for a significant portion of global crops. Open Ruche's primary goal is to contribute significantly to the well-being of bee colonies and, by extension, to global food security.

### IoT Innovation

Open Ruche leverages cutting-edge IoT technology, combining hardware and software expertise to create a state-of-the-art monitoring system. The project's key innovation lies in its ability to provide real-time data on beehive conditions. This includes critical parameters such as temperature, humidity, hive weight, and light exposure. Such granular data is essential for beekeepers to make informed decisions about hive management, anticipate potential issues, and ensure the health and productivity of their bee colonies.

### Bridging the Gap

A core objective of Open Ruche is to bridge the gap between the beekeeping community and environmental researchers. By providing accessible and accurate hive data, the project enables collaboration between these two vital stakeholders. Beekeepers gain valuable insights into the conditions of their hives, allowing for more precise and timely interventions. Environmental researchers, on the other hand, can access a wealth of data to study the impact of environmental factors on bee health.

### Sustainability Commitment

Open Ruche is not just about technology; it's also a testament to sustainability and responsible environmental stewardship. The project embraces a sustainable approach by incorporating renewable energy sources, such as solar panels, to power the monitoring system. This ensures continuous and eco-friendly operation, aligning with the broader goal of promoting sustainable practices in agriculture and environmental monitoring.

In summary, Open Ruche is more than a project; it's a commitment to safeguarding bee populations, fostering collaboration, and advancing the frontiers of IoT technology. It stands as a shining example of how academia, technology, and environmental consciousness can come together to address critical global challenges.

## Hardware Details

### 1. MKRWAN Board
- The MKRWAN board serves as the core of the monitoring system. It is an Arduino-compatible board specifically designed for LoRaWAN communication, making it an ideal choice for IoT applications. Its compact size and low power consumption are well-suited for remote beehive monitoring.

### 2. DHT22 Temperature and Humidity Sensors
- The DHT22 sensors were carefully chosen for their high accuracy in measuring both temperature and humidity levels inside beehives. These parameters are critical for monitoring bee health and hive conditions.
- The sensors utilize a single-wire digital interface, ensuring reliable and consistent readings even in challenging environments.

### 3. OneWire Protocol Compatible Temperature Sensors (e.g., DS18B20)
- OneWire-compatible temperature sensors, such as the DS18B20, are employed to provide precise temperature readings for external conditions around the hive. These sensors are essential for understanding the ambient environment that the bees are exposed to.
- They utilize the efficient OneWire protocol for digital communication, making them reliable and easy to integrate into the system.

### 5. H401-C3 Load Cell (Connected to HX711 Amplifier)
- The H401-C3 load cell is a crucial component used for precise weight monitoring of the beehive. This load cell is specifically designed for applications that require accurate and reliable weight measurements.
- It offers high precision and stability, making it ideal for assessing hive growth and bee activity.
- The H401-C3 load cell is known for its durability and resistance to environmental factors, ensuring long-term performance even in challenging conditions. It is connected to the HX711 amplifier for signal processing.

### 6. HX711 Load Cell Amplifier
- The HX711 load cell amplifier is a critical component used to monitor the hive's weight. Tracking the weight of the hive is essential for assessing hive growth and bee activity.
- This amplifier features low-noise analog-to-digital conversion, ensuring accurate and consistent weight measurements.

### 7. Photoresistor
- A photoresistor is integrated into the system to measure ambient light conditions surrounding the beehive. Understanding the external light environment provides valuable context to the data collected by the sensors.
- The photoresistor assists in assessing the influence of light on bee behavior and hive activity.

### 8. Buzzer
- A buzzer is included in the system to provide audible feedback and notifications. It enhances the user interaction with the monitoring system.
- The buzzer can generate sounds for various purposes, including diagnostics, connection status indication, and alerting beekeepers to specific events or conditions.

### 9. Battery (with TPL5110 for Power Management)
- The monitoring system is powered by a rechargeable LiPo battery, ensuring autonomy and continuous operation. The choice of a LiPo battery reflects the project's commitment to sustainability and energy efficiency.
- To efficiently manage power consumption and extend battery life, the TPL5110 power management module is employed. It ensures that the system operates only when necessary, conserving energy and prolonging battery life.

### Power Supply Considerations

#### LiPo Battery and Solar Panels Integration

The Open Ruche monitoring system relies on a carefully designed power supply system to ensure continuous operation. Here are the key components and considerations:

##### 1. LiPo Battery
- The system is powered by a rechargeable LiPo (Lithium-Polymer) battery with a nominal voltage of 3.7V and a maximum voltage of approximately 4.2V.
- The LiPo battery is selected for its energy density and rechargeable nature, making it an excellent choice for remote IoT applications like beehive monitoring.
- The battery's capacity is rated at 1050mAh, providing sufficient energy for extended operation.

##### 2. LiPo Rider Pro Charging Circuit
- To efficiently manage the LiPo battery's charging and ensure its longevity, the system incorporates the LiPo Rider Pro charging circuit.
- The LiPo Rider Pro is responsible for safely recharging the LiPo battery. It regulates the voltage from the connected solar panel to charge the battery effectively.
- This charging circuit includes safeguards to prevent overcharging and over-discharging, prolonging the LiPo battery's lifespan.

##### 3. Solar Panels
- Solar panels with dimensions of approximately 18cm by 8cm are integrated into the Open Ruche system to harness solar energy.
- These solar panels serve as a renewable power source, continuously recharging the LiPo battery during daylight hours.
- The energy harvested from the solar panels helps maintain the battery's charge and sustain the system's operation even in locations with limited access to traditional power sources.

##### 4. Power Consumption
- The system is designed with power-efficient components and sleep modes to minimize power consumption.
- Expected power consumption is carefully managed to ensure the system's autonomy and reduce the need for frequent battery recharging.
- Power management modules, such as the TPL5110, are utilized to control power states and optimize energy usage.

The integration of a LiPo battery and solar panels in the Open Ruche project provides a sustainable power solution for remote beehive monitoring. This setup ensures that the system can operate autonomously, continuously collect data, and contribute to the well-being of bee colonies.

These carefully selected components collectively enable the Open Ruche project to collect data effectively, ensuring the well-being of bee colonies and addressing the challenges faced by beekeepers in a sustainable and responsible manner.


### PCB Schematic
In this section, we provide an overview of the PCB schematic designed for the Open Ruche project. The PCB serves as a central component, featuring connectors for the MKRWAN 1310, interfaces for various sensors, and integration with the TPL5110 for efficient power management.

#### Key Features:
- **MKRWAN 1310 Interface:** The PCB includes a dedicated interface for seamless connection with the MKRWAN 1310 board. This interface ensures compatibility and efficient data transmission.

- **Sensor Connections:** Multiple sensors are accommodated through the PCB, allowing for the collection of crucial data. Detailed interfaces for each sensor type are provided on the PCB, enabling accurate measurements.

- **TPL5110 Integration:** To enhance power management and optimize energy consumption, the PCB integrates the TPL5110 module. This feature contributes to the project's low-power operation.

#### PCB Schematic Image
![Open Ruche PCB Schematic](pcb_schematic.png)

The image above displays the actual PCB schematic, providing a visual representation of the board's layout, connectors, and sensor interfaces.

Including this schematic image helps users gain a better understanding of the physical configuration of the PCB, facilitating the replication of the Open Ruche project.


## Software Requirements

### 1. Arduino IDE
- We recommend using the Arduino IDE for programming the MKRWAN board and integrating the required libraries.

### 2. LoRaWAN Connectivity Setup
- Configure LoRaWAN connectivity using your chosen network provider (e.g., The Things Network - TTN).

## Setup Instructions

### 1. Assemble the Hardware
- Connect the sensors and components following the provided wiring diagram.

### 2. Configure the Arduino IDE
- Install necessary libraries for DHT, OneWire, DallasTemperature, HX711, and ArduinoLowPower.
- Set up the Arduino IDE for your MKRWAN board.

### 3. Configure LoRaWAN
- Obtain unique Application EUI and Application Key credentials from your LoRaWAN network provider (e.g., TTN).
- Update the `appEui` and `appKey` variables in the Arduino code with these credentials.

### 4. Sensor Calibration

#### Weight Sensor Calibration

The weight sensor used in the Open Ruche project, the H401-C3, requires calibration to provide accurate weight measurements. The calibration process involves determining the correct calibration factor that converts sensor readings into meaningful weight values.

Here are the steps to calibrate the weight sensor:

1. **Select a Reference Weight:** Begin by selecting a known reference weight. This weight should be accurately measured and preferably falls within the typical range of beehive weights you intend to monitor. Ensure that the reference weight is evenly distributed on the hive's weight-sensing platform.

2. **Place the Reference Weight:** Carefully place the reference weight on the hive's weight-sensing platform, ensuring it is centered and balanced. This step should be performed with precision to obtain accurate calibration.

3. **Record Sensor Reading:** Record the sensor reading corresponding to the applied reference weight. The sensor will provide a reading in a raw unit, which is not directly interpretable as weight.

4. **Calculate Calibration Factor:** To calculate the calibration factor, divide the known reference weight (in grams or kilograms) by the recorded sensor reading (in raw units). The formula is as follows:
   
   Calibration Factor = Reference Weight (grams or kilograms) / Sensor Reading (raw units)

   For example, if the reference weight is 1095 grams and the sensor reading is 1000 raw units, the calibration factor would be:
   
   Calibration Factor = 1095 grams / 1000 raw units = 1.095 grams/raw unit

5. **Apply Calibration Factor:** Once you have calculated the calibration factor, you can apply it to the sensor readings to convert raw units into weight values. Multiply the sensor readings by the calibration factor to obtain accurate weight measurements.

By following these steps, you can calibrate the weight sensor in the Open Ruche project to provide precise and reliable weight measurements of beehives. Calibration ensures that the system accurately monitors hive growth and provides valuable data to beekeepers.


### 5. Upload the Code
- Open the Arduino sketch provided in the project repository.
- Upload the code to your MKRWAN board.

### 6. Power Up the System
- Use a battery as the power source and the TPL5110 for efficient power management.

## Testing

### 1. Data Monitoring
- Monitor the data transmitted by your device via LoRaWAN on your chosen network provider's platform (for example, we used TTN Console for this project).
- Verify temperature, humidity, weight, light, and battery voltage data.

### 2. Troubleshooting
- Refer to the troubleshooting section in the project documentation for guidance on resolving any issues.

## Programming

The Open Ruche project is powered by an Arduino MKRWAN 1310 board, and its functionality is achieved through a combination of libraries and custom code. Below, we provide an overview of the code structure, libraries used, and how data is transmitted to the Things Network (TTN) and integrated with the Beep app API.

### Code Overview

You can find the code in the [src](https://github.com/OpenRuche-Mahon-Lelong-Zaidi/open-ruche/tree/main/src) folder.


The project's Arduino code [sendSensorsData.ino](https://github.com/OpenRuche-Mahon-Lelong-Zaidi/open-ruche/blob/main/src/arduino/sendSensorsData/sendSensorsData.ino) is organized into several sections, each responsible for specific tasks:

- **Initialization:** This section includes the setup of pins, sensors, and LoRa communication. It also initializes the modem and sets up Morse code signaling for system startup.

- **Sensor Initialization:** Here, the various sensors used in the project, such as DHT temperature and humidity sensors, DS18B20 temperature sensors, and the HX711 weight sensor, are initialized.

- **Main Loop:** The main loop of the program handles the core functionality. It includes functions to read sensor data, handle LoRa communication, and signal task completion. The system also enters a low-power sleep mode to conserve energy between data transmissions.

- **Display Functions:** These functions are used for debugging and can be uncommented to display sensor readings and battery percentage in the Serial Monitor.

- **LoRa Communication:** This section handles LoRa communication, including joining the TTN network and sending data packets.

### Libraries and Dependencies

The project relies on the following libraries and dependencies:

- `MKRWAN`: This library provides LoRaWAN communication capabilities for the Arduino MKRWAN board.

- `DHT`: The DHT library is used for reading temperature and humidity data from DHT22 sensors.

- `OneWire` and `DallasTemperature`: These libraries are employed for interfacing with DS18B20 temperature sensors using the OneWire protocol.

- `HX711`: The HX711 library allows communication with the HX711 weight sensor, used for hive weight monitoring.

- `ArduinoLowPower`: This library provides functions for managing low-power modes to extend battery life.

### Payload Formatter (TTN)

The payload formatter, an essential component in the TTN (The Things Network) console, plays a crucial role in the OpenRuche project. It is responsible for decoding the raw data received from the MKRWAN board, transforming it into human-readable information, and preparing it for further processing.

**Importance:**
- **Data Decoding:** The payload formatter is instrumental in translating the binary data transmitted by the MKRWAN board into a structured format that can be easily interpreted. This is crucial for understanding the sensor readings and other data points collected by the monitoring system.

- **Signed Temperature Values:** One noteworthy feature of the payload formatter is its ability to handle signed temperature values. This is essential for accurately representing both positive and negative temperatures, making it versatile for various environmental conditions.

- **Data Structure:** The payload formatter structures the data into meaningful data points, including temperature readings, weight measurements, humidity levels, battery voltage, and more. These structured data points are vital for monitoring the health and conditions of beehives.

- **Data Integration:** Once decoded and structured, the data can be seamlessly integrated into the OpenRuche system, allowing beekeepers and researchers to access real-time hive information through the Beep API.

**Operation:**
- The payload formatter operates using JavaScript code, which is executed within the TTN console.

- It extracts the relevant bytes from the received data and processes them to form meaningful variables.

- The `decodeSignedTemperature` function is used to handle signed temperature values, ensuring accurate representation.

- The formatted data is then made available for further analysis and integration with the Beep application.

The payload formatter's code can be found at [this link](https://github.com/OpenRuche-Mahon-Lelong-Zaidi/open-ruche/blob/main/src/payload_formater_ttn.js).

### Data Transmission and visualization

Data is transmitted from the MKRWAN board to TTN, where it is decoded using the payload formatter. TTN then sends the data to the Beep API through a webhook. The [Beep-API](app.beep.nl) allows the visualization and analysis of data from multiple beehives.

## Acknowledgements
This project is a collaborative effort by students at Polytech Sorbonne: [@wolfyc](https://github.com/wolfyc), [@A-LELONG](https://github.com/A-LELONG), [@gregoiremahon](https://github.com/gregoiremahon), and Chahine Boukhenaissi.

## Contact
For more information or inquiries, please contact us.
