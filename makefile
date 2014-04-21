OS := $(shell uname)
OBJECTS = main.o Skybox.o Heightfield.o Camera.o Sound.o Pikachu.o Xatu.o Wooper.o
WARNINGS = -g

ifeq ($(OS),Darwin)
	LFLAGS += -lSOIL -ljpeg -lfmodex -framework OpenGL -framework GLUT -framework CoreFoundation
	WARNINGS += -Wno-deprecated
else
	LFLAGS += -lGL -lglut -lGLU -lm
endif

all: main

main: $(OBJECTS)
	g++ $(LFLAGS) $(OBJECTS) Object.cpp Face.cpp Material.cpp Point.cpp PointBase.cpp Vector.cpp jpeg.cpp -o main $(WARNINGS)

main.o: main.cpp
	g++ -c main.cpp $(WARNINGS)

Skybox.o: Skybox.cpp
	g++ -c Skybox.cpp $(WARNINGS)

Heightfield.o: Heightfield.cpp
	g++ -c Heightfield.cpp $(WARNINGS)

Camera.o: Camera.cpp
	g++ -c Camera.cpp $(WARNINGS)

Sound.o: Sound.cpp
	g++ -c Sound.cpp $(WARNINGS)

Pikachu.o: Pikachu.cpp
	g++ -c Pikachu.cpp $(WARNINGS)

Xatu.o: Xatu.cpp
	g++ -c Xatu.cpp $(WARNINGS)

Wooper.o: Wooper.cpp
	g++ -c Wooper.cpp $(WARNINGS)

clean:
	rm -rf *.o *.dSYM main

love:
	clear;
	echo "not war"
