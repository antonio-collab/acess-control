
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mfrc522.h"
#include "hardware/pwm.h"

// Define o pino do relé (ou buzzer)
#define VERDE_PIN 11
#define VERMELHO_PIN 13
#define BUZZER_PIN 10

// UID da tag autorizada
uint8_t tag_autorizada[] = {0x34, 0xCC, 0xAA, 0x89};

void start_buzzer_pwm(int freq_hz, int duty_percent)
{
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125.0f); // 1 MHz
    pwm_config_set_wrap(&config, 1000000 / freq_hz);
    pwm_init(slice, &config, true);
    pwm_set_gpio_level(BUZZER_PIN, (1000000 / freq_hz) * duty_percent / 100);
}

void stop_buzzer_pwm()
{
    uint slice = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_set_gpio_level(BUZZER_PIN, 0);
    pwm_set_enabled(slice, false);
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_SIO);
    gpio_put(BUZZER_PIN, 0);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

int main()
{
    stdio_init_all();
    gpio_init(VERDE_PIN);
    gpio_set_dir(VERDE_PIN, GPIO_OUT);
    gpio_put(VERDE_PIN, 0);

     gpio_init(VERMELHO_PIN);
    gpio_set_dir(VERMELHO_PIN, GPIO_OUT);
    gpio_put(VERMELHO_PIN, 0);

    MFRC522Ptr_t mfrc = MFRC522_Init();
    PCD_Init(mfrc, spi0);

    printf("Controle de acesso RFID iniciado...\n");

    while (true)
    {
        if (PICC_IsNewCardPresent(mfrc) && PICC_ReadCardSerial(mfrc))
        {
            printf("UID detectado: ");
            for (int i = 0; i < mfrc->uid.size; i++)
            {
                printf("%02X ", mfrc->uid.uidByte[i]);
            }
            printf("\n");

            if (memcmp(mfrc->uid.uidByte, tag_autorizada, 4) == 0)
            {
                gpio_put(VERDE_PIN, 1);
                for (int i = 0; i < 2; i++)
                {
                    start_buzzer_pwm(1000, 50);
                    sleep_ms(200);
                    stop_buzzer_pwm();
                    sleep_ms(200);
                }
                gpio_put(VERDE_PIN, 0);
            }
            else
            {
                printf("Acesso negado.\n");
                gpio_put(VERMELHO_PIN, 1);
                sleep_ms(200);
                start_buzzer_pwm(1000, 50);
                sleep_ms(1000);
                stop_buzzer_pwm();
                gpio_put(VERMELHO_PIN, 0);
            }

            sleep_ms(1500); // Espera a tag ser removida
        }

        sleep_ms(100);
    }

    return 0;
}
