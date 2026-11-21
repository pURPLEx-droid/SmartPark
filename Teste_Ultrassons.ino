// Teste dos 4 sensores ultrassom HC-SR04, numa ESP32-C6-DevKitM-1.
// Placa no Arduino IDE: "ESP32C6 Dev Module", com USB CDC On Boot > Disabled.
//
// Le os 4 sensores, um de cada vez, e mostra a distancia de cada um no
// Serial Monitor (115200 baud) a cada 2 segundos.
//
// Ligacoes de cada sensor:
//   VCC  -> 5V
//   GND  -> GND
//   TRIG -> GPIO (direto)
//   ECHO -> 1 kohm -> GPIO, com 2 kohm do GPIO ao GND (divisor de tensao:
//           o ECHO sai a 5 V e a placa so aguenta 3,3 V)

const int NUM_US = 4;

//                             US1 US2 US3 US4
const int TRIG_PINS[NUM_US] = { 7, 14, 13, 18};
const int ECHO_PINS[NUM_US] = { 1,  2,  3,  6};

const unsigned long INTERVALO_MS = 2000;  // tempo entre leituras

// Mede a distancia em cm. Devolve -1 se nao houver eco (fora de alcance ou mal ligado).
float lerDistanciaCm(int indice) {
  digitalWrite(TRIG_PINS[indice], LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PINS[indice], HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PINS[indice], LOW);

  unsigned long duracao = pulseIn(ECHO_PINS[indice], HIGH, 30000);  // ~5 m max
  if (duracao == 0) return -1;
  return duracao * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== Teste dos ultrassons ===");

  // Desliga o LED RGB integrado da placa (GPIO 8)
  rgbLedWrite(RGB_BUILTIN, 0, 0, 0);

  for (int i = 0; i < NUM_US; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < NUM_US; i++) {
    float cm = lerDistanciaCm(i);

    Serial.printf("[US%d] TRIG %d / ECHO %d: ", i + 1, TRIG_PINS[i], ECHO_PINS[i]);
    if (cm < 0) {
      Serial.println("sem eco");
    } else {
      Serial.print(cm, 1);
      Serial.println(" cm");
    }

    delay(30);  // deixa o eco anterior desaparecer antes do proximo sensor
  }
  Serial.println("--------------------------------");

  delay(INTERVALO_MS);
}
