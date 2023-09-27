function decodeUplink(input) {
    var data = {};
    data.temperatureDHT11 = (input.bytes[1] << 8 | (input.bytes[0]));
    data.humidityDHT11 = (input.bytes[3] << 8 | (input.bytes[2]));
    data.temperatureDS18B20_1 = (input.bytes[5] << 8 | (input.bytes[4]));
    data.temperatureDS18B20_2 = (input.bytes[7] << 8 | (input.bytes[6]));
    return {
      data: data,
      warnings: [],
      errors: []
    };
 }