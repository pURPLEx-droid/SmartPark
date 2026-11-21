// Teste do sensor de gas MQ-5 (modulo com pinos VCC, GND, NC e SIG),
// numa ESP32-C6-DevKitM-1.
// Placa no Arduino IDE: "ESP32C6 Dev Module", com USB CDC On Boot > Disabled.
//
// Le o sinal do sensor a cada 2 segundos e mostra no Serial Monitor (115200 baud):
//   - o valor bruto (0 a 4095)
//   - a tensao no pino da placa
//   - a tensao a saida do sensor (antes do divisor)
//
// Ligacoes:
//   VCC -> 5V
//   GND -> GND
//   SIG -> 10 kohm -> GPIO 0, com 20 kohm do GPIO 0 ao GND (divisor de tensao)
//   NC  -> sem ligacao
//
// O MQ-5 aquece por dentro: espera alguns minutos depois de ligar antes de
// confiar nos valores (na primeira utilizacao, umas 24 horas).
// Para testar, aproxima um isqueiro SEM o acender e carrega no gas:
// o valor deve subir bastante.

const int GAS_PIN = 0;  // so os GPIO 0 a 6 leem valores analogicos na ESP32-C6

// Divisor de 10 k + 20 k: no pino fica 2/3 da tensao do sensor.
// Se testares sem divisor (VCC no 3V3 e SIG direto no pino), muda para 1.0.
const float FATOR_DIVISOR = 1.5;

const unsigned long INTERVALO_MS = 2000;  // tempo entre leituras

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== Teste do sensor de gas MQ-5 ===");

  // Desliga o LED RGB integrado da placa (GPIO 8)
  rgbLedWrite(RGB_BUILTIN, 0, 0, 0);

  analogReadResolution(12);  // valores de 0 a 4095
}

void loop() {
  int bruto = analogRead(GAS_PIN);
  float voltsPino = analogReadMilliVolts(GAS_PIN) / 1000.0;
  float voltsSensor = voltsPino * FATOR_DIVISOR;

  Serial.printf("[GAS] valor %4d / 4095 | pino %.2f V | sensor %.2f V\n",
                bruto, voltsPino, voltsSensor);

  delay(INTERVALO_MS);
}
