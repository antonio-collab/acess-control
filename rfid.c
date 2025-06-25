
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mfrc522.h"

// Define o pino do relé (ou buzzer)
#define RELE_PIN 10

// UID da tag autorizada
uint8_t tag_autorizada[] = {0xE1, 0xA4, 0xD8, 0x51};

int main() {
    stdio_init_all();
    gpio_init(RELE_PIN);
    gpio_set_dir(RELE_PIN, GPIO_OUT);
    gpio_put(RELE_PIN, 0);

    MFRC522Ptr_t mfrc = MFRC522_Init();
    PCD_Init(mfrc, spi0);

    printf("Controle de acesso RFID iniciado...\n");

    while (true) {
        if (PICC_IsNewCardPresent(mfrc) && PICC_ReadCardSerial(mfrc)) {
            printf("UID detectado: ");
            for (int i = 0; i < mfrc->uid.size; i++) {
                printf("%02X ", mfrc->uid.uidByte[i]);
            }
            printf("\n");

            if (memcmp(mfrc->uid.uidByte, tag_autorizada, 4) == 0) {
                printf("Acesso liberado!\n");
                gpio_put(RELE_PIN, 1);
                sleep_ms(3000); // libera por 3s
                gpio_put(RELE_PIN, 0);
            } else {
                printf("Acesso negado.\n");
            }

            sleep_ms(1500); // Espera a tag ser removida
        }

        sleep_ms(100);
    }

    return 0;
}
