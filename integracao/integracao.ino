#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Pino do LED (use um pino que suporte PWM - GPIO 2, 4, 5, 12-19, 21-23, 25-27, 32-33)
#define LED_PIN 5  

void setup() {
  Serial.begin(115200);
  
  // Inicializa I2C e sensor
  Wire.begin(21, 22);  // SDA = 21, SCL = 22
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Sensor BH1750 iniciado!");
  } else {
    Serial.println("Erro ao iniciar BH1750!");
  }

  // Configura o pino do LED como saída
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  

  delay(500);
}

void lux(){
  float lux = lightMeter.readLightLevel();

  Serial.print("Luminosidade: ");
  Serial.print(lux);
  Serial.println(" lx");

  // Converte lux (quanto mais escuro, mais brilho no LED)
  float luxLimitado = constrain(lux, 0, 30);

  // Converte 0–500 lux em 255–0 (inverso: menos luz → mais brilho)
  int brilho = map(luxLimitado, 0, 30, 255, 0);

  // Define o brilho PWM usando analogWrite
  analogWrite(LED_PIN, brilho);
}

void 