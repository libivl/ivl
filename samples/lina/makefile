# A user Linux Makefile for the ivl sample

PACKAGES=ivl ivl-lina 
IVL_LIBS=$(shell pkg-config --libs $(PACKAGES))
IVL_CFLAGS=$(shell pkg-config --cflags $(PACKAGES))

LIBS=$(IVL_LIBS)
CFLAGS=$(IVL_CFLAGS)


.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CFLAGS) $< $(LIBS) -o $@

lina_sample: lina_sample.o
	g++ $^ $(LIBS) -o $@

.PHONY: clean

clean:
	rm *.o


