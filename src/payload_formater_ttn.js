function decodeUplink(input) {
  var data = {};
  data.luminosity = (input.bytes[1] << 8 | (input.bytes[0]));
  data.temperatureDS18B20_1 = (input.bytes[3] << 8 | (input.bytes[2]));
  data.temperatureDS18B20_2 = (input.bytes[5] << 8 | (input.bytes[4]));
  data.weight = (input.bytes[7] << 8 | (input.bytes[6])) * 10; // remultiplie
  data.humidityDHT11_2 = (input.bytes[9] << 8 | (input.bytes[8])); // Humidité capteur DHT 11 numero 2
  data.humidityDHT11_3 = (input.bytes[11] << 8 | (input.bytes[10])); // Humidité capteur DHT 22 numero 2
  data.temperatureDHT11_2 = (input.bytes[13] << 8 | (input.bytes[12])); // Temperature capteur DHT 11 numero 2
  data.temperatureDHT11_3 = (input.bytes[15] << 8 | (input.bytes[14])); // Temperature capteur DHT 22 numero 3
  return {
    data: data,
    warnings: [],
    errors: []
  };
}
