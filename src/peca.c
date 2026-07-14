#include "xadrez.h"

Peca new_peca(Classe classe, Cor cor) { return (Peca){classe, cor}; }

bool cmp_peca(Peca a, Peca b) { return a.classe == b.classe && a.cor == b.cor; }

Peca parse_peca(char ch) {
    if (ch < 'a' && ch > 'z' && ch < 'A' && ch > 'Z') {
        return PECA_VAZIA;
    }

    bool maiscula = ch >= 'A' && ch <= 'Z';
    Cor cor = maiscula ? BRANCA : PRETA;

    switch (ch) {
    case 'c':
    case 'C':
        return (Peca){CAVALO, cor};
    case 'b':
    case 'B':
        return (Peca){BISPO, cor};
    case 't':
    case 'T':
        return (Peca){TORRE, cor};
    case 'p':
    case 'P':
        return (Peca){PEAO, cor};
    case 'd':
    case 'D':
        return (Peca){RAINHA, cor};
    case 'r':
    case 'R':
        return (Peca){REI, cor};
    default:
        return PECA_VAZIA;
    }
}
