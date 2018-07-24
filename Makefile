BIN_DIR := bin
PROGRAM := $(BIN_DIR)/ElonaFoobar
TEST_RUNNER := $(BIN_DIR)/test_runner
BENCH_RUNNER := $(BIN_DIR)/bench_runner
APK := $(BIN_DIR)/ElonaFoobar-debug.apk
APK_RELEASE := $(BIN_DIR)/ElonaFoobar-release.apk

FORMAT := clang-format
FIND := find
XARGS := xargs
MKDIR := mkdir


.PHONY: FORCE


all: build


build: $(BIN_DIR) $(PROGRAM)


tests: $(BIN_DIR) $(TEST_RUNNER)


bench: $(BIN_DIR) $(BENCH_RUNNER)


android: $(BIN_DIR) $(APK)


android_release: $(BIN_DIR) $(APK_RELEASE)


$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)


$(PROGRAM): FORCE
	cd $(BIN_DIR); cmake .. $(CMAKE_ARGS); make


$(TEST_RUNNER):
	cd $(BIN_DIR); cmake .. $(CMAKE_ARGS) -DWITH_TESTS=TESTS; make


$(BENCH_RUNNER):
	cd $(BIN_DIR); cmake .. $(CMAKE_ARGS) -DWITH_TESTS=BENCH --config Release; make


$(APK): FORCE
	cd $(BIN_DIR); cmake .. -DANDROID_GENERATE_PROPERTIES=ON
	export TERM=xterm-color; cd android; ./gradlew assembleDebug; cp distribution/android/app/outputs/apk/debug/app-debug.apk ../${APK}


$(APK_RELEASE): FORCE
	cd $(BIN_DIR); cmake .. -DANDROID_GENERATE_PROPERTIES=ON
	export TERM=xterm-color; cd android; ./gradlew assembleRelease; cp distribution/android/app/outputs/apk/release/app-release-unsigned.apk ../${APK_RELEASE}
	echo -e "\e[93m\"You've been a faithful servant of me. Here, use it wisely.\""
	echo "Something is placed at $(BIN_DIR)."


clean: FORCE
	-@$(RM) -rf $(BIN_DIR)
	-@$(RM) -rf android/distribution android/app/.externalNativeBuild android/SDL2/.externalNativeBuild


# Format src/*.{hpp,cpp} except under src/thirdparty.
format: FORCE
	$(FIND) src \( -type d -name "thirdparty" -prune \) -or \( -name "*.cpp" -or -name "*.hpp" \) -print0 | \
		$(XARGS) -n 1 -0 -I{} sh -c "$(FORMAT) -i {}; echo {}"
	test -z "$$(git status --short)"

ldoc:
	mkdir -p $(BIN_DIR)/doc
	cp doc/README.md $(BIN_DIR)/doc/readme.md
	cp doc/ldoc.css $(BIN_DIR)/doc/ldoc.css
	cp -r doc/topics $(BIN_DIR)/doc
	cp -r doc/examples $(BIN_DIR)/doc/examples
	cp doc/uikit.min.css $(BIN_DIR)/doc/uikit.min.css
	cp doc/red_putit.png $(BIN_DIR)/doc/red_putit.png
	cd $(BIN_DIR) && ldoc -c ../doc/config.ld -l ../doc -s ../doc ../doc/api/
	cp -r $(BIN_DIR)/doc docs

luacheck:
	luacheck --version
	luacheck runtime/mods/
	luacheck src/tests/lua

i18n-check:
	lua -e 'package.path="tools/i18n_checker/src/?.lua;"..package.path'\
	    tools/i18n_checker/bin/i18n_checker.lua $(CURDIR) en
	lua -e 'package.path="tools/i18n_checker/src/?.lua;"..package.path'\
	    tools/i18n_checker/bin/i18n_checker.lua $(CURDIR) jp

i18n-check-err:
	lua -e 'package.path="tools/i18n_checker/src/?.lua;"..package.path'\
	    tools/i18n_checker/bin/i18n_checker.lua $(CURDIR) en --no-warnings
	lua -e 'package.path="tools/i18n_checker/src/?.lua;"..package.path'\
	    tools/i18n_checker/bin/i18n_checker.lua $(CURDIR) jp --no-warnings

rebuild: clean build
