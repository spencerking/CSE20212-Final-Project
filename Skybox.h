#ifndef SKYBOX_H
#define SKYBOX_H

#include <OpenGL/gl.h>

class Skybox {
public:
	Skybox();
	~Skybox();
	void init();
	void render();
private:
	float *points;
	GLuint vbo, vao, skybox;
};

#endif