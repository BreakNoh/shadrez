#ifndef TESTE_H
#define TESTE_H

#include "../src/xadrez.h"
#include <assert.h>
#include <stdio.h>

void test_cavalo_ambiguo();
void test_bispo_ambiguo();

#define INICIAR_TESTE(nome) void test_##nome(){ \
	char __nome_teste[] = #nome; \
	int __erros = 0; \
	printf("== INICIANDO TESTE %s ==\n", __nome_teste);
#define FINALIZAR_TESTE \
	printf("erros encontrados: %d\n", __erros); \
	printf("== TESTE %s FINALIZADO ==\n\n", __nome_teste); \
	}
#define ASSERT_EQ(a,b,d) \
	if (a != b) { \
		printf("assert falhou: " #a "(%"#d") != " #b "(%"#d")\n", a, b); \
		__erros ++; \
	}

#endif // !TESTE_H
