#include "xadrez.h"
#include <stdio.h>
#include <wchar.h>

const wchar_t COR_PECA_BRANCA[] = L"\u001b[1;39m";
const wchar_t COR_PECA_PRETA[] = L"\u001b[1;32m";

const wchar_t COR_FUNDO_BRANCA[] = L"\u001b[48;5;234m";
const wchar_t COR_FUNDO_PRETA[] = L"\u001b[40m";
const wchar_t LIMPAR_ESTILO[] = L"\u001b[0m";

const wchar_t *cor_fundo_pos(i8 x, i8 y) {
    return (x + y) % 2 == 1 ? COR_FUNDO_BRANCA : COR_FUNDO_PRETA;
}

wchar_t simbolo_peca(Peca p) {
    if (p.classe == VAZIO || p.cor == INDEFINIDA) {
        return L' ';
    }

    return (wchar_t)(p.classe);
}

const wchar_t *cor_peca(Peca p) {
    switch (p.cor) {
    case INDEFINIDA:
        return L"";
    case BRANCA:
        return COR_PECA_BRANCA;
    case PRETA:
        return COR_PECA_PRETA;
    }
}

void print_tab(Tabuleiro *tab, bool brancas_embaixo) {
    for (int i = 0; i < 8; i++) {
        if (brancas_embaixo) {
            printf("%d ", 8 - i);
        } else {
            printf("%d ", i + 1);
        }
        for (int j = 0; j < 8; j++) {
            Peca p;
            if (brancas_embaixo) {
                p = tab->posicoes[8 - 1 - i][j];
            } else {
                p = tab->posicoes[i][j];
            }

            printf("%ls%ls%lc %ls", cor_fundo_pos(i, j), cor_peca(p),
                   simbolo_peca(p), LIMPAR_ESTILO);
        }
        printf("\n");
    }
    printf("  A B C D E F G H\n");
}
