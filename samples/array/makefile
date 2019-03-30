# A user Linux Makefile for the ivl sample

PACKAGES=ivl
IVL_LIBS=$(shell pkg-config --libs $(PACKAGES))
IVL_CFLAGS=$(shell pkg-config --cflags $(PACKAGES))

LIBS=$(IVL_LIBS)
CFLAGS=$(IVL_CFLAGS)


.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CFLAGS) $< $(LIBS) -o $@

array_sample: array_samples.o array_2d_samples.o array_nd_samples.o other_array_samples.o set_samples.o main.o
	g++ $^ $(LIBS) -o $@

.PHONY: clean

clean:
	rm *.o


