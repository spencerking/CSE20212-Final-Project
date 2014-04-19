#ifndef SKYBOX_H
#define SKYBOX_H

#include <OpenGL/gl.h>
#include <string>

class Skybox {
public:
	Skybox();
	~Skybox();
	void init(std::string filename);
	void render();
private:
	//float points[];
	GLuint vbo, vao, skybox;
};

#endif