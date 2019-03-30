# A user Linux Makefile for the ivl sample

PACKAGES=ivl ivl-lina ivl-cv
IVL_LIBS=$(shell pkg-config --libs $(PACKAGES))
IVL_CFLAGS=$(shell pkg-config --cflags $(PACKAGES))

LIBS=$(IVL_LIBS)
CFLAGS=$(IVL_CFLAGS)


.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CFLAGS) $< $(LIBS) -o $@

full_ivl_sample: full_ivl_sample.o
	g++ $^ $(LIBS) -o $@

.PHONY: clean

clean:
	rm *.o


