all: main

main: main.o IntroRoom.o
	g++ main.o IntroRoom.o -framework OpenGL -framework GLUT -o main # FOR MAC

main.o: main.cpp
	g++ -c main.cpp

IntroRoom.o: IntroRoom.cpp
	g++ -c IntroRoom.cpp

clean: main