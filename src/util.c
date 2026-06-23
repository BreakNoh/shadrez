#include "xadrez.h"

bool esta_dentro(i8 x, i8 y) {
    return x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO;
}
bool sao_mesma_peca(Peca a, Peca b) {
    return a.classe == b.classe && a.cor == b.cor;
}
