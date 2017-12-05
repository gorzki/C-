cmatrix: cmatrix.o
	g++ -g -Wall -pedantic $^ -o $@

cmatrix.o: matrix.cpp cmatrix.h
	g++ -g -c -Wall -pedantic $< -o $@

.PHONY: clean

clean:
	-rm cmatrix.o cmatrix
