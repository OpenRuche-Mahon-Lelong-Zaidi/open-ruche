function decodeUplink(input) {
  var data = {};
  data.key = "3upgcl5ny1se8nva";
  data.l = (input.bytes[1] << 8 | input.bytes[0]);
  data.t_1 = decodeTemperature(input.bytes[2], input.bytes[3]);
  data.t_2 = decodeTemperature(input.bytes[4], input.bytes[5]);
  data.weight_kg = (((input.bytes[7] << 8 | input.bytes[6]) * 10) / 1000).toFixed(2);
  data.h = ((input.bytes[9] << 8 | input.bytes[8]) / 100).toFixed(2); // exterieur
  data.h_I = ((input.bytes[11] << 8 | input.bytes[10]) / 100).toFixed(2); // interieur
  data.t = decodeTemperature(input.bytes[12], input.bytes[13]); // exterieur
  data.t_0 = decodeTemperature(input.bytes[14], input.bytes[15]); // interieur
  data.bv = ((input.bytes[17] << 8 | input.bytes[16]) / 100).toFixed(2);

  return {
      data: data,
      warnings: [],
      errors: []
  };
}

// Fonction pour décoder une température en tenant compte des valeurs signées
function decodeTemperature(byte1, byte2) {
  var temp = (byte2 << 8 | byte1);
  // Vérifie si la température est négative
  if (temp > 32767) {
      temp = temp - 65536;
  }
  return (temp / 100).toFixed(2);
}
