BIN_DIR := bin
PROGRAM := $(BIN_DIR)/ElonaFoobar
TEST_RUNNER := $(BIN_DIR)/test_runner
BENCH_RUNNER := $(BIN_DIR)/bench_runner

FORMAT := clang-format
FIND := find
XARGS := xargs
MKDIR := mkdir


.PHONY: FORCE


all: build


build: $(BIN_DIR) $(PROGRAM)


tests: $(BIN_DIR) $(TEST_RUNNER)


bench: $(BIN_DIR) $(BENCH_RUNNER)


$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)


$(PROGRAM): FORCE
	cd $(BIN_DIR); cmake .. $(CMAKE_ARGS); make


$(TEST_RUNNER):
	cd $(BIN_DIR); cmake .. $(CMAKE_ARGS) -DWITH_TESTS=TESTS; make


$(BENCH_RUNNER):
	cd $(BIN_DIR); cmake .. $(CMAKE_ARGS) -DWITH_TESTS=BENCH --config Release; make


clean: FORCE
	-@$(RM) -rf $(BIN_DIR)


# Format src/*.{hpp,cpp} except under src/thirdparty.
format: FORCE
	$(FIND) src \( -type d -name "thirdparty" -prune \) -or \( -name "*.cpp" -or -name "*.hpp" \) -print0 | \
		$(XARGS) -n 1 -0 -I{} sh -c "$(FORMAT) -i {}; echo {}"

ldoc:
	mkdir -p $(BIN_DIR)/doc
	cp doc/README.md $(BIN_DIR)/doc/readme.md
	cp doc/ldoc.css $(BIN_DIR)/doc/ldoc.css
	cp -r doc/topics $(BIN_DIR)/doc
	cp -r doc/examples $(BIN_DIR)/doc/examples
	cp doc/uikit.min.css $(BIN_DIR)/doc/uikit.min.css
	cp doc/*.png $(BIN_DIR)/doc/
	cd $(BIN_DIR) && ldoc -c ../doc/config.ld -l ../doc -s ../doc ../doc/api/
	cp -r $(BIN_DIR)/doc docs

luacheck:
	luacheck --version
	luacheck runtime/mods/
	luacheck src/tests/lua

rebuild: clean build
