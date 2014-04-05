//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html

#include <stdio.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "heightfield.h"
using namespace std;

//this function open a raw heightmap file and reads it in
//I have no idea how heightmaps are stored, but this works
bool HeightField::Create(char *hFileName, const int hWidth, const int hHeight){
	hmHeight = hHeight;
	hmWidth = hWidth;
	
	FILE *fp;
    
	fp = fopen(hFileName, "rb");
    
	fread(hHeightField, 1, hWidth * hHeight, fp);
    
	fclose(fp);

//prints out all points on the map
/*
	for (int hMapX = 0; hMapX < hWidth; hMapX++){
		for (int hMapZ = 0; hMapZ < hHeight; hMapZ++){
			printf("%d, %d, %d\n", hMapX, hMapZ, hHeightField[hMapX][hMapZ]);
		}
	}
   */

//prints out the max coordinates for each axis
/*
int testx=0;
int testy=0;
int testz=0;
for (int hMapX = 0; hMapX < hWidth; hMapX++){
		for (int hMapZ = 0; hMapZ < hHeight; hMapZ++){
			if (hMapX>testx){
				testx = hMapX;
			}
			if (hMapZ>testz){
				testz = hMapZ;
			}
			if (hHeightField[hMapX][hMapZ]>testy){
				testy = hHeightField[hMapX][hMapZ];
			}
		}
	}

printf("%d, %d, %d\n", testx, testz, testy);*/
	return true;
}


//Collision detection with terrain using bounding spheres method
//this is was originally too memory intensive, the program hangs for extended periods
//we need to subdivide the screen into smaller sections to check
//this way we don't need to check every single point
//the example I'm using from swiftless is 1024 x 1024 so I'm thinking 8 subdivisions
//I'm going to try to make our heightmap as close to this as possible
int HeightField::collisionDetection(float xCamera, float yCamera, float zCamera){

	int counter = 0;
	int q=1;
	float d; //the distance between the camera and the terrain
	int terrainX;
	int terrainY;
	int terrainZ;
	//bounding sphere radii
	terrainRadius = 0.75;
	cameraRadius = 0.75;

		//0-128, what I was doing with counter won't work past the
		//initial section
		if ((xCamera <= 128) && (zCamera <=128)){
			if (counter == 129){
				return 0; //no collision
			}

			terrainX=xPoints[counter];
			terrainY=yPoints[counter];
			terrainZ=zPoints[counter];

			

			d=sqrt(((xCamera-terrainX)*(xCamera-terrainX))+((yCamera-terrainY)*(yCamera-terrainY))+((zCamera-terrainZ)*(zCamera-terrainZ)));

			//check for collision
			if (d <= terrainRadius + cameraRadius){
				cout << "collision detected"<<endl;
			}

			counter++;
		}

}

void HeightField::Render(void){
//this will render the heightfield as a series of coordinate points

    glBegin(GL_POINTS);
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
	    xPoints.push_back(hMapX);
	    yPoints.push_back(hHeightField[hMapX][hMapZ]);
            zPoints.push_back(hMapZ);
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
