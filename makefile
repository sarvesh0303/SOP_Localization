all: src/main.cc src/core_iepf.cc src/core_adaptive.cc src/input_parse.cc src/merge.cc
	g++ -std=c++11 -o fex src/main.cc src/core_iepf.cc src/core_adaptive.cc src/input_parse.cc src/merge.cc  lib/defs.h `pkg-config opencv --cflags --libs`

clean:
	rm fex;
