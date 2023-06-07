GCC=clang++
FLAGS=-std=c++11 -O1 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

all: output/pa03

.PHONY: output/pa03

output/pa03:
	$(GCC) $(FLAGS) -o $@ `find . -type f -name "*.cpp" | xargs -I % echo -n "% "`