# Pinos da ESP32-C6-DevKitM-1

A placa tem duas filas de pinos, J1 e J3. A ordem segue o [guia da Espressif](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitm-1/user_guide.html). Esta placa não tem os GPIO 10 e 11.

| N.º | J1 | Uso | J3 | Uso |
| --- | --- | --- | --- | --- |
| 1 | 3V3 | — | GND | GND dos sensores e LEDs |
| 2 | RST | — | TX (16) | Serial — não usar |
| 3 | 2 | ECHO ultrassom 2 | RX (17) | Serial — não usar |
| 4 | 3 | ECHO ultrassom 3 | 23 | LED vermelho |
| 5 | 4 | LED vermelho | 22 | LED verde |
| 6 | 5 | sinal do servo | 21 | LED verde |
| 7 | 0 | SIG do sensor de gás | 20 | LED verde |
| 8 | 1 | ECHO ultrassom 1 | 19 | LED verde |
| 9 | 8 | LED RGB da placa | 18 | TRIG ultrassom 4 |
| 10 | 6 | ECHO ultrassom 4 | 15 | LED vermelho |
| 11 | 7 | TRIG ultrassom 1 | 9 | botão BOOT — não usar |
| 12 | 14 | TRIG ultrassom 2 | GND | GND |
| 13 | GND | GND | 13 | TRIG ultrassom 3 |
| 14 | 5V | 5V dos sensores e do servo | 12 | LED vermelho |
| 15 | GND | GND | GND | GND |

## Por componente

| Componente | Ligações |
| --- | --- |
| Ultrassom 1 | TRIG → GPIO 7 · ECHO → divisor → GPIO 1 |
| Ultrassom 2 | TRIG → GPIO 14 · ECHO → divisor → GPIO 2 |
| Ultrassom 3 | TRIG → GPIO 13 · ECHO → divisor → GPIO 3 |
| Ultrassom 4 | TRIG → GPIO 18 · ECHO → divisor → GPIO 6 |
| LEDs verdes | GPIO 19, 20, 21, 22 → 220 Ω → LED → GND |
| LEDs vermelhos | GPIO 23, 4, 12, 15 → 220 Ω → LED → GND |
| Sensor de gás MQ-5 | VCC → 5V · GND → GND · SIG → divisor → GPIO 0 · NC sem ligação |
| Servo da cancela | sinal → GPIO 5 · VCC → 5V · GND → GND |

## Divisores de tensão

O sinal de 5 V liga à resistência de cima; a outra ponta vai ao pino da placa e à resistência de baixo, que vai ao GND.

| Sinal | De cima | De baixo |
| --- | --- | --- |
| ECHO dos ultrassons | 1 kΩ | 2 kΩ |
| SIG do MQ-5 | 10 kΩ | 20 kΩ |
