//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html

#include <stdio.h>
#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif
#include <iostream>
#include <vector>
#include <iterator>
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
//the example I'm using from swiftless is 1024 x 1024 so I'm thinking 64 subdivisions
//I'm going to try to make our heightmap as close to this as possible
int HeightField::collisionDetection(float xCamera, float yCamera, float zCamera){

	int counter = 0;
    int zero_count = 0;
	int q=1;
	float d; //the distance between the camera and the terrain
	int terrainX;
	int terrainY;
	int terrainZ;

	vector<int>::const_iterator xvecIter;
    
    //I don't have my notebook with me at the moment, I just need to change numbers here
    //also need to change the function that reads them in
    //Square 1 (bottom left)
    /*
    if (xCamera > 768 && xCamera < 897 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints1.end()){
            
            terrainX=xPoints1[counter];
            terrainY=yPoints1[counter];
            terrainZ=zPoints1[counter];
            
			
            
            d=sqrt(((xCamera-terrainX)*(xCamera-terrainX))+((yCamera-terrainY)*(yCamera-terrainY))+((zCamera-terrainZ)*(zCamera-terrainZ)));

            //check for collision
            if (d <= 10){ //might want to increase this
                cout << "collision detected"<<endl;
                return 1;
            }
            
            xvecIter++;
            counter++;
            if (terrainX==0 && terrainY==0 && terrainZ==0){
                zero_count++;
                if (zero_count>1){
                    return 0;
                }
            }
            
        }
        
    }*/
    
    //Square 2 (above square 1)
    /*
    if (xCamera > 768 && xCamera < 897 && zCamera > 256 && zCamera <385){
       
        while (xvecIter != xPoints2.end()){
            
            terrainX=xPoints2[counter];
            terrainY=yPoints2[counter];
            terrainZ=zPoints2[counter];
            
			
            
            d=sqrt(((xCamera-terrainX)*(xCamera-terrainX))+((yCamera-terrainY)*(yCamera-terrainY))+((zCamera-terrainZ)*(zCamera-terrainZ)));

            //check for collision
            if (d <= 10){ //might want to increase this
                cout << "collision detected"<<endl;
                return 1;
            }
            
            xvecIter++;
            counter++;
            if (terrainX==0 && terrainY==0 && terrainZ==0){
                return 0;
            }
            
        }
        
    }*/
    

		//system("clear");
		//769-896
		if (xCamera > 768 && xCamera < 897 && zCamera > 256 && zCamera <385){
			
			//cout << "test896" <<endl;
			while (xvecIter != xPoints896.end()){ 

				terrainX=xPoints896[counter];
				terrainY=yPoints896[counter];
				terrainZ=zPoints896[counter];

			

				d=sqrt(((xCamera-terrainX)*(xCamera-terrainX))+((yCamera-terrainY)*(yCamera-terrainY))+((zCamera-terrainZ)*(zCamera-terrainZ)));
				//cout << "d is "<< d<<endl;
				//check for collision
				if (d <= 10){ //might want to increase this
					cout << "collision detected"<<endl;
					return 1;
				}

				xvecIter++;
				counter++;
				if (terrainX==0 && terrainY==0 && terrainZ==0){
					return 0;
				}

			}

		}

}

void HeightField::Render(void){
//this will render the heightfield as a series of coordinate points

    int counter=0;

    glBegin(GL_POINTS);
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
		if (hMapX > 768 && hMapX < 897 && hMapZ > 256 && hMapZ <385){
			if (counter%5==0){
				xPoints896.push_back(hMapX);
				yPoints896.push_back(hHeightField[hMapX][hMapZ]);
          			zPoints896.push_back(hMapZ);
			}
		}
		counter++;
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
