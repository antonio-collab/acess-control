# Controle de Acesso RFID com Raspberry Pi Pico

Este projeto implementa um sistema simples de controle de acesso por RFID utilizando o microcontrolador **Raspberry Pi Pico**, um leitor RFID **MFRC522**, LEDs indicadores e um buzzer.

---

## 🚀 Funcionalidades

- Leitura de tags RFID (UID)
- Verificação de UID autorizado
- LED verde para acesso permitido
- LED vermelho para acesso negado
- Buzzer PWM para feedback sonoro
- Sistema extensível para múltiplas tags

---

## 🧱 Hardware necessário

- Raspberry Pi Pico
- Leitor RFID RC522 (MFRC522)
- Módulo buzzer (ativo ou passivo)
- 2 LEDs (verde e vermelho)
- Resistores (para os LEDs, ~220Ω)
- Jumpers / protoboard

---

## 🔌 Conexões sugeridas

| Componente      | GPIO Pico | Descrição          |
|-----------------|------------|--------------------|
| MFRC522 - SDA   | GPIO 5     | SPI Chip Select    |
| MFRC522 - SCK   | GPIO 2     | SPI Clock          |
| MFRC522 - MOSI  | GPIO 3     | SPI MOSI           |
| MFRC522 - MISO  | GPIO 4     | SPI MISO           |
| MFRC522 - RST   | GPIO 6     | Reset              |
| LED Verde       | GPIO 11    | Acesso permitido   |
| LED Vermelho    | GPIO 13    | Acesso negado      |
| Buzzer          | GPIO 10    | PWM (som)          |

---

## 🧠 Como funciona

1. O sistema inicializa o leitor RFID e os periféricos.
2. Quando uma tag RFID é aproximada:
   - O UID é lido e comparado com uma lista autorizada.
   - Se o UID for autorizado:
     - O LED verde acende.
     - O buzzer emite dois bipes curtos.
   - Se não for autorizado:
     - O LED vermelho acende.
     - O buzzer emite um som longo.

---

## 🧾 UID Autorizado (padrão)

O código está configurado para aceitar apenas uma tag:

```c
uint8_t tag_autorizada[] = {0x34, 0xCC, 0xAA, 0x89};
