#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <ostream>
#include "camera.h"

using namespace std;


//default constructor
camera::camera(){

    fileName = "0";

}

//string incrementer
//help from: http://rosettacode.org/wiki/Increment_a_numerical_string#C.2B.2B
void camera::stringIncrement(std::string& s){
    std::string::reverse_iterator iter = s.rbegin(), end = s.rend();
    int carry = 1;
    while (carry && iter != end){
        int value = (*iter - '0') + carry;
        carry = (value/10);
        *iter = '0'+(value%10);
        ++iter;
    }
    if (carry){
        s.insert(0, "1");
    }
    
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

//sets up the filename for the screenshot function
void camera::setupScreenshot(){

    char file[30];
    strcpy(file, "file");
    
    camera::stringIncrement(fileName);
    const char *c = fileName.c_str();
    
    char str[15];
    strcpy(str, c);
    strcat(str, ".tga");
    strcat(file, str);

	camera::screenshot(file, 500, 500);
	

}

