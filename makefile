build:
	gcc ./src/*.c -o ./bin/main -lncurses

run: build
	./bin/main $(ARGS)
