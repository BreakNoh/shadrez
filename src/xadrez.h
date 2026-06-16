#ifndef XADREZ_H
#define XADREZ_H

#include <stdint.h>

#define TAMANHO_TABULEIRO 8

#define VAZIO 0
#define PEAO 1 
#define BISPO 2
#define CAVALO 3
#define TORRE 4
#define RAINHA 5
#define REI 6

#define FLAG_CAPTURA 1

#define FLAG_CHECK (1 << 1)
#define FLAG_CHECK_MATE (1 << 2)

#define FLAG_ROQUE_REI (1 << 3)
#define FLAG_ROQUE_RAINHA (1 << 4)

#define FLAG_EN_PASSANT (1 << 5)
#define FLAG_PROMO_BISPO (1 << 6)
#define FLAG_PROMO_CAVALO (1 << 7)
#define FLAG_PROMO_TORRE (1 << 8)
#define FLAG_PROMO_RAINHA (1 << 9)

typedef Peca uint8_t;

typedef struct Movimento {
	Peca peca;
	uint16_t flags;
	uint8_t x1;
	uint8_t y1;
	uint8_t x2;
	uint8_t y2;
} Movimento;
typedef struct Tabuleiro {
	Peca posicoes[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
	uint32_t turno;
} Tabuleiro;

int parsear_comando(char *comando)
bool movimento_valido(Tabuleiro *tab, char *mov);

#endif // !XADREZ_H
