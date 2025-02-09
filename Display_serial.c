#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "WS2812B/matrizNums.h"
#include "Display/ssd1306.h"

// Pinos dos botões e LED RGB (Outros pinos se encontram nos arquivos .h!)
const uint btn_a_pin = 5;
const uint btn_b_pin = 6;
const uint led_green_pin = 11;
const uint led_blue_pin = 12;

// Display SSD1306
ssd1306_t ssd;

// Buffer para debounce
static volatile uint tempoAnterior = 0;

// Variáveis de estado
static volatile bool matrizOn = false;
static volatile bool ledGreenOn = false;
static volatile bool ledBlueOn = false;
static volatile bool novaInfo = true;

// Buffers de caracteres enviados pelo usuário definitivo e temporário, respectivamente
static volatile char recebido;
static volatile char c;


// Headers de funções
void inicializarPinos();
void handle_button(uint gpio, uint32_t events);
void menuDisplay();

int main()
{   
    // Inicialização de pinos e periféricos
    inicializarPinos();
    inicializarMatriz();
    ssd1306_i2c_init(&ssd);

    // Rotinas de interrupção
    gpio_set_irq_enabled_with_callback(btn_a_pin, GPIO_IRQ_EDGE_FALL, true, &handle_button);
    gpio_set_irq_enabled_with_callback(btn_b_pin, GPIO_IRQ_EDGE_FALL, true, &handle_button);

    stdio_init_all();

    while (true) 
    {   
        // Atualizar display apenas quando houver mudança na informação emitida
        if (novaInfo)
        {   
            // Exibir dados no display e atualizar status de informação
            menuDisplay();
            novaInfo = false;
        }


        // Obter caractere do usuário e emitir no display se válido
        c = getchar_timeout_us(100000);
        if (c != PICO_ERROR_TIMEOUT && (isalpha(c) || isdigit(c)))
        {   
            recebido = c;

            // Providenciar atualização do menu no display
            novaInfo = true;

            // Exibir, também, na matriz caso seja um digito
            if (isdigit(recebido))
            {   
                desenharDigito(recebido);
                matrizOn = true;
            }
            else if (matrizOn)
            {   
                // Desliga a matriz se caractere atual não for um número
                limparMatriz();
                matrizOn = false;
            }
        }
    }
}

// Inicializa os LEDs e botões do programa
void inicializarPinos()
{
    // Inicializar LEDs
    gpio_init(led_green_pin);
    gpio_set_dir(led_green_pin, GPIO_OUT);
    gpio_put(led_green_pin, 0);

    gpio_init(led_blue_pin);
    gpio_set_dir(led_blue_pin, GPIO_OUT);
    gpio_put(led_blue_pin, 0);

    // Inicializar botões
    gpio_init(btn_a_pin);
    gpio_set_dir(btn_a_pin, GPIO_IN);
    gpio_pull_up(btn_a_pin);

    gpio_init(btn_b_pin);
    gpio_set_dir(btn_b_pin, GPIO_IN);
    gpio_pull_up(btn_b_pin);
}

void handle_button(uint gpio, uint32_t events)
{
    // Tratar efeito bounce
    uint tempoAtual = to_us_since_boot(get_absolute_time());
    if (tempoAtual - tempoAnterior > 200000)
    {   
        tempoAnterior = tempoAtual;

        // Indicar que uma informação do display foi alterada
        novaInfo = true;

        if (gpio == btn_a_pin)
        {      
            // Alternar estado do LED verde
            ledGreenOn = !ledGreenOn;
            gpio_put(led_green_pin, ledGreenOn);

            printf("Botão A acionado -> LED verde ");
            if (ledGreenOn)
            {
                printf("LIGADO!\n");
            }
            else
            {
                printf("DESLIGADO!\n");
            }
        }
        else if (gpio == btn_b_pin)
        {   
            // Alternar estado do LED azul
            ledBlueOn = !ledBlueOn;
            gpio_put(led_blue_pin, ledBlueOn);

            printf("Botão B acionado -> LED azul ");
            if (ledBlueOn)
            {
                printf("LIGADO!\n");
            }
            else
            {
                printf("DESLIGADO!\n");
            }
        }
    }
}

// Exibe as informações principais no display
void menuDisplay()
{   
    // Limpar display
    ssd1306_fill(&ssd, false);

    // Escrever mensagem atualizada
    ssd1306_draw_string(&ssd, ledGreenOn ? "Luz verde LIGADA" : "Luz verde DESLIGADA", 5, 1);
    ssd1306_draw_string(&ssd, ledBlueOn ? "Luz azul  LIGADA" : "Luz azul  DESLIGADA", 5, 11);

    // Escrever caractere recebido
    ssd1306_draw_char(&ssd, recebido, 60, 21);

    // Atualizar display
    ssd1306_send_data(&ssd);
}