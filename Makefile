GCC=g++
FLAGS=-O3

all: output/pa03

output/pa03: src/driver.cpp
	$(GCC) $(FLAGS) -o $@ $^