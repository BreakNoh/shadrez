build:
	gcc ./src/*.c -o ./bin/main 

run: build
	./bin/main $(ARGS)

build-test:
	gcc  ./src/*.c ./test/*.c -o ./bin/test -D TESTE_RUN

test: build-test
	./bin/test
