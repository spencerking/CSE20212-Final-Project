#ifndef JPEG_H
#define JPEG_H

#include <stdio.h>
#include <jpeglib.h>
#include <string>
//#pragma comment(lib, "jpeg.lib")

struct jpegtexture {
	unsigned int rowSpan;
	unsigned int sizeX;
	unsigned int sizeY;
	unsigned char *data;
};

jpegtexture *loadJpeg(const char *srFileName);

void textureJpeg(unsigned int tTexture[], std::string strFileName, int ID);
void skyboxJpeg(unsigned int tTexture[], std::string strFileName, int ID);

#endif