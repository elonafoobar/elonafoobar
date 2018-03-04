CXX := /usr/local/bin/g++-HEAD
CXX_FLAGS := -Werror -Wall -Wextra -g -O0 -MMD -DDEBUG -std=c++17 -I/usr/local/include -I./thirdparty $(EX_CXX_FLAGS)
LN_FLAGS := -lstdc++fs -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua
BIN_DIR := bin
SRC_DIR := .
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(foreach i, $(SOURCES), $(BIN_DIR)/$(basename $(i)).o)
RUNTIME_DIR := ./runtime
PROGRAM := $(RUNTIME_DIR)/elonafoobar


FORMAT := clang-format
FIND := find
XARGS := xargs
MKDIR := mkdir


.PHONY: FORCE clean cleandep


all: build


build: $(RUNTIME_DIR) $(BIN_DIR) $(PROGRAM)


$(RUNTIME_DIR):
	$(MKDIR) $(RUNTIME_DIR)


$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)


$(PROGRAM): $(OBJECTS) snail/snail.a
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LN_FLAGS)


snail/snail.a: FORCE
	cd snail; make


$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@


clean:
	-@$(RM) -f $(PROGRAM)
	$(MAKE) cleandep
	-@$(RM) -f $(BIN_DIR)/*.o


format: FORCE
	$(FIND) $(SRC_DIR) \( -name "*.cpp" -or -name "*.hpp" \) -print0 | $(XARGS) -0 $(FORMAT) -i


checksyntax:
	$(MAKE) EX_CXX_FLAGS=-fsyntax-only


cleandep:
	-@$(RM) -f $(BIN_DIR)/*.d



rebuild: clean build


-include $(BIN_DIR)/*.d
