#include "teste.h"
#include <stdbool.h>

typedef struct {
    char *comando;
    Cor cor_usada;
    Jogada espeardo;
} TesteParse;

TESTE(parse_comando_sem_captura) {
    TesteParse testes[] = {

        {"c3", BRANCA,
         (Jogada){.peca = {PEAO, BRANCA},
                  .captura = false,
                  .mov = {-1, -1, 2, 2},
                  .res = NAO_RESOLVIDA}},
        {"e4", BRANCA,
         (Jogada){.peca = {PEAO, BRANCA},
                  .captura = false,
                  .mov = {-1, -1, 4, 3},
                  .res = NAO_RESOLVIDA}},
        {"a6", PRETA,
         (Jogada){.peca = {PEAO, PRETA},
                  .captura = false,
                  .mov = {-1, -1, 0, 5},
                  .res = NAO_RESOLVIDA}},
        {"h5", PRETA,
         (Jogada){.peca = {PEAO, PRETA},
                  .captura = false,
                  .mov = {-1, -1, 7, 4},
                  .res = NAO_RESOLVIDA}},

        {"Cf3", BRANCA,
         (Jogada){.peca = {CAVALO, BRANCA},
                  .captura = false,
                  .mov = {-1, -1, 5, 2},
                  .res = NAO_RESOLVIDA}},
        {"Cc6", PRETA,
         (Jogada){.peca = {CAVALO, PRETA},
                  .captura = false,
                  .mov = {-1, -1, 2, 5},
                  .res = NAO_RESOLVIDA}},
        {"Bc4", BRANCA,
         (Jogada){.peca = {BISPO, BRANCA},
                  .captura = false,
                  .mov = {-1, -1, 2, 3},
                  .res = NAO_RESOLVIDA}},
        {"Be7", PRETA,
         (Jogada){.peca = {BISPO, PRETA},
                  .captura = false,
                  .mov = {-1, -1, 4, 6},
                  .res = NAO_RESOLVIDA}},
        {"Td1", BRANCA,
         (Jogada){.peca = {TORRE, BRANCA},
                  .captura = false,
                  .mov = {-1, -1, 3, 0},
                  .res = NAO_RESOLVIDA}},
        {"Te8", PRETA,
         (Jogada){.peca = {TORRE, PRETA},
                  .captura = false,
                  .mov = {-1, -1, 4, 7},
                  .res = NAO_RESOLVIDA}},
        {"Dd2", BRANCA,
         (Jogada){.peca = {RAINHA, BRANCA},
                  .captura = false,
                  .mov = {-1, -1, 3, 1},
                  .res = NAO_RESOLVIDA}},
        {"Dd8", PRETA,
         (Jogada){.peca = {RAINHA, PRETA},
                  .captura = false,
                  .mov = {-1, -1, 3, 7},
                  .res = NAO_RESOLVIDA}},
        {"Re2", BRANCA,
         (Jogada){.peca = {REI, BRANCA},
                  .captura = false,
                  .mov = {-1, -1, 4, 1},
                  .res = NAO_RESOLVIDA}},
        {"Rg8", PRETA,
         (Jogada){.peca = {REI, PRETA},
                  .captura = false,
                  .mov = {-1, -1, 6, 7},
                  .res = NAO_RESOLVIDA}},

        {"Cbd2", BRANCA,
         (Jogada){.peca = {CAVALO, BRANCA},
                  .captura = false,
                  .mov = {1, -1, 3, 1},
                  .res = NAO_RESOLVIDA}},
        {"Tfc1", BRANCA,
         (Jogada){.peca = {TORRE, BRANCA},
                  .captura = false,
                  .mov = {5, -1, 2, 0},
                  .res = NAO_RESOLVIDA}},
        {"Tac8", PRETA,
         (Jogada){.peca = {TORRE, PRETA},
                  .captura = false,
                  .mov = {0, -1, 2, 7},
                  .res = NAO_RESOLVIDA}},

        {"T1e2", BRANCA,
         (Jogada){.peca = {TORRE, BRANCA},
                  .captura = false,
                  .mov = {-1, 0, 4, 1},
                  .res = NAO_RESOLVIDA}},
        {"C8f6", PRETA,
         (Jogada){.peca = {CAVALO, PRETA},
                  .captura = false,
                  .mov = {-1, 7, 5, 5},
                  .res = NAO_RESOLVIDA}}};

    int total_testes = sizeof(testes) / sizeof(testes[0]);

    for (int i = 0; i < total_testes; i++) {
        TesteParse teste = testes[i];
        bool sucesso = false;
        Jogada j = parse_comando(teste.comando, teste.cor_usada, &sucesso);

        // ASSERT_EQ(sucesso, true, d);
        ASSERT_EQ(j.peca.classe, teste.espeardo.peca.classe, c);
        ASSERT_EQ(j.peca.cor, teste.espeardo.peca.cor, c);
        ASSERT_EQ(j.mov.x2, teste.espeardo.mov.x2, d);
        ASSERT_EQ(j.mov.y2, teste.espeardo.mov.y2, d);
        ASSERT_EQ(j.mov.x1, teste.espeardo.mov.x1, d);
        ASSERT_EQ(j.mov.y1, teste.espeardo.mov.y1, d);
    }
}

