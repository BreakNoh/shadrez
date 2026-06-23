#include "xadrez.h"
#include <stdio.h>

void print_jogada(Jogada *j) {
    printf("{\np:%c, cap: %d, x1: %d, y1: %d, x2: %d, y2: %d\n}", j->peca,
           j->captura, j->origem.x + 1, 1 + j->origem.y, j->alvo.x + 1,
           1 + j->alvo.y);
}

int main(int argc, char *argv[]) {
    Jogada jog;

    if (argc > 1) {
        jog = parse_comando(argv[1]);
    } else {

        jog = parse_comando("Ba4");
    }

    print_jogada(&jog);

    return 0;
}
