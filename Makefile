CXX := /usr/local/bin/g++-HEAD
#CXX_FLAGS := -Wall -Wextra -g -O0 -MMD -DDEBUG -std=c++17
CXX_FLAGS := -g -O0 -MMD -DDEBUG -std=c++17 -I/usr/local/include
LN_FLAGS := -lstdc++fs -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
BIN_DIR := bin
SRC_DIR := .
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(foreach i, $(SOURCES), $(BIN_DIR)/$(basename $(i)).o)
PROGRAM := ./runtime/elonafoobar


FORMAT := clang-format
FIND := find
XARGS := xargs


.PHONY: FORCE clean


all: build


build: $(PROGRAM)


$(PROGRAM): $(OBJECTS) sdl/sdl.a
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LN_FLAGS)


sdl/sdl.a: FORCE
	cd sdl; make


$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@


clean:
	-@$(RM) -f $(PROGRAM)
	-@$(RM) -f $(BIN_DIR)/*.d $(BIN_DIR)/*.o


format: FORCE
	$(FIND) $(SRC_DIR) \( -name "*.cpp" -or -name "*.hpp" \) -print0 | $(XARGS) -0 $(FORMAT) -i



rebuild: clean build


-include $(BIN_DIR)/*.d
