//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html

#include <stdio.h>
#include <GL/gl.h>

#include "heightfield.h"

//this function open a raw heightmap file and reads it in
//I have no idea how heightmaps are stored, but this works
bool HeightField::Create(char *hFileName, const int hWidth, const int hHeight){
	hmHeight = hHeight;
	hmWidth = hWidth;
	
	FILE *fp;
    
	fp = fopen(hFileName, "rb");
    
	fread(hHeightField, 1, hWidth * hHeight, fp);
    
	fclose(fp);
    
	return true;
}

//this will render the heightfield as a series of coordinate points
//this can be smoothed out by using triangles, addressed later in swiftless
void HeightField::Render(void){
	glBegin(GL_POINTS);
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
        }
    }
	glEnd();
}