all:
	g++ -c test.cpp
	g++ test.o -o a.out -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm -rf *.o *.out
