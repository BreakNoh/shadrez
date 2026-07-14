#include "xadrez.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    Tabuleiro tab = new_tabuleiro(NULL);

    char comando[11] = {0};

    while (true) {
        print_tab(&tab, true);
        scanf("%10s", comando);

        if (strcmp(comando, "exit") == 0) {
            return 0;
        }

        Jogada jog = parse_comando(comando, tab.jogador, NULL);
        Resolucao res = resolver_jogada(tab.posicoes, &jog);

        switch (res) {
        case AMBIGUO:
            printf("movimento ambiguo\n");
            continue;
        case NENHUMA:
            printf("peca não encotrada\n");
            continue;
        case ENCONTRADA:
            bool mov_legal = validar_movimento(
                tab.posicoes, (Movimento){jog.origem.x, jog.origem.y,
                                          jog.alvo.x, jog.alvo.y});

            if (!mov_legal) {
                printf("movimento ilegal\n");
                continue;
            }

            mover_peca(&tab, jog.origem.x, jog.origem.y, jog.alvo.x,
                       jog.alvo.y);
            tab.jogador = tab.jogador == BRANCA ? PRETA : BRANCA;
            continue;
        }
    }

    return 0;
}
