# parametro padrao: arquivo de entrada
input = "tests/in.txt"

# compilador
CC = g++

# regra default: obter os executáveis dos dois algoritmos
all: backtracking dsatur

# prepara os executáveis dos dois algoritmos
backtracking: backtracking.o Graph.o
	$(CC) backtracking.o Graph.o -o backtracking

dsatur: dsatur.o Graph.o
	$(CC) dsatur.o Graph.o -o dsatur

# prepara os arquivos objetos dos dois algoritmos
backtracking.o: src/backtracking.cpp src/Graph.h
	$(CC) -c -I src/ src/backtracking.cpp -o backtracking.o

dsatur.o: src/dsatur.cpp src/Graph.h
	$(CC) -c -I src/ src/dsatur.cpp -o dsatur.o

# prepara o arquivo objeto da biblioteca
Graph.o: src/Graph.cpp src/Graph.h
	$(CC) -c -I src/ src/Graph.cpp -o Graph.o

# executa os dois algoritmos
run: runbacktracking rundsatur

# executa o algoritmo 1 separadamente
runbacktracking: backtracking
	./backtracking $(input)

# executa o algoritmo 2 separadamente
rundsatur: dsatur
	./dsatur $(input)

# remove os arquivos objetos e os executáveis
clean:
	rm -f *.o backtracking dsatur
