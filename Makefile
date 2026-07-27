CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4 -MMD -MP
SRC=$(wildcard src/*.cc)
OBJ=$(SRC:.cc=.o)
DEP=$(OBJ:.o=.d)

exec: bin/exec

bin/exec: $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $@

src/%.o: src/%.cc
	$(CXX) $(CXX_FLAGS) -c $< -o $@

-include $(DEP)

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*
	rm -rf src/*.o src/*.d