all: ../3.cpp


../3.cpp: ast.dump astprinter.rb astoptimizer.rb
	ruby ast2cpp.rb < ast.dump > ../3.cpp


ast.dump: ../2.hsp parser.rb lexer.rb
	ruby hsp2ast.rb < ../2.hsp > ast.dump
