FLAGS = -std=c++20
all: File.cpp File.hpp FstreamTest.cpp
	clang++ File.cpp FstreamTest.cpp -g -o FstreamTest

run: all
	./FstreamTest
