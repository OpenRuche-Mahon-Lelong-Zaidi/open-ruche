function decodeUplink(input) {
  var data = {};
  data.temperatureDHT11 = (input.bytes[1] << 8 | (input.bytes[0]));
  data.humidityDHT11 = (input.bytes[3] << 8 | (input.bytes[2]));
  data.temperatureDS18B20_1 = (input.bytes[5] << 8 | (input.bytes[4]));
  data.temperatureDS18B20_2 = (input.bytes[7] << 8 | (input.bytes[6]));
  data.weight = (input.bytes[9] << 8 | (input.bytes[8])) * 10; // remultiplie
  data.humidityDHT11_2 = (input.bytes[11] << 8 | (input.bytes[10])); // Humidité capteur DHT 11 numero 2
  data.humidityDHT11_3 = (input.bytes[13] << 8 | (input.bytes[12])); // Humidité capteur DHT 22 numero 2
  data.temperatureDHT11_2 = (input.bytes[15] << 8 | (input.bytes[14])); // Temperature capteur DHT 11 numero 2
  data.temperatureDHT11_3 = (input.bytes[17] << 8 | (input.bytes[16])); // Temperature capteur DHT 22 numero 3
  return {
    data: data,
    warnings: [],
    errors: []
  };
}
