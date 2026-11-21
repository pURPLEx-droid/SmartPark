// Teste do display LCD 16x2 com modulo I2C (PCF8574), numa ESP32-C6-DevKitM-1.
// Placa no Arduino IDE: "ESP32C6 Dev Module", com USB CDC On Boot > Disabled.
// Biblioteca: "LiquidCrystal I2C" de Frank de Brabander (Library Manager).
//
// A frase "Hello world" passa da direita para a esquerda na linha de cima,
// sem parar.
//
// Ligacoes do modulo I2C:
//   GND -> GND
//   VCC -> 5V
//   SDA -> GPIO 23
//   SCL -> GPIO 22
// Se nao aparecer texto, roda o potenciometro azul atras do modulo (contraste).

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int SDA_PIN = 23;
const int SCL_PIN = 22;

const char FRASE[] = "Hello world";
const int COLUNAS = 16;
const int LINHAS = 2;

const unsigned long PASSO_MS = 300;  // velocidade da passagem (uma coluna por passo)

LiquidCrystal_I2C *lcd = nullptr;

// Procura o endereco do modulo I2C (normalmente 0x27 ou 0x3F).
uint8_t procurarEndereco() {
  for (uint8_t endereco = 1; endereco < 127; endereco++) {
    Wire.beginTransmission(endereco);
    if (Wire.endTransmission() == 0) return endereco;
  }
  return 0;
}

// Escreve a frase na linha de cima, a comecar na coluna "posicao"
// (pode ser negativa ou maior que 15: a parte fora do ecra nao aparece).
void desenharFrase(int posicao) {
  char linha[COLUNAS + 1];
  int tamanho = strlen(FRASE);
  for (int coluna = 0; coluna < COLUNAS; coluna++) {
    int indice = coluna - posicao;
    linha[coluna] = (indice >= 0 && indice < tamanho) ? FRASE[indice] : ' ';
  }
  linha[COLUNAS] = '\0';
  lcd->setCursor(0, 0);
  lcd->print(linha);
}

// Inicializa (ou reinicializa) o LCD. Se uma interferencia baralhar o LCD
// e ele comecar a mostrar simbolos estranhos, isto volta a po-lo em ordem.
void iniciarLcd() {
  lcd->init();
  lcd->backlight();
  lcd->clear();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("=== Teste do LCD 16x2 ===");

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(50000);  // I2C mais lento: mais tolerante a fios compridos e ruido

  uint8_t endereco = procurarEndereco();
  if (endereco == 0) {
    Serial.println("[LCD] Nenhum modulo I2C encontrado. Verifica SDA, SCL, VCC e GND.");
    while (true) delay(1000);
  }
  Serial.printf("[LCD] Modulo encontrado no endereco 0x%02X\n", endereco);

  lcd = new LiquidCrystal_I2C(endereco, COLUNAS, LINHAS);
  iniciarLcd();
}

void loop() {
  static int posicao = COLUNAS;  // comeca fora do ecra, a direita
  static unsigned long ultimoPasso = 0;
  unsigned long agora = millis();

  // Passagem: avanca uma coluna para a esquerda e volta ao inicio no fim
  if (agora - ultimoPasso >= PASSO_MS) {
    ultimoPasso = agora;
    desenharFrase(posicao);
    posicao--;
    if (posicao < -(int)strlen(FRASE)) {
      posicao = COLUNAS;
      // A frase saiu do ecra (que esta vazio): reinicia o LCD sem se notar,
      // para recuperar se uma interferencia o tiver baralhado.
      iniciarLcd();
    }
  }
}
