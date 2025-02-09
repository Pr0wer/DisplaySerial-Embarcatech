#ifndef MATRIZNUMS
#define MATRIZNUMS

#include "matriz.h"

// Frames dos números 0 a 9 em caracteres digitais
static const uint8_t nums[10][MATRIZ_ROWS][MATRIZ_COLS] = 
{
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0}, // Algarismo 0
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
   {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 1, 0, 0}, // Algarismo 1
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0}
  },
  {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}, // Algarismo 2
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0}
  },
  {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}, // Algarismo 3
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}
  },
  {
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}, // Algarismo 4
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0}
  },
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0}, // Algarismo 5
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}
  },
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0}, // Algarismo 6
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}
  },
  {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0}, // Algarismo 7
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0}
  },
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}, // Algarismo 8
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}
  },
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0}, // Algarismo 9
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0}
  }
};

// Cor do digito na matriz (em RGB)
static const uint8_t red = 1;
static const uint8_t green = 0;
static const uint8_t blue = 0;

// Desenha o digito desejado na matriz de LED
void desenharDigito(char digito)
{   
    // Converter digito em string para inteiro
    uint8_t index = digito - '0';

    // Adicionar na matrix
    desenharFrame(nums[index], red, green, blue);
    atualizarMatriz();
}

#endif