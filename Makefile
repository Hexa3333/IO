COMPILER = clang++
FILES = $(wildcard src/**)
SRC = $(wildcard src/**.cpp)
FLAGS = -std=c++17 -g -DUNIX

all: $(FILES)
	$(COMPILER) $(SRC) $(FLAGS) -o test

run: all
	./test
