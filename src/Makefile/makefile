CC=g++
OPCOES_COMPILADOR=-I. -lSOIL -lglut -lGLU -lGLEW -lGL -std=c++14
TODOS_ARQUIVOS_PONTOH = 
TODOS_ARQUIVOS_OBJ = main.o  

%.o: ../%.cpp #$(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	$(CC) -o main $^ $(OPCOES_COMPILADOR)

run: all
	(cd .. && exec Makefile/main && cd Makefile)

clean:
	rm *.o main
