Explicação das Funcionalidades Implementadas
Este código implementa um sistema de semáforo sonoro, acionado pelo botão A. Ele controla três LEDs e um buzzer para sinalizar diferentes estados:

Configuração do hardware (configurar_gpio)

Inicializa os LEDs (verde, amarelo e vermelho) como saídas.
Configura o botão A como entrada com pull-up ativado.
Configura o buzzer para utilizar PWM, permitindo a geração de sons com frequências variadas.
Geração de som (emitir_som)

Calcula e define os parâmetros do PWM para gerar um som na frequência desejada.
Ajusta o duty cycle para 50% e ativa o buzzer pelo tempo especificado.
Desativa o PWM ao final para evitar ruídos indesejados.
Ciclo do semáforo (ciclo_semaforo)

Ao pressionar o botão A, os LEDs acendem em sequência (verde, amarelo e vermelho).
O buzzer emite sons distintos para cada fase:
Verde: Som baixo intermitente.
Amarelo: Som médio pulsante.
Vermelho: Som alto contínuo.
Loop principal (main)

Monitora continuamente o botão A.
Quando pressionado, inicia o ciclo do semáforo.

Link do vídeo: https://www.youtube.com/watch?v=i1UzHlPstmo
