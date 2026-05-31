CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4
SRC=$(wildcard src/*.cc)
OBJ=$(SRC:.cc=.o)


exec: bin/exec

bin/exec: $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $@

src/%.o: src/%.cc
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*