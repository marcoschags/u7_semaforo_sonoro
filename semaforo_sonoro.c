#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

// Definição dos pinos
#define LED_VERDE 11
#define LED_AMARELO 12
#define LED_VERMELHO 13
#define BUZZER 10
#define BOTAO_A 5

// Definição dos tempos de cada fase (em ms)
#define TEMPO_VERDE 5000
#define TEMPO_AMARELO 2000
#define TEMPO_VERMELHO 5000

// Função para emitir som no buzzer
void emitir_som(uint buzzer_pin, uint freq, uint duration) {
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.0);
    uint slice_num = pwm_gpio_to_slice_num(buzzer_pin);
    pwm_init(slice_num, &config, true);
    gpio_set_function(buzzer_pin, GPIO_FUNC_PWM);
    uint level = freq * 100; // Define o nível de PWM
    pwm_set_gpio_level(buzzer_pin, level);
    sleep_ms(duration);
    pwm_set_gpio_level(buzzer_pin, 0);
}

// Função para executar o ciclo do semáforo
void ciclo_semaforo() {
    // Verde - Som baixo e intermitente
    gpio_put(LED_VERDE, 1);
    for (int i = 0; i < 5; i++) {
        emitir_som(BUZZER, 500, 200);
        sleep_ms(300);
    }
    gpio_put(LED_VERDE, 0);
    sleep_ms(TEMPO_VERDE);

    // Amarelo - Som médio e pulsante
    gpio_put(LED_AMARELO, 1);
    for (int i = 0; i < 5; i++) {
        emitir_som(BUZZER, 1000, 100);
        sleep_ms(150);
    }
    gpio_put(LED_AMARELO, 0);
    sleep_ms(TEMPO_AMARELO);

    // Vermelho - Som alto e contínuo
    gpio_put(LED_VERMELHO, 1);
    emitir_som(BUZZER, 2000, TEMPO_VERMELHO);
    gpio_put(LED_VERMELHO, 0);
}

int main() {
    stdio_init_all();
    
    // Inicialização dos GPIOs
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    
    while (1) {
        if (gpio_get(BOTAO_A) == 0) { // Botão pressionado
            ciclo_semaforo();
        }
        sleep_ms(100);
    }
}
