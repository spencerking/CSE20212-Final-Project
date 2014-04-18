OS := $(shell uname)
OBJECTS = main.o heightfield.o camera.o
WARNINGS = -g

ifeq ($(OS),Darwin)
	LFLAGS +=  -framework OpenGL -framework GLUT -framework CoreFoundation
	WARNINGS += -Wno-deprecated
else
	LFLAGS += -lGL -lglut -lGLU
endif

all: main

main: $(OBJECTS)
	g++ $(OBJECTS) -o main $(WARNINGS) $(LFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(WARNINGS)

heightfield.o: heightfield.cpp
	g++ -c heightfield.cpp $(WARNINGS)

camera.o: camera.cpp
	g++ -c camera.cpp $(WARNINGS)

clean: main
	rm -rf *.o main

love:
	clear;
	echo "not war"
