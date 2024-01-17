function decodeUplink(input) {
  var data = {};
  data.key = "3upgcl5ny1se8nva";
  data.l = (input.bytes[1] << 8 | input.bytes[0]);
  data.t_1 = decodeSignedTemperature(input.bytes[2], input.bytes[3]);
  data.t_2 = decodeSignedTemperature(input.bytes[4], input.bytes[5]);
  data.weight_kg = (((input.bytes[7] << 8 | input.bytes[6]) * 10)/ 1000).toFixed(2);
  data.h = ((input.bytes[9] << 8 | input.bytes[8]) / 100).toFixed(2);
  data.h_I = ((input.bytes[11] << 8 | input.bytes[10]) / 100).toFixed(2);
  data.t = decodeSignedTemperature(input.bytes[12], input.bytes[13]);
  data.t_0 = decodeSignedTemperature(input.bytes[14], input.bytes[15]);
  data.bv = ((input.bytes[17] << 8 | input.bytes[16]) / 100).toFixed(2);

  return {
    data: data,
    warnings: [],
    errors: []
  };
}

function decodeSignedTemperature(lowByte, highByte) {
  var temp = (highByte << 8) | lowByte;
  if (temp & 0x8000) {
    temp = temp - 0x10000;
  }
  return (temp / 100).toFixed(2);
}
