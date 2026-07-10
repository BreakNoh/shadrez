#ifndef TESTE_H
#define TESTE_H

#include "../src/xadrez.h"
#include <assert.h>
#include <stdio.h>

void test_cavalo_ambiguo();

#define INICIAR_TESTE(nome) void test_##nome(){ \
	char __nome_teste[] = #nome; \
	printf("== INICIANDO TESTE %s ==\n", __nome_teste);
#define FINALIZAR_TESTE \
	printf("== TESTE %s FINALIZADO ==\n", __nome_teste);}
#define ASSERT_EQ(a,b,d) \
	if (a != b) {printf("assert falhou: " #a "(%"#d") != " #b "(%"#d")\n", a, b);}

#endif // !TESTE_H
