#ifndef XADREZ_H
#define XADREZ_H

#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define u8 uint8_t
#define i8 int8_t

#define sign(x) ((x > 0) ? 1 : (x < 0 ? -1 : 0))
#define MIN(a, b) ((a < b)? (a) : (b))

#define TAM_TABULEIRO 8

typedef enum { ENCONTRADA = 'e', NENHUMA = 'n' , AMBIGUO = 'a', NAO_RESOLVIDA = 'i' } Resolucao;
typedef enum {AVANCO, CAPTURA, ILEGAL} TipoJogada;

typedef enum {
	VAZIO = '[',
	PEAO = 'P',
	BISPO = 'B',
	CAVALO = 'C',
	TORRE = 'T',
	RAINHA = 'D',
	REI = 'R'
} Classe;

typedef enum {
	BRANCA = 'b',
	PRETA = 'p',
	INDEFINIDA = ']'
} Cor;

typedef struct {
	Classe classe;
	Cor cor;
} Peca;

typedef struct {
	i8 x1;
	i8 y1;
	i8 x2;
	i8 y2;
} Movimento;

typedef struct  {
	Peca posicoes[TAM_TABULEIRO][TAM_TABULEIRO];
	uint32_t turno;
	Cor jogador;
} Tabuleiro;

bool esta_dentro(i8 x, i8 y);
bool sao_mesma_peca(Peca a, Peca b);

Peca *raycast(Peca tab[8][8], Movimento mov, u8 *x, u8 *y);
bool validar_movimento(Peca tab[8][8], Movimento mov);

typedef struct {
    Peca peca;
	bool captura;
    struct {
        i8 x;
        i8 y;
    } alvo;
    struct {
        i8 x;
        i8 y;
    } origem;
	Resolucao res;
} Jogada;

Jogada parse_comando(char *cmd, Cor cor);
Resolucao resolver_jogada(Peca tab[8][8], Jogada *jog);

Tabuleiro new_tabuleiro();
void print_tab(Tabuleiro *tab, bool brancas_embaixo);
void mover_peca(Tabuleiro *tab, i8 x1, i8 y1, i8 x2, i8 y2);

#endif // !XADREZ_H
