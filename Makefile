
all: clean build
clean:
	rm -f brainfuck
build:
	g++ brainfuck.cpp -o brainfuck
