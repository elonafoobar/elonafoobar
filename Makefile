BIN_DIR := bin
PROGRAM := $(BIN_DIR)/Elona_foobar
TEST_RUNNER := $(BIN_DIR)/test_runner
BENCH_RUNNER := $(BIN_DIR)/bench_runner
APK := $(BIN_DIR)/Elona_foobar-debug.apk
APK_RELEASE := $(BIN_DIR)/Elona_foobar-release.apk

# Utilities
FORMAT := clang-format
FIND := find
XARGS := xargs
MKDIR := mkdir
GREP := grep
AWK := awk


.PHONY: FORCE


all: $(BIN_DIR) # Build the most recently built target.
	cd $(BIN_DIR); \
		cmake .. $(CMAKE_ARGS); \
		cmake --build .


build: $(BIN_DIR) $(PROGRAM) # Build Elona foobar (debug).


tests: $(BIN_DIR) $(TEST_RUNNER) # Build test runner.


bench: $(BIN_DIR) $(BENCH_RUNNER) # Build benchmark runner.


android: $(APK) # Build android Elona foobar (debug).


android_release: $(APK_RELEASE) # Build android Elona foobar (release).


$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)


$(PROGRAM): FORCE
	cd $(BIN_DIR); \
		cmake .. $(CMAKE_ARGS) -DELONA_BUILD_TARGET=GAME; \
		cmake --build . --config Debug


$(TEST_RUNNER):
	cd $(BIN_DIR); \
		cmake .. $(CMAKE_ARGS) -DELONA_BUILD_TARGET=TESTS; \
		cmake --build . --config Debug


$(BENCH_RUNNER):
	cd $(BIN_DIR); \
		cmake .. $(CMAKE_ARGS) -DELONA_BUILD_TARGET=BENCH; \
		cmake --build . --config Release


$(APK): FORCE
	cd $(BIN_DIR); cmake .. -DANDROID_GENERATE_PROPERTIES=ON
	export TERM=xterm-color; cd android; ./gradlew assembleDebug; cp distribution/android/app/outputs/apk/debug/app-debug.apk ../${APK}


$(APK_RELEASE): FORCE
	cd $(BIN_DIR); cmake .. -DANDROID_GENERATE_PROPERTIES=ON
	export TERM=xterm-color; cd android; ./gradlew assembleRelease; cp distribution/android/app/outputs/apk/release/app-release-unsigned.apk ../${APK_RELEASE}
	echo -e "\e[93m\"You've been a faithful servant of me. Here, use it wisely.\""
	echo "Something is placed at $(BIN_DIR)."


clean: FORCE # Clean up built products.
	-@$(RM) -rf $(BIN_DIR)
	-@$(RM) -rf android/distribution android/app/.externalNativeBuild android/SDL2/.externalNativeBuild


# Format src/*.{hpp,cpp} except under src/thirdparty.
format: FORCE # Format all C++ source files.
	$(FIND) src \( -type d -name "thirdparty" -prune \) -or \( -name "*.cpp" -or -name "*.hpp" \) -print0 | \
		$(XARGS) -n 1 -0 -I{} sh -c "$(FORMAT) -i {}; echo {}"
	git diff
	test -z "$$(git status --short)"


ldoc: # Generate LDoc.
	rm -rf $(BIN_DIR)/doc
	rm -rf docs
	mkdir -p $(BIN_DIR)/doc
	cp doc/README.md $(BIN_DIR)/doc/readme.md
	cp doc/ldoc.css $(BIN_DIR)/doc/ldoc.css
	cp -r doc/topics $(BIN_DIR)/doc
	cp -r doc/examples $(BIN_DIR)/doc
	cp doc/uikit.min.css $(BIN_DIR)/doc/uikit.min.css
	cp doc/putit.png $(BIN_DIR)/doc/putit.png
	cd $(BIN_DIR) && ldoc -c ../doc/config.ld -l ../doc -s ../doc ../doc/api/
	cp -r $(BIN_DIR)/doc docs


luacheck: # Run luacheck.
	luacheck --version
	luacheck runtime/mods/
	luacheck src/tests/lua


i18n-check: # Run i18n-checker.
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) en
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) jp


i18n-check-err: # Run i18n-checker with --no-warnings.
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) en --no-warnings
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) jp --no-warnings


rebuild: clean build # Clean and build Elona.


help: # Show help.
	@$(GREP) '^[a-zA-Z_-]*:.* # .*' $(MAKEFILE_LIST) \
		| $(AWK) 'BEGIN {FS = ":.* # "}; {printf "%-25s%s\n", $$1, $$2}'
