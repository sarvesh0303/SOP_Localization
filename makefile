all: src/main.cc src/core_iepf.cc src/core_adaptive.cc src/input_parse.cc src/merge.cc src/sarvesh_fe.cc 
	g++ -std=c++11 -o fex src/main.cc src/core_iepf.cc src/core_adaptive.cc src/input_parse.cc src/merge.cc src/sarvesh_fe.cc  lib/defs.h lib/cvdefs.h lib/feature_extract.h lib/sarvesh_fe.h `pkg-config opencv --cflags --libs`

clean:
	rm fex;
