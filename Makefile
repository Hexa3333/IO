COMPILER = clang++
FILES = $(wildcard src/**)
SRC = $(wildcard src/**.cpp)
FLAGS = -std=c++17 -g

all: $(FILES)
	$(COMPILER) $(SRC) -o test

run: all
	./test
