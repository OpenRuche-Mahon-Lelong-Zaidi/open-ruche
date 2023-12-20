function decodeUplink(input) {
  var data = {};
  data.luminosity = (input.bytes[1] << 8 | (input.bytes[0]));
  data.temperatureDS18B20_1 = ((input.bytes[3] << 8 | (input.bytes[2])) / 100).toFixed(2);
  data.temperatureDS18B20_2 = ((input.bytes[5] << 8 | (input.bytes[4])) / 100).toFixed(2);
  data.weight = (input.bytes[7] << 8 | (input.bytes[6])) * 10;
  data.humidityDHT22_2 = (input.bytes[9] << 8 | (input.bytes[8]));
  data.humidityDHT22_3 = (input.bytes[11] << 8 | (input.bytes[10]));
  data.temperatureDHT22_2 = ((input.bytes[13] << 8 | (input.bytes[12]))/ 100).toFixed(2);
  data.temperatureDHT22_3 = ((input.bytes[15] << 8 | (input.bytes[14]))/ 100).toFixed(2);
  data.batteryPercentage = (input.bytes[17] << 8 | (input.bytes[16]));
  return {
    data: data,
    warnings: [],
    errors: []
  };
}
