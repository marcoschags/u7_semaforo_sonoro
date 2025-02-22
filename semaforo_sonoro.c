#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"

#define LED_VERDE 11
#define LED_AMARELO 12
#define LED_VERMELHO 13
#define BUZZER 10
#define BOTAO_A 5

void configurar_gpio();
void emitir_som(uint frequency, uint duration);
void ciclo_semaforo();

int main() {
    configurar_gpio();
    
    while (true) {
        if (!gpio_get(BOTAO_A)) { // Botão pressionado
            ciclo_semaforo();
        }
        sleep_ms(100);
    }
}

void configurar_gpio() {
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);
    
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_put(LED_AMARELO, 0);
    
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0);
    
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    
    // Configurar PWM no buzzer
    gpio_set_function(BUZZER, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    pwm_set_enabled(slice_num, false);
}

void emitir_som(uint frequency, uint duration) {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER);
    uint clock_div = 4; // Define uma divisão do clock (ajustável)
    uint wrap = (125000000 / (clock_div * frequency)) - 1;
    
    pwm_set_clkdiv(slice_num, clock_div);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_gpio_level(BUZZER, wrap / 2); // 50% duty cycle
    pwm_set_enabled(slice_num, true);
    
    sleep_ms(duration);
    
    pwm_set_enabled(slice_num, false);
}

void ciclo_semaforo() {
    // Verde: Som baixo intermitente
    gpio_put(LED_VERDE, 1);
    for (int i = 0; i < 5; i++) {
        emitir_som(500, 300);
        sleep_ms(700);
    }
    gpio_put(LED_VERDE, 0);
    
    // Amarelo: Som médio pulsante
    gpio_put(LED_AMARELO, 1);
    for (int i = 0; i < 2; i++) {
        emitir_som(1000, 300);
        sleep_ms(700);
    }
    gpio_put(LED_AMARELO, 0);
    
    // Vermelho: Som alto contínuo
    gpio_put(LED_VERMELHO, 1);
    emitir_som(2000, 5000);
    gpio_put(LED_VERMELHO, 0);
}
