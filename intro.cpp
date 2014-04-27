/*
 * intro.cpp
 * created by hannah Porter
 * 4/23/2014
 *
 */

#include "intro.h"
#include <iostream>

GLuint tex_2d;

Intro::Intro() {
	
}

void Intro::initTitlescreen() {
	glEnable(GL_TEXTURE_2D);
	tex_2d = SOIL_load_OGL_texture
		("pug.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
		SOIL_FLAG_INVERT_Y);

	if (0==tex_2d) {
		std::cout << "SOIL loading error" 
			<< SOIL_last_result() << std::endl;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Intro::renderTitlescreen() {
	
	GLfloat vertices[] = { 5.0f,5.0f,25.0f, 5.0f,5.0f,5.0f, 5.0f,65.0f,5.0f, 65.0f,5.0f,25.0f,
		     5.0f,45.0f,25.0f, 5.0f,45.0f,5.0f, 65.0f,45.0f,5.0f, 65.0f,45.0f,25.0f,
		     5.0f,5.0f,25.0f, 5.0f,45.0f,25.0f, 65.0f,45.0f,25.0f, 65.0f,5.0f,25.0f,
		     5.0f,45.0f,5.0f, 5.0f,5.0f,5.0f, 5.0f,65.0f,5.0f, 65.0f,45.0f,5.0f,
		     65.0f,45.0f,5.0f, 65.0f,45.0f,25.0f, 65.0f,5.0f,25.0f, 5.0f,65.0f,5.0f,
		     5.0f,45.0f,5.0f, 5.0f,45.0f,25.0f, 5.0f,5.0f,25.0f, 5.0f,5.0f,5.0f };
	
	GLfloat texcoords[] = { 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
		      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0 };

	GLuint indices[] = { 0,1,2,3, 4,5,6,7, 8,9,10,11, 12,13,14,15,
		    16,17,18,19, 20,21,22,23 }; 

	glEnableClientState(GL_VERTEX_ARRAY | GL_TEXTURE_COORD_ARRAY | GL_INDEX_ARRAY);	
	glColor3f(1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D, tex_2d);

	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY | GL_TEXTURE_COORD_ARRAY | GL_INDEX_ARRAY);
}

void Intro::loadTitleImage() {
	
}


