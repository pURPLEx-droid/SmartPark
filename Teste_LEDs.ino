// Teste dos 8 LEDs (4 verdes e 4 vermelhos), numa ESP32-C6-DevKitM-1.
// Placa no Arduino IDE: "ESP32C6 Dev Module", com USB CDC On Boot > Disabled.
//
// 1. No arranque acende cada LED sozinho, um de cada vez, e escreve no
//    Serial Monitor qual e o pino, para confirmares cada ligacao.
// 2. Depois pisca os 8 LEDs todos juntos, meio segundo aceso e meio apagado.
//
// Ligacao de cada LED: GPIO -> resistencia de 220 ohm -> perna comprida (+);
// perna curta (-) -> GND.

const int NUM_LEDS = 4;

const int LED_VERDE[NUM_LEDS]    = {19, 20, 21, 22};
const int LED_VERMELHO[NUM_LEDS] = {23,  4, 12, 15};

const unsigned long TEMPO_CADA_LED_MS = 700;  // tempo aceso de cada LED no teste inicial
const unsigned long PISCAR_MS = 500;          // meio segundo aceso, meio apagado

void acenderUm(int pino, const char *cor, int numero) {
  Serial.printf("[LEDS] %s %d no GPIO %d\n", cor, numero, pino);
  digitalWrite(pino, HIGH);
  delay(TEMPO_CADA_LED_MS);
  digitalWrite(pino, LOW);
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== Teste dos LEDs ===");

  // Desliga o LED RGB integrado da placa (GPIO 8)
  rgbLedWrite(RGB_BUILTIN, 0, 0, 0);

  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_VERDE[i], OUTPUT);
    pinMode(LED_VERMELHO[i], OUTPUT);
  }

  // Um de cada vez
  for (int i = 0; i < NUM_LEDS; i++) acenderUm(LED_VERDE[i], "Verde", i + 1);
  for (int i = 0; i < NUM_LEDS; i++) acenderUm(LED_VERMELHO[i], "Vermelho", i + 1);

  Serial.println("[LEDS] Agora a piscar todos juntos");
}

void loop() {
  static bool aceso = false;
  aceso = !aceso;
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_VERDE[i], aceso ? HIGH : LOW);
    digitalWrite(LED_VERMELHO[i], aceso ? HIGH : LOW);
  }
  delay(PISCAR_MS);
}
