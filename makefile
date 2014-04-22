OS := $(shell uname)
OBJECTS = main.o Skybox.o Heightfield.o Camera.o Sound.o Pikachu.o Xatu.o Wooper.o Raichu.o
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

Pikachu.o: Pikachu.cpp
	g++ -c Pikachu.cpp $(WARNINGS)

Xatu.o: Xatu.cpp
	g++ -c Xatu.cpp $(WARNINGS)

Wooper.o: Wooper.cpp
	g++ -c Wooper.cpp $(WARNINGS)

Raichu.o: Raichu.cpp
	g++ -c Raichu.cpp $(WARNINGS)

clean:
	rm -rf *.o *.dSYM main

love:
	clear;
	echo "not war"
