#include "xadrez.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  Jogada jog;
  Tabuleiro tab = new_tabuleiro(NULL);

  char comando[16] = {0};

  while (true) {
    print_tab(&tab, true);
    scanf("%s", comando);

    printf("%s\n", comando);
  }

  return 0;
}
