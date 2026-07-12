#include "teste.h"
#include <stdio.h>

extern Teste __start_testes;
extern Teste __stop_testes;

void rodar_testes() {
  Teste *atual = &__start_testes;
  Teste *fim = &__stop_testes;

  int total = fim - atual;

  printf("testes encotrados: %d\n\n", total);

  for (; atual < fim; atual++) {
    printf("[iniciando] %s\n", atual->nome);
    int res = atual->funcao();
    printf("[finalizado] %s: %s\n\n", atual->nome, res == ERRO ? "erro" : "ok");
  }

  printf("testes finalizados\n");
}

int main() {
  rodar_testes();
  // test_cavalo_ambiguo();
  // test_bispo_ambiguo();
  // test_torre_ambiguo();
  return 0;
}
