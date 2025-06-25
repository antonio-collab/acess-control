# 🔐 Controle de Acesso com RFID (RC522) e Raspberry Pi Pico

Este projeto implementa um sistema simples de controle de acesso utilizando o microcontrolador **Raspberry Pi Pico**, um leitor **RFID RC522** e tags RFID. O código foi escrito em **C/C++ utilizando o SDK oficial da Raspberry Pi**.

## 📦 Funcionalidades

- Leitura de tags RFID.
- Verificação de UID autorizado.
- Acionamento de relé (ou buzzer) para liberação de acesso.
- Mensagens exibidas no monitor serial para debug.

## 🛠️ Hardware Utilizado

- [x] Raspberry Pi Pico
- [x] Leitor RFID RC522 (interface SPI)
- [x] Tag RFID (UID de exemplo: `E1 A4 D8 51`)
- [x] Jumpers, protoboard
- [x] (Opcional) Relé ou Buzzer

## ⚙️ Conexões SPI (padrão do projeto)

| Componente | Pino no RC522 | GPIO no Pico |
|------------|----------------|--------------|
| SCK        | SCK            | GP18         |
| MOSI       | MOSI           | GP19         |
| MISO       | MISO           | GP16         |
| SDA (CS)   | SS             | GP17         |
| RST        | *não usado*    | *(fixado internamente)* |
| VCC        | VCC            | 3.3V         |
| GND        | GND            | GND          |

> 🔧 A biblioteca usada permite **não utilizar o pino RST**, facilitando a ligação.

## 📂 Estrutura do Projeto

