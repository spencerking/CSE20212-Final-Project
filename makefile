OS := $(shell uname)
OBJECTS = main.o Skybox.o heightfield.o camera.o pikachu.o
WARNINGS = -g

ifeq ($(OS),Darwin)
	LFLAGS += -lSOIL -ljpeg -framework OpenGL -framework GLUT -framework CoreFoundation
	WARNINGS += -Wno-deprecated
else
	LFLAGS += -lGL -lglut -lGLU
endif

all: main

main: $(OBJECTS)
	g++ $(LFLAGS) $(OBJECTS) Object.cpp Face.cpp Material.cpp Point.cpp PointBase.cpp Vector.cpp jpeg.cpp -o main $(WARNINGS)

main.o: main.cpp
	g++ -c main.cpp $(WARNINGS)

Skybox.o: Skybox.cpp
	g++ -c Skybox.cpp $(WARNINGS)

heightfield.o: heightfield.cpp
	g++ -c heightfield.cpp $(WARNINGS)

camera.o: camera.cpp
	g++ -c camera.cpp $(WARNINGS)

pikachu.o: pikachu.cpp
	g++ -c pikachu.cpp $(WARNINGS)

clean:
	rm -rf *.o *.dSYM main

love:
	clear;
	echo "not war"
