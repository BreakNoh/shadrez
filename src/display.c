#include "xadrez.h"

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
            printf("%c%c", p.classe, p.cor);
        }
        printf("\n");
    }
    printf("  A B C D E F G H\n");
}