TESTE(parse_comando_com_captura) {
    TesteParse testes[] = {

        {"cxd4", BRANCA,
         (Jogada){.peca = {PEAO, BRANCA},
                  .captura = true,
                  .mov = {2, -1, 3, 3},
                  .res = NAO_RESOLVIDA}},
        {"exd5", BRANCA,
         (Jogada){.peca = {PEAO, BRANCA},
                  .captura = true,
                  .mov = {4, -1, 3, 4},
                  .res = NAO_RESOLVIDA}},
        {"axb5", PRETA,
         (Jogada){.peca = {PEAO, PRETA},
                  .captura = true,
                  .mov = {0, -1, 1, 4},
                  .res = NAO_RESOLVIDA}},
        {"gxf6", PRETA,
         (Jogada){.peca = {PEAO, PRETA},
                  .captura = true,
                  .mov = {6, -1, 5, 5},
                  .res = NAO_RESOLVIDA}},

        {"Cxf3", BRANCA,
         (Jogada){.peca = {CAVALO, BRANCA},
                  .captura = true,
                  .mov = {-1, -1, 5, 2},
                  .res = NAO_RESOLVIDA}},
        {"Cxc6", PRETA,
         (Jogada){.peca = {CAVALO, PRETA},
                  .captura = true,
                  .mov = {-1, -1, 2, 5},
                  .res = NAO_RESOLVIDA}},
        {"Bxc4", BRANCA,
         (Jogada){.peca = {BISPO, BRANCA},
                  .captura = true,
                  .mov = {-1, -1, 2, 3},
                  .res = NAO_RESOLVIDA}},
        {"Bxe7", PRETA,
         (Jogada){.peca = {BISPO, PRETA},
                  .captura = true,
                  .mov = {-1, -1, 4, 6},
                  .res = NAO_RESOLVIDA}},
        {"Txd1", BRANCA,
         (Jogada){.peca = {TORRE, BRANCA},
                  .captura = true,
                  .mov = {-1, -1, 3, 0},
                  .res = NAO_RESOLVIDA}},
        {"Txe8", PRETA,
         (Jogada){.peca = {TORRE, PRETA},
                  .captura = true,
                  .mov = {-1, -1, 4, 7},
                  .res = NAO_RESOLVIDA}},
        {"Dxd2", BRANCA,
         (Jogada){.peca = {RAINHA, BRANCA},
                  .captura = true,
                  .mov = {-1, -1, 3, 1},
                  .res = NAO_RESOLVIDA}},
        {"Dxd8", PRETA,
         (Jogada){.peca = {RAINHA, PRETA},
                  .captura = true,
                  .mov = {-1, -1, 3, 7},
                  .res = NAO_RESOLVIDA}},
        {"Rxe2", BRANCA,
         (Jogada){.peca = {REI, BRANCA},
                  .captura = true,
                  .mov = {-1, -1, 4, 1},
                  .res = NAO_RESOLVIDA}},
        {"Rxg8", PRETA,
         (Jogada){.peca = {REI, PRETA},
                  .captura = true,
                  .mov = {-1, -1, 6, 7},
                  .res = NAO_RESOLVIDA}},

        {"Cbxd2", BRANCA,
         (Jogada){.peca = {CAVALO, BRANCA},
                  .captura = true,
                  .mov = {1, -1, 3, 1},
                  .res = NAO_RESOLVIDA}},
        {"Tfxc1", BRANCA,
         (Jogada){.peca = {TORRE, BRANCA},
                  .captura = true,
                  .mov = {5, -1, 2, 0},
                  .res = NAO_RESOLVIDA}},
        {"Taxc8", PRETA,
         (Jogada){.peca = {TORRE, PRETA},
                  .captura = true,
                  .mov = {0, -1, 2, 7},
                  .res = NAO_RESOLVIDA}},
        {"T1xe2", BRANCA,
         (Jogada){.peca = {TORRE, BRANCA},
                  .captura = true,
                  .mov = {-1, 0, 4, 1},
                  .res = NAO_RESOLVIDA}},
        {"C8xf6", PRETA,
         (Jogada){.peca = {CAVALO, PRETA},
                  .captura = true,
                  .mov = {-1, 7, 5, 5},
                  .res = NAO_RESOLVIDA}}};

    int total_testes = sizeof(testes) / sizeof(testes[0]);

    for (int i = 0; i < total_testes; i++) {
        TesteParse teste = testes[i];
        bool sucesso = false;
        Jogada j = parse_comando(teste.comando, teste.cor_usada, &sucesso);

        // ASSERT_EQ(sucesso, true, d);
        ASSERT_EQ(j.peca.classe, teste.espeardo.peca.classe, c);
        ASSERT_EQ(j.peca.cor, teste.espeardo.peca.cor, c);
        ASSERT_EQ(j.captura, teste.espeardo.captura, d);
        ASSERT_EQ(j.mov.x2, teste.espeardo.mov.x2, d);
        ASSERT_EQ(j.mov.y2, teste.espeardo.mov.y2, d);
        ASSERT_EQ(j.mov.x1, teste.espeardo.mov.x1, d);
        ASSERT_EQ(j.mov.y1, teste.espeardo.mov.y1, d);
    }
}
