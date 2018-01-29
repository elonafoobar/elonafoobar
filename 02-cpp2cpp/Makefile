CXX := /usr/local/Cellar/gcc/HEAD-256941_1/bin/g++-HEAD


all: build


build: 7.o std.o sdl/sdl.a
	$(CXX) -g -O0 --std=c++17 7.o std.o sdl/sdl.a -lstdc++fs -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

sdl/sdl.a: FORCE
	cd sdl; make

std.o: elona.hpp std.cpp variables.hpp
	$(CXX) -c -O0 -g --std=c++17 -I/usr/local/include -o std.o std.cpp

7.o: 7.cpp elona.hpp variables.hpp main.hpp
	$(CXX) -c -O0 -g --std=c++17 -o 7.o 7.cpp

7.cpp: 6.cpp 6-7.sh header footer
	rm -f 7.cpp
	sh 6-7.sh

6.cpp: fast.dump fast2cpp.rb typetable.rb ctype.rb simpletypeanalyzer.rb astprinter.rb builtins.rb statanalyzer.rb
	rm -f 6.cpp
	ruby fast2cpp.rb < fast.dump > 6.cpp 2> log


fast.dump: ast.dump ast2fast.rb flowanalyzer.rb gotoanalyzer.rb gotosimplifier.rb
	ruby ast2fast.rb < ast.dump > fast.dump


ast.dump: ../5.cpp parser.rb lexer.rb
	cp ../5.cpp ./5.cpp
	ruby cpp2ast.rb < ./5.cpp > ast.dump


.PHONY: build FORCE
