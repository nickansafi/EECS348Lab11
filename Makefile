CC = g++
all: matrix
matrix: matrix.cpp
	$(CC) matrix.cpp -o matrix
clean:
	rm -rf matrix