//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html

#include <stdio.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
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
/*
	for (int hMapX = 0; hMapX < hWidth; hMapX++){
		for (int hMapZ = 0; hMapZ < hHeight; hMapZ++){
			printf("%d, %d, %d\n", hMapX, hMapZ, hHeightField[hMapX][hMapZ]);
		}
	}
  */  
	return true;
}


void HeightField::Render(void){
//this will render the heightfield as a series of coordinate points

   // int counter=0;

    glBegin(GL_POINTS);
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
	   // Points[counter].push_back(hMapX);
	   // counter++;
        }
    }
	glEnd();


//renders as triangle strips

/*

	for (int hMapX = 0; hMapX < hmWidth; hMapX++){
		for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
			glBegin(GL_TRIANGLE_STRIP);
				glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);	
				glVertex3f(hMapX, hHeightField[hMapX][hMapZ + 1], hMapZ + 1);	
				glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ], hMapZ);	
				glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ + 1], hMapZ + 1);
			glEnd();
		}
	}
*/



}
