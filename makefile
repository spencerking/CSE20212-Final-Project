all: main

main:
	g++ main.cpp -o main -framework OpenGL -framework GLUT # FOR MAC

clean: main