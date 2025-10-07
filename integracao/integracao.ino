#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Valores de calibração - AJUSTE ESTES VALORES!
const int DRY_VALUE = 4000;    // Valor no ar seco
const int WET_VALUE = 3000;    // Valor na água (precisa calibrar!)

const int LUX_VALUE = 85;

// Pino do LED (use um pino que suporte PWM - GPIO 2, 4, 5, 12-19, 21-23, 25-27, 32-33)
#define LUX_OUT_PIN 4  
#define SOIL_OUT_PIN 5
#define SOIL_PIN 34

void setup() {
  Serial.begin(115200);
  
  // Inicializa I2C e sensor
  Wire.begin(21, 22);  // SDA = 21, SCL = 22

  // Configura o pino do LED como saída
  pinMode(LUX_OUT_PIN, OUTPUT);
  pinMode(SOIL_OUT_PIN, OUTPUT);

  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
}

void loop() {
  lux();
  umidade();  

  delay(500);
}

void lux(){
  float lux = lightMeter.readLightLevel();

  Serial.print("Luminosidade: ");
  Serial.print(lux);
  Serial.println(" lx");

  // Converte lux (quanto mais escuro, mais brilho no LED)
  float luxLimitado = constrain(lux, 0, LUX_VALUE);

  // Converte 0–500 lux em 255–0 (inverso: menos luz → mais brilho)
  int brilho = map(luxLimitado, 0, LUX_VALUE, 255, 0);

  // Define o brilho PWM usando analogWrite
  analogWrite(LUX_OUT_PIN, brilho);
}

void umidade(){
  int value = analogRead(SOIL_PIN);
  
  // Mapeamento com calibração
  float humidity = map(value, DRY_VALUE, WET_VALUE, 0, 255);
  humidity = constrain(humidity, 0, 255);  // Limita entre 0% e 100%
  
  Serial.print("Valor bruto: ");
  Serial.print(value);
  Serial.print("  |  Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  analogWrite(SOIL_OUT_PIN, humidity);
}