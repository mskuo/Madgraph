CXXFLAGS = $(shell root-config --cflags) -Wno-write-strings -D_FILE_OFFSET_BITS=64 -DDROP_CGAL -I../ -I../external -I../external/tcl
DELPHES_LIBS = $(shell root-config --libs) -lEG -L../ -lDelphes

all:
	g++ -c dimuon.cc $(CXXFLAGS)
	g++ -o dimuon dimuon.o $(LDFLAGS) $(DELPHES_LIBS)
