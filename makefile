build:
	gcc ./src/*.c -o ./bin/main -lncurses

run: build
	./bin/main $(ARGS)

build-test:
	gcc  ./src/parse.c ./src/validacao.c ./src/resolve.c ./src/tabuleiro.c ./src/util.c ./test/*.c -o ./bin/test

test: build-test
	./bin/test
