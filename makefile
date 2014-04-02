all: main

main: main.o heightfield.o
	g++ main.o heightfield.o -lglut -lGL -lGLU

main.o: main.cpp
	g++ -c main.cpp

heightfield.o: heightfield.cpp
	g++ -c heightfield.cpp

clean: main