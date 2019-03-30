# A user Linux Makefile for the ivl sample

PACKAGES=ivl ivl-cv ivl-lina
LIBS=$(shell pkg-config --libs $(PACKAGES))
CFLAGS=$(shell pkg-config --cflags $(PACKAGES))


.SUFFIXES: .cpp .o

.cpp.o:
	g++ -c $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CFLAGS) $< $(LIBS) -o $@

clean:
	rm *.o

full_ivl_sample: full_ivl_sample.o
	g++ $< $(LIBS) -o $@


