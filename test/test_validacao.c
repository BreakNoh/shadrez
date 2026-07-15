#include "teste.h"
#include <stdbool.h>

static Leiaute l = {
    "-", "-", "-", "PpP", "pPp-", "-", "-", "-",
};

TESTE(test_en_passant) {
    Tabuleiro tab = new_tabuleiro(l);
    struct {
        Movimento ult_mov;
        Movimento mov;
        Cor cor;
        bool valido;
    } testes[] = {
        {{0, 6, 0, 4}, {1, 4, 0, 5}, BRANCA, true}, // branco esq

        {{2, 6, 2, 4}, {1, 4, 2, 5}, BRANCA, true}, // branco dir

        {{0, 1, 0, 3}, {1, 3, 0, 2}, PRETA, true}, // preto esq

        {{2, 1, 2, 3}, {1, 3, 2, 2}, PRETA, true}, // preto dir

        {{2, 1, 2, 2}, {1, 3, 2, 2}, PRETA, false}, // preto dir
    };

    int num_testes = sizeof(testes) / sizeof(testes[0]);

    for (int i = 0; i < num_testes; i++) {
        Jogada jog = (Jogada){.peca = {PEAO, testes[i].cor},
                              .captura = true,
                              .mov = testes[i].mov};
        tab.ultimo_movimento = testes[i].ult_mov;

        ASSERT_EQ(validar_jogada(&tab, jog), testes[i].valido, d)
    }
}
