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
}

void Intro::renderTitlescreen() {
	
	GLfloat vertices[] = { -0.5f, 0.0f, 0.5f,   0.5f, 0.0f, 0.5f,   0.5f, 1.0f, 0.5f,  -0.5f, 1.0f, 0.5f,
  			       -0.5f, 1.0f, -0.5f,  0.5f, 1.0f, -0.5f,  0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f,
  			       0.5f, 0.0f, 0.5f,   0.5f, 0.0f, -0.5f,  0.5f, 1.0f, -0.5f,  0.5f, 1.0f, 0.5f,
  			       -0.5f, 0.0f, -0.5f,  -0.5f, 0.0f, 0.5f,  -0.5f, 1.0f, 0.5f, -0.5f, 1.0f, -0.5f };
	
	GLfloat texcoords[] = { 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                               0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                               0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                               0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0 };

	GLuint indices[] = {0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0,
                                  8,9,10,11, 12,13,14,15};

	//glEnableClientState(GL_VERTEX_ARRAY | GL_TEXTURE_COORD_ARRAY | GL_INDEX_ARRAY);
        glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glVertexPointer(3, GL_FLOAT, 0, vertices);

        //glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_TEXTURE_2D);

	glTranslatef(908.833,26.8181,400.551);


	/*glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY | GL_TEXTURE_COORD_ARRAY | GL_INDEX_ARRAY);*/
}

void Intro::loadTitleImage() {
	
}


