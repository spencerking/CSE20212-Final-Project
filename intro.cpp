#include "intro.h"
#include <SOIL/soil.h>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

Intro::Intro() {

	size = 50.0;

	float s=size/2;
	
	GLfloat tempVertices[] = {  -s,-s,s,
				s,-s,s,
				s,s,s,
				-s,s,s,

				-s,s,s,
				s,s,s,
				s,s,-s,
				-s,s,-s,
				
				s,-s,-s,
				-s,-s,-s,
				-s,s,-s,
				s,s,-s,

				-s,-s,-s,
				s,-s,-s,
				s,-s,s,
				-s,-s,s,
				
				-s,-s,-s,
				-s,-s,s,
				-s,s,s,
				-s,s,-s,
				
				s,-s,s,
				s,-s,-s,
				s,s,-s,
				s,s,s };

	for(int i=0; i<72; i++) {
		vertices[i] = tempVertices[i];
	}

	GLfloat tempTexcoords[48] = { 0.0,0.0,
				      1.0, 0.0,
				      1.0, 1.0,
				      0.0, 1.0 };

	for (int i=0; i<8; i++) {
		texcoords[i]=tempTexcoords[i];
	}

	for (int i=1; i<6; i++) {
		memcpy(&texcoords[i*4*2], &texcoords[0], 2*4*sizeof(GLfloat));
	}

	GLshort tempIndices[36] = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11,
		8, 12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20};

	for (int i=0; i<32; i++) {
		indices[i]=tempIndices[i];
	}	

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex_2d);
	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int intSize = 500;
	unsigned char* image =
		SOIL_load_image("img.png", &intSize, &intSize, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, intSize, intSize, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	
}


void Intro::renderTitlescreen() {
	cout << "Time to render the CUBE" << endl;
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glColor3f(1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glVertexPointer(3, GL_FLOAT, 0, vertices);

	cout << "pointers" << endl;

	glPushMatrix();
	glTranslatef(800.0, 351.0, 100.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
        glDrawElements(GL_TRIANGLES, 36, GL_SHORT, indices);
	glFlush();
	//glutSwapBuffers();
	glPopMatrix();

	cout << "elements drawn" << endl;
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisable(GL_TEXTURE_2D);

	cout << "DONE RENDERING" << endl;

}



