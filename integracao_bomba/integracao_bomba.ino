#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Valores de calibração - AJUSTE ESTES VALORES!
const int DRY_VALUE = 4000;    // Valor no ar seco
const int WET_VALUE = 3000;    // Valor na água (precisa calibrar!)

const int LUX_VALUE = 200;

// Pino do LED (use um pino que suporte PWM - GPIO 2, 4, 5, 12-19, 21-23, 25-27, 32-33)
#define PUMP_OUT_PIN 23  
#define SOIL_IN_PIN 34

void setup() {
  Serial.begin(115200);
  
  // Inicializa I2C e sensor
  Wire.begin(21, 22);  // SDA = 21, SCL = 22

  // Configura o pino da bomb como saída
  pinMode(PUMP_OUT_PIN, OUTPUT);

  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
}

void loop() {
  int luz = lux();
  int umid = umidade();  


  if(luz > 50){
    digitalWrite(PUMP_OUT_PIN, HIGH);
    Serial.println("Bomba ligada");
  }
  else{
    digitalWrite(PUMP_OUT_PIN, LOW);
    Serial.println("Bomba desligada");
  }

  delay(1000);
}

int lux(){
  float lux = lightMeter.readLightLevel();

  Serial.print("Luminosidade: ");
  Serial.print(lux);
  Serial.print(" lx ");

  float luxLimitado = constrain(lux, 0, LUX_VALUE);
  int brilho = map(luxLimitado, 0, LUX_VALUE, 0, 100);

  Serial.print(brilho);
  Serial.println("%");

  return brilho;
}

int umidade(){
  int value = analogRead(SOIL_IN_PIN);
  
  // Mapeamento com calibração
  float humidity = map(value, DRY_VALUE, WET_VALUE, 0, 100);
  humidity = constrain(humidity, 0, 100);  // Limita entre 0% e 100%
  
  Serial.print("Valor bruto: ");
  Serial.print(value);
  Serial.print("  |  Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  return humidity;
}