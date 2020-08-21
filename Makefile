CC=mpic++
INC=-I./include
all:
	$(CC) $(INC) -c src/test.cpp src/engine.cpp
	$(CC) test.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf *.o *.out
