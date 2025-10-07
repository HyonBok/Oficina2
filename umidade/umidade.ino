#define SOIL_PIN 34

// Valores de calibração - AJUSTE ESTES VALORES!
const int DRY_VALUE = 4095;    // Valor no ar seco
const int WET_VALUE = 1500;    // Valor na água (precisa calibrar!)

void setup() {
  Serial.begin(115200);
  Serial.println("Sensor de umidade do solo - Versão Melhorada");
}

void loop() {
  int value = analogRead(SOIL_PIN);
  
  // Mapeamento com calibração
  float humidity = map(value, DRY_VALUE, WET_VALUE, 0, 100);
  humidity = constrain(humidity, 0, 100);  // Limita entre 0% e 100%
  
  Serial.print("Valor bruto: ");
  Serial.print(value);
  Serial.print("  |  Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");
  

  delay(2000);
}