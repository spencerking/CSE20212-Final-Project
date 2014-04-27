OS := $(shell uname)
OBJECTS = main.o Skybox.o Heightfield.o Camera.o Sound.o GameController.o models.o intro.o
WARNINGS = -g

ifeq ($(OS),Darwin)
	LFLAGS += -lSOIL -ljpeg -lfmodex -framework OpenGL -framework GLUT -framework CoreFoundation
	WARNINGS += -Wno-deprecated
else

	SOIL = /afs/nd.edu/user5/hporter/CSE20212-Final-Project/soil
        ifneq "$(wildcard $(SOIL))" ""
		INCPATH += -I$(SOIL)/include
             	LIBPATH += -L$(SOIL)/lib -Wl,--rpath -Wl,$(SOIL)/lib
		LFLAGS += -lSOIL
	endif

	LFLAGS += -lm -lglut -lGL -lGLU -ljpeg

	FMOD = /afs/nd.edu/user5/hporter/CSE20212-Final-Project/fmod
        ifneq "$(wildcard $(FMOD))" ""
                INCPATH += -I$(FMOD)/include
                LIBPATH += -L$(FMOD)/lib -Wl,--rpath -Wl,$(FMOD)/lib
                LFLAGS += -lfmodex64
        endif


endif



all: main

main: $(OBJECTS)
	g++ $(OBJECTS) $(INCPATH) Object.cpp Face.cpp Material.cpp Point.cpp PointBase.cpp Vector.cpp jpeg.cpp -o main $(LIBPATH) $(LFLAGS) $(WARNINGS)

main.o: main.cpp
	g++ -c $(INCPATH) main.cpp $(LIBPATH) $(LFLAGS) $(WARNINGS)

Skybox.o: Skybox.cpp
	g++ -c $(INCPATH) Skybox.cpp $(LIBPATH) $(LFLAGS) $(WARNINGS)

Heightfield.o: Heightfield.cpp
	g++ -c Heightfield.cpp $(WARNINGS)

Camera.o: Camera.cpp
	g++ -c Camera.cpp $(WARNINGS)

Sound.o: Sound.cpp
	g++ -c $(INCPATH) Sound.cpp $(LIBPATH) $(LFLAGS) $(WARNINGS)

GameController.o: GameController.cpp
	g++ -c $(INCPATH) GameController.cpp $(LIBPATH) $(LFLAGS) $(WARNINGS)

Models.o: models.cpp
	g++ -c models.cpp $(WARNINGS)

intro.o: intro.cpp
	g++ -c $(INCPATH) intro.cpp $(LIBPATH) $(LFLAGS) $(WARNINGS)

clean:
	rm -rf *.o *.dSYM main

love:
	clear;
	echo "not war"
