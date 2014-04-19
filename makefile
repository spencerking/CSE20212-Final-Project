OS := $(shell uname)
OBJECTS = main.o heightfield.o camera.o
WARNINGS = -g

ifeq ($(OS),Darwin)
	LFLAGS += -lSOIL -ljpeg -framework OpenGL -framework GLUT -framework CoreFoundation
	WARNINGS += -Wno-deprecated
else
	LFLAGS += -lGL -lglut -lGLU
endif

all: main

main: $(OBJECTS)
	g++ $(LFLAGS) $(OBJECTS) -o main $(WARNINGS)

main.o: main.cpp
	g++ -c main.cpp $(WARNINGS)

heightfield.o: heightfield.cpp
	g++ -c heightfield.cpp $(WARNINGS)

camera.o: camera.cpp
	g++ -c camera.cpp $(WARNINGS)

#Object.o: Object.cpp Point.cpp Vector.cpp Material.cpp Pointbase.cpp Face.cpp
#	g++ -c Object.cpp Point.cpp Vector.cpp Material.cpp Pointbase.cpp Face.cpp $(WARNINGS)

clean:
	rm -rf *.o main

love:
	clear;
	echo "not war"
