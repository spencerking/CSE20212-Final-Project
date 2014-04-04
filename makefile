all: main

main: main.o heightfield.o camera.o
	g++ main.o heightfield.o camera.o -lglut -lGL -lGLU

main.o: main.cpp
	g++ -c main.cpp

heightfield.o: heightfield.cpp
	g++ -c heightfield.cpp

camera.o: camera.cpp
	g++ -c camera.cpp

clean: main
