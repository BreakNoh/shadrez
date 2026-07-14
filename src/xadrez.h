#ifndef XADREZ_H
#define XADREZ_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define u8 uint8_t
#define i8 int8_t

#define sign(x) ((x > 0) ? 1 : (x < 0 ? -1 : 0))
#define MIN(a, b) ((a < b) ? (a) : (b))

#define TAM_TABULEIRO 8

typedef enum {
    ENCONTRADA = 'e',
    NENHUMA = 'n',
    AMBIGUO = 'a',
    NAO_RESOLVIDA = 'i'
} Resolucao;

typedef struct {
    i8 x1;
    i8 y1;
    i8 x2;
    i8 y2;
} Movimento;

// PECA
typedef enum {
    VAZIO = '[',
    PEAO = 'P',
    BISPO = 'B',
    CAVALO = 'C',
    TORRE = 'T',
    RAINHA = 'D',
    REI = 'R'
} Classe;
typedef enum { BRANCA = 'b', PRETA = 'p', INDEFINIDA = ']' } Cor;
typedef struct {
    Classe classe;
    Cor cor;
} Peca;

static Peca PECA_VAZIA = {VAZIO, INDEFINIDA};
static Movimento MOVIMENTO_VAZIO = {-1, -1, -1, -1};

Peca new_peca(Classe classe, Cor cor);
bool cmp_peca(Peca a, Peca b);
Peca parse_peca(char ch);

// TABULEIRO
typedef enum { ANDAMENTO, EM_CHECK, CHECK_MATE, EMPATE } EstadoTabuleiro;
typedef struct {
    Peca posicoes[TAM_TABULEIRO][TAM_TABULEIRO];
    Cor jogador_atual;

    EstadoTabuleiro estado;
    bool iniciadas[2][3];

    Movimento ultimo_movimento;
} Tabuleiro;
typedef char Leiaute[TAM_TABULEIRO + 1][TAM_TABULEIRO + 1];

static Leiaute LEIAUTE_PADRAO = {"TCBDRBCT", "PPPPPPPP", "-",       "-", "-",
                                 "-",        "pppppppp", "tcbdrbct"};

Tabuleiro new_tabuleiro(Leiaute leiaute);
void print_tab(Tabuleiro *tab, bool brancas_embaixo);
void mover_peca(Tabuleiro *tab, i8 x1, i8 y1, i8 x2, i8 y2);

bool cmp_pos(Tabuleiro *tab, i8 x, i8 y, Peca peca);
bool cmp_cor_pos(Tabuleiro *tab, i8 x, i8 y, Peca peca);
bool cmp_classe_pos(Tabuleiro *tab, i8 x, i8 y, Peca peca);

Peca *get_pos(Tabuleiro *tab, i8 x, i8 y);

// LOGICA
bool esta_dentro(i8 x, i8 y);
Peca *raycast(Peca tab[8][8], Movimento mov, u8 *x, u8 *y);
bool validar_movimento(Peca tab[8][8], Movimento mov);

typedef struct {
    Peca peca;
    bool captura;
    Movimento mov;
    Resolucao res;
} Jogada;

Jogada parse_comando(char *cmd, Cor cor, bool *sucesso);
Resolucao resolver_jogada(Tabuleiro *tab, Jogada *jog);
#endif // !XADREZ_H
