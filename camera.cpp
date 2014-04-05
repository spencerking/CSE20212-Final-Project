#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include "camera.h"

using namespace std;


//default constructor
camera::camera(){

	screenCounter = 0;

}


//takes a screenshot and outputs it as an image file
//code taken from:
//https://www.opengl.org/discussion_boards/showthread.php/158514-capturing-the-OpenGL-output-to-a-image-file
void camera::screenshot(char *tga_file, short W, short H) {
	FILE   *out = fopen(tga_file, "w");
	char   pixel_data[3*W*H];
	short  TGAhead[] = {0, 2, 0, 0, 0, 0, W, H, 24};
 
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, W, H, GL_BGR, GL_UNSIGNED_BYTE, pixel_data);
	fwrite(TGAhead, sizeof(TGAhead), 1, out);
	fwrite(pixel_data, 3*W*H, 1, out);
	fclose(out); 
}

//ideally this function will call screenshot and increment the number of the file
//e.g. first one is file1, next is file2, etc.
//I'm blanking on how to change the char* based on the int counter
void camera::setupScreenshot(){

	screenCounter++;

	char *fileName; 	

	camera::screenshot(fileName, 1500, 1500);
	

}

