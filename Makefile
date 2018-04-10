BIN_DIR := bin
PROGRAM := $(BIN_DIR)/ElonaFoobar

FORMAT := clang-format
FIND := find
XARGS := xargs
MKDIR := mkdir
 

.PHONY: FORCE


all: build


build: $(BIN_DIR) $(PROGRAM)


$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)


$(PROGRAM): FORCE
	cd $(BIN_DIR); cmake .. $(CMAKE_ARGS); make


clean: FORCE
	-@$(RM) -rf $(BIN_DIR)


format: FORCE
	$(FIND) . \( -name "*.cpp" -or -name "*.hpp" \) -print0 | $(XARGS) -0 $(FORMAT) -i


rebuild: clean build
