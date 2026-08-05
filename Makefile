CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4 -MMD -MP -fsanitize=address -fno-omit-frame-pointer
SRC=$(wildcard src/*.cc)
OBJ=$(SRC:.cc=.o)
DEP=$(OBJ:.o=.d)
LIB_OBJ=$(filter-out src/driver.o,$(OBJ))
TEST_SRC=$(wildcard tests/*.cc)
TEST_OBJ=$(TEST_SRC:.cc=.o)
DEP+=$(TEST_OBJ:.o=.d)

exec: bin/exec
tests: bin/tests

bin/exec: $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $@
	
bin/tests: $(LIB_OBJ) $(TEST_OBJ)
	$(CXX) $(CXX_FLAGS) $(LIB_OBJ) $(TEST_OBJ) -o $@

src/%.o: src/%.cc
	$(CXX) $(CXX_FLAGS) -c $< -o $@

tests/%.o: tests/%.cc
	$(CXX) $(CXX_FLAGS) -c $< -o $@

-include $(DEP)

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*
	rm -rf src/*.o src/*.d