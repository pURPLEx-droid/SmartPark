# SmartPark

Projeto para a cadeira de Projeto 1.

Parque inteligente com uma ESP32-C6-DevKitM-1: ultrassons para detetar carros, um sensor de gás MQ-5, LEDs de sinalização e um LCD 16x2. O programa principal está em construção; por agora, cada peça tem o seu teste em `Testes/`.

## Estrutura

| Pasta | Conteúdo |
| --- | --- |
| `Projeto/` | programa principal (em construção) e documentação de montagem |
| `Projeto/hardware/` | pinos da placa e lista de material |
| `Testes/` | pequenos programas para testar uma peça de cada vez |

## Como carregar o código

1. Instala o [Arduino IDE 2](https://www.arduino.cc/en/software) e, no Boards Manager, o pacote **esp32** da Espressif.
2. Abre o `.ino` de um teste em `Testes/`.
3. Em **Tools**, escolhe:
   - **Board:** ESP32C6 Dev Module
   - **USB CDC On Boot:** Disabled
   - **Port:** a porta da placa (no Linux, `/dev/ttyUSB0`)
4. Liga o cabo à porta USB marcada **UART** da placa. A outra porta usa os GPIO 12 e 13, que o projeto ocupa.
5. Carrega em **Upload** e abre o **Serial Monitor** a **115200 baud**.

## Montagem

- [Pinos da placa](Projeto/hardware/pinos.md)
- [Lista de material](Projeto/hardware/material.md)

Os sinais de 5 V (ECHO dos ultrassons e SIG do MQ-5) passam por um divisor de tensão antes de chegarem à placa, que só aguenta 3,3 V.

## Testes

| Teste | O que faz | Bibliotecas |
| --- | --- | --- |
| [Teste_LEDs](Testes/Teste_LEDs/Teste_LEDs.ino) | acende cada um dos 8 LEDs à vez e depois pisca-os todos de meio em meio segundo | — |
| [Teste_Ultrassons](Testes/Teste_Ultrassons/Teste_Ultrassons.ino) | mostra a distância dos 4 HC-SR04 no Serial Monitor a cada 2 segundos | — |
| [Teste_Gas](Testes/Teste_Gas/Teste_Gas.ino) | mostra o valor e a tensão do MQ-5 no Serial Monitor a cada 2 segundos | — |
| [Teste_LCD](Testes/Teste_LCD/Teste_LCD.ino) | LCD 16x2 I2C (SDA 23, SCL 22): "Hello world" a passar sem parar | LiquidCrystal I2C (Frank de Brabander) |
