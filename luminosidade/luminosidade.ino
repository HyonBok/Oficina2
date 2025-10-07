#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(115200); // Velocidade do monitor serial
  Wire.begin();         // Inicia comunicação I2C
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Sensor BH1750 iniciado com sucesso!");
  } else {
    Serial.println("Erro ao iniciar o sensor BH1750. Verifique conexões!");
  }
}

void loop() {
  float lux = lightMeter.readLightLevel(); // Lê o valor em lux
  Serial.print("Luminosidade: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000); // Lê a cada 1 segundo
}
