# CRLF -> LF
# Shift-JIS -> UTF-8


all: 5.cpp


1.hsp: 0.hsp 0-1.sh
	rm -f 1.hsp
	sh 0-1.sh

2.hsp: 1.hsp 1-2.sh
	rm -f 2.hsp
	sh 1-2.sh

3.cpp: 2.hsp FORCE
	cd 00-hsp2cpp/; make

4.cpp: 3.cpp 3-4.sh
	rm -f 4.cpp
	sh 3-4.sh

5.cpp: 4.cpp 4-5.rb
	rm -f 5.cpp
	ruby 4-5.rb < 4.cpp > 5.cpp


.PHONY: FORCE
