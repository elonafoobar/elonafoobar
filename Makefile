BIN_DIR := bin

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


all: $(BIN_DIR) FORCE # Build the most recently built target.
	cd $(BIN_DIR); \
		cmake .. $(CMAKE_ARGS); \
		cmake --build .


run: build FORCE # Run Elona foobar (debug).
	./$(BIN_DIR)/Elona_foobar


build: $(BIN_DIR) FORCE # Build Elona foobar (debug).
	cd $(BIN_DIR); \
		cmake .. -DELONA_BUILD_TARGET=GAME -DCMAKE_BUILD_TYPE=Debug $(CMAKE_ARGS); \
		cmake --build . --config Debug


run_release: build_release FORCE # Run Elona foobar (release).
	./$(BIN_DIR)/Elona_foobar


build_release: $(BIN_DIR) FORCE # Build Elona foobar (release).
	cd $(BIN_DIR); \
		cmake .. -DELONA_BUILD_TARGET=GAME -DCMAKE_BUILD_TYPE=Release $(CMAKE_ARGS); \
		cmake --build . --config Release
	@echo "\"You've been a faithful servant of me. Here, use it wisely.\""
	@echo "Something is placed at $(BIN_DIR)."


tests: test_runner FORCE # Run all tests.
	cd $(BIN_DIR); \
		./Elona_foobar --durations=yes


test_runner: $(BIN_DIR) FORCE # Build test runner.
	# -@$(RM) -rf ./$(BIN_DIR)/tests
	cd $(BIN_DIR); \
		cmake .. -DELONA_BUILD_TARGET=TESTS -DCMAKE_BUILD_TYPE=Debug $(CMAKE_ARGS); \
		cmake --build . --config Debug


bench: bench_runner FORCE # Run benchmark.
	cd $(BIN_DIR); \
		./Elona_foobar


bench_runner: $(BIN_DIR) FORCE # Build benchmark runner.
	cd $(BIN_DIR); \
		cmake .. -DELONA_BUILD_TARGET=BENCH -DCMAKE_BUILD_TYPE=Release $(CMAKE_ARGS); \
		cmake --build . --config Release


android: $(BIN_DIR) FORCE # Build android Elona foobar (debug).
	cd $(BIN_DIR); cmake .. -DANDROID_GENERATE_PROPERTIES=ON
	export TERM=xterm-color; cd android; ./gradlew assembleDebug; cp distribution/android/app/outputs/apk/debug/app-debug.apk ../$(APK)


android_release: $(BIN_DIR) FORCE # Build android Elona foobar (release).
	cd $(BIN_DIR); cmake .. -DANDROID_GENERATE_PROPERTIES=ON
	export TERM=xterm-color; cd android; ./gradlew assembleRelease; cp distribution/android/app/outputs/apk/release/app-release-unsigned.apk ../$(APK_RELEASE)
	@echo "\"You've been a faithful servant of me. Here, use it wisely.\""
	@echo "Something is placed at $(BIN_DIR)."


$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)


clean: FORCE # Clean up built products.
	-@$(RM) -rf $(BIN_DIR)
	-@$(RM) -rf android/distribution android/app/.externalNativeBuild android/SDL2/.externalNativeBuild


# Format src/*.{hpp,cpp} except under src/thirdparty.
format: FORCE # Format all C++ source files.
	$(FIND) src \( -type d -name "thirdparty" -prune \) -or \( -name "*.cpp" -or -name "*.hpp" \) -print0 | \
		$(XARGS) -n 1 -0 -I{} sh -c "$(FORMAT) -i {}; echo {}"
	git diff
	test -z "$$(git status --short)"


ldoc: FORCE # Generate LDoc.
	-@$(RM) -rf $(BIN_DIR)/doc
	-@$(RM) -rf docs
	mkdir -p $(BIN_DIR)/doc
	cp doc/README.md $(BIN_DIR)/doc/readme.md
	cp doc/ldoc.css $(BIN_DIR)/doc/ldoc.css
	cp -r doc/topics $(BIN_DIR)/doc
	cp -r doc/examples $(BIN_DIR)/doc
	cp doc/uikit.min.css $(BIN_DIR)/doc/uikit.min.css
	cp doc/putit.png $(BIN_DIR)/doc/putit.png
	cd $(BIN_DIR) && ldoc -c ../doc/config.ld -l ../doc -s ../doc ../doc/api/
	cp -r $(BIN_DIR)/doc docs


luacheck: FORCE # Run luacheck.
	luacheck --version
	luacheck runtime/mods/
	luacheck src/tests/lua


i18n-check:FORCE  # Run i18n-checker.
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) en
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) jp


i18n-check-err: FORCE # Run i18n-checker with --no-warnings.
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) en --no-warnings
	./tools/i18n_checker/bin/i18n_checker $(CURDIR) jp --no-warnings


rebuild: clean build FORCE # Clean and build Elona.


help: FORCE # Show help.
	@$(GREP) '^[a-zA-Z_-]*:.* # .*' $(MAKEFILE_LIST) \
		| $(AWK) 'BEGIN {FS = ":.* # "}; {printf "%-25s%s\n", $$1, $$2}'
