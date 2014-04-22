#ifndef SKYBOX_H
#define SKYBOX_H

#ifdef __APPLE__
   #include <OpenGL/gl.h>
#else
   #include <GL/gl.h>
#endif  

class Skybox {
public:
	Skybox();
	void init();
	void render();
private:
	//float *points;
	//GLuint vbo, vao, skybox;
	GLuint skybox;
};

#endif
