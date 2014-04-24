//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html

#include <stdio.h>
#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#define GL_GLEXT_PROTOTYPES
	#include <GL/gl.h>
#endif
#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include "Heightfield.h"
#include "jpeg.h"
using namespace std;

bool HeightField::makeVBO(void) {
    glGenBuffersARB(1, &vhVBOVertices);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 3 * sizeof(float), vhVertices, GL_STATIC_DRAW_ARB);

    glGenBuffersARB(1, &vhVBOTexCoords);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
    glBufferDataARB(GL_ARRAY_BUFFER_ARB, vhVertexCount * 2 * sizeof(float), vhTexCoords, GL_STATIC_DRAW_ARB);

    delete [] vhVertices;
    vhVertices = NULL;

    delete [] vhTexCoords;
    vhTexCoords = NULL;

    return true;
}

//this function open a raw heightmap file and reads it in
//I have no idea how heightmaps are stored, but this works
bool HeightField::init(const char *hFileName, const int hWidth, const int hHeight, int hLOD){
	hmHeight = hHeight;
	hmWidth = hWidth;
    hmLOD = hLOD;
	
	FILE *fp;
    
	fp = fopen(hFileName, "rb");
    
	fread(hHeightField, 1, hWidth * hHeight, fp);
    
	fclose(fp);

    vhVertexCount = (int)(hHeight * hHeight * 6) / (hLOD * hLOD);
    vhVertices = new Vert[vhVertexCount];
    vhTexCoords = new TexCoord[vhVertexCount];

    // Temp
    int nIndex = 0;
    float flX;
    float flZ;

    for (int hMapX = 0; hMapX < hmWidth; hMapX+=hLOD){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ+=hLOD){
            for (int nTri = 0; nTri < 6; nTri++){
                flX = (float)hMapX + ((nTri == 1 || nTri == 2 || nTri == 5) ? hLOD : 0);
                flZ = (float)hMapZ + ((nTri == 2 || nTri == 4 || nTri == 5) ? hLOD : 0);

                vhVertices[nIndex].x = flX;
                vhVertices[nIndex].y = hHeightField[(int)flX][(int)flZ];
                vhVertices[nIndex].z = flZ;

                vhTexCoords[nIndex].u = flX / 1024;
                vhTexCoords[nIndex].v = flZ / 1024;
                nIndex++;
            }
        }
    }

    textureJpeg(texture, "Heightfield/terrain.jpg", 0); // Load texture into array


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
    HeightField::makeVBO();
	return true;
}


//Collision detection with terrain using bounding spheres method
//this is was originally too memory intensive, the program would hang for extended periods
//we decided to subdivide the screen into smaller sections to check
//this way we don't need to check every single point every time the user moves
int HeightField::collisionDetection(float xCamera, float yCamera, float zCamera){

	int counter = 0;
    int zero_count = 0;
	float d; //the distance between the camera and the terrain
    
    //coordinates for each point in the terrain
	int terrainX;
	int terrainY;
	int terrainZ;

	vector<int>::const_iterator xvecIter;
    
    
    //Square 1 (bottom left)
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 0 && zCamera <129){
        
        while (xvecIter != xPoints1.end()){
            
            //sets the coordinates from the vectors
            terrainX=xPoints1[counter];
            terrainY=yPoints1[counter];
            terrainZ=zPoints1[counter];
            
			
            //calculates the distance between the camera and a point
            d=sqrt(((xCamera-terrainX)*(xCamera-terrainX))+((yCamera-terrainY)*(yCamera-terrainY))+((zCamera-terrainZ)*(zCamera-terrainZ)));

            //check for collision
            if (d <= 10){ //might want to increase this
                cout << "collision detected"<<endl;
                return 1;
            }
            
            //increment the iterator and the count
            xvecIter++;
            counter++;
            
            //check is (0,0,0) appears more than once
            //sometimes this point appears endlessly and we are not sure why
            //this function breaks the loop should it appear more than it should
            if (terrainX==0 && terrainY==0 && terrainZ==0){
                zero_count++;
                if (zero_count>1){
                    return 0;
                }
            }
            
        }
        
    }
    
    //Square 2 (above square 1)
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 0 && zCamera <129){
       
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
        
    }
    
    
    //Square 3
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 0 && zCamera <129){
        
        while (xvecIter != xPoints3.end()){
            
            terrainX=xPoints3[counter];
            terrainY=yPoints3[counter];
            terrainZ=zPoints3[counter];
            
			
            
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
    
    //Square 4
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 0 && zCamera <129){
        
        while (xvecIter != xPoints4.end()){
            
            terrainX=xPoints4[counter];
            terrainY=yPoints4[counter];
            terrainZ=zPoints4[counter];
            
			
            
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
    
    //Square 5
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 0 && zCamera <129){
        
        while (xvecIter != xPoints5.end()){
            
            terrainX=xPoints5[counter];
            terrainY=yPoints5[counter];
            terrainZ=zPoints5[counter];
            
			
            
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
    
    //Square 6
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 0 && zCamera <129){
        
        while (xvecIter != xPoints6.end()){
            
            terrainX=xPoints6[counter];
            terrainY=yPoints6[counter];
            terrainZ=zPoints6[counter];
            
			
            
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
    
    //Square 7
    
    if (xCamera > 768 && xCamera < 897 && zCamera > 0 && zCamera <129){
        
        while (xvecIter != xPoints7.end()){
            
            terrainX=xPoints7[counter];
            terrainY=yPoints7[counter];
            terrainZ=zPoints7[counter];
            
			
            
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
    
    //Square 8
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 0 && zCamera <129){
        
        while (xvecIter != xPoints8.end()){
            
            terrainX=xPoints8[counter];
            terrainY=yPoints8[counter];
            terrainZ=zPoints8[counter];
            
			
            
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
    
    //Square 9
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints9.end()){
            
            terrainX=xPoints9[counter];
            terrainY=yPoints9[counter];
            terrainZ=zPoints9[counter];
            
			
            
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
    
    //Square 10
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints10.end()){
            
            terrainX=xPoints10[counter];
            terrainY=yPoints10[counter];
            terrainZ=zPoints10[counter];
            
			
            
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
    
    //Square 11
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints11.end()){
            
            terrainX=xPoints11[counter];
            terrainY=yPoints11[counter];
            terrainZ=zPoints11[counter];
            
			
            
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
    
    //Square 12
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints12.end()){
            
            terrainX=xPoints12[counter];
            terrainY=yPoints12[counter];
            terrainZ=zPoints12[counter];
            
			
            
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
    
    //Square 13
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints13.end()){
            
            terrainX=xPoints13[counter];
            terrainY=yPoints13[counter];
            terrainZ=zPoints13[counter];
            
			
            
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
    
    //Square 14
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints14.end()){
            
            terrainX=xPoints14[counter];
            terrainY=yPoints14[counter];
            terrainZ=zPoints14[counter];
            
			
            
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
    
    //Square 15
    
    if (xCamera > 768 && xCamera < 897 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints15.end()){
            
            terrainX=xPoints15[counter];
            terrainY=yPoints15[counter];
            terrainZ=zPoints15[counter];
            
			
            
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
    
    //Square 16
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 128 && zCamera <257){
        
        while (xvecIter != xPoints16.end()){
            
            terrainX=xPoints16[counter];
            terrainY=yPoints16[counter];
            terrainZ=zPoints16[counter];
            
			
            
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
    
    
    //Square 17
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints17.end()){
            
            terrainX=xPoints17[counter];
            terrainY=yPoints17[counter];
            terrainZ=zPoints17[counter];
            
			
            
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
    
    //Square 18
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints18.end()){
            
            terrainX=xPoints18[counter];
            terrainY=yPoints18[counter];
            terrainZ=zPoints18[counter];
            
			
            
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
    
    //Square 19
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints19.end()){
            
            terrainX=xPoints19[counter];
            terrainY=yPoints19[counter];
            terrainZ=zPoints19[counter];
            
			
            
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
    
    //Square 20
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints20.end()){
            
            terrainX=xPoints20[counter];
            terrainY=yPoints20[counter];
            terrainZ=zPoints20[counter];
            
			
            
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
    
    //Square 21
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints21.end()){
            
            terrainX=xPoints21[counter];
            terrainY=yPoints21[counter];
            terrainZ=zPoints21[counter];
            
			
            
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
    
    //Square 22
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints22.end()){
            
            terrainX=xPoints22[counter];
            terrainY=yPoints22[counter];
            terrainZ=zPoints22[counter];
            
			
            
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
    
    //Square 23
    //system("clear");
    //769-896
    if (xCamera > 768 && xCamera < 897 && zCamera > 256 && zCamera <385){
        
        //cout << "test896" <<endl;
        while (xvecIter != xPoints23.end()){
            
            terrainX=xPoints23[counter];
            terrainY=yPoints23[counter];
            terrainZ=zPoints23[counter];
            
			
            
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
    
    //Square 24
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 256 && zCamera <385){
        
        while (xvecIter != xPoints24.end()){
            
            terrainX=xPoints24[counter];
            terrainY=yPoints24[counter];
            terrainZ=zPoints24[counter];
            
			
            
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
    
    //Square 25
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 384 && zCamera <513){
        
        while (xvecIter != xPoints25.end()){
            
            terrainX=xPoints25[counter];
            terrainY=yPoints25[counter];
            terrainZ=zPoints25[counter];
            
			
            
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
    
    //Square 26
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 384 && zCamera <513){
        
        while (xvecIter != xPoints26.end()){
            
            terrainX=xPoints26[counter];
            terrainY=yPoints26[counter];
            terrainZ=zPoints26[counter];
            
			
            
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
    
    //Square 27
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 384 && zCamera <513){
        
        while (xvecIter != xPoints27.end()){
            
            terrainX=xPoints27[counter];
            terrainY=yPoints27[counter];
            terrainZ=zPoints27[counter];
            
			
            
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
    
    //Square 28
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 384 && zCamera <513){
        
        while (xvecIter != xPoints28.end()){
            
            terrainX=xPoints28[counter];
            terrainY=yPoints28[counter];
            terrainZ=zPoints28[counter];
            
			
            
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
    
    //Square 29
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 384 && zCamera <513){
        
        while (xvecIter != xPoints29.end()){
            
            terrainX=xPoints29[counter];
            terrainY=yPoints29[counter];
            terrainZ=zPoints29[counter];
            
			
            
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
    
    //Square 30
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 384 && zCamera <513){
        
        while (xvecIter != xPoints30.end()){
            
            terrainX=xPoints30[counter];
            terrainY=yPoints30[counter];
            terrainZ=zPoints30[counter];
            
			
            
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
    
    //Square 31
    
    if (xCamera > 768 && xCamera < 897 && zCamera > 384 && zCamera <513){
        
        //cout << "test896" <<endl;
        while (xvecIter != xPoints31.end()){
            
            terrainX=xPoints31[counter];
            terrainY=yPoints31[counter];
            terrainZ=zPoints31[counter];
            
			
            
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
    
    //Square 32
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 384 && zCamera <513){
        
        while (xvecIter != xPoints32.end()){
            
            terrainX=xPoints32[counter];
            terrainY=yPoints32[counter];
            terrainZ=zPoints32[counter];
            
			
            
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
    
    //Square 33
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints33.end()){
            
            terrainX=xPoints33[counter];
            terrainY=yPoints33[counter];
            terrainZ=zPoints33[counter];
            
			
            
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
    
    //Square 34
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints34.end()){
            
            terrainX=xPoints34[counter];
            terrainY=yPoints34[counter];
            terrainZ=zPoints34[counter];
            
			
            
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
    
    //Square 35
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints35.end()){
            
            terrainX=xPoints35[counter];
            terrainY=yPoints35[counter];
            terrainZ=zPoints35[counter];
            
			
            
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
    
    //Square 36
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints36.end()){
            
            terrainX=xPoints36[counter];
            terrainY=yPoints36[counter];
            terrainZ=zPoints36[counter];
            
			
            
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
    
    //Square 37
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints37.end()){
            
            terrainX=xPoints37[counter];
            terrainY=yPoints37[counter];
            terrainZ=zPoints37[counter];
            
			
            
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
    
    //Square 38
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints38.end()){
            
            terrainX=xPoints38[counter];
            terrainY=yPoints38[counter];
            terrainZ=zPoints38[counter];
            
			
            
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
    
    //Square 39
    
    if (xCamera > 768 && xCamera < 897 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints39.end()){
            
            terrainX=xPoints39[counter];
            terrainY=yPoints39[counter];
            terrainZ=zPoints39[counter];
            
			
            
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
    
    //Square 40
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 512 && zCamera <641){
        
        while (xvecIter != xPoints40.end()){
            
            terrainX=xPoints40[counter];
            terrainY=yPoints40[counter];
            terrainZ=zPoints40[counter];
            
			
            
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
    
    
    //Square 41
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints41.end()){
            
            terrainX=xPoints41[counter];
            terrainY=yPoints41[counter];
            terrainZ=zPoints41[counter];
            
			
            
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
    
    //Square 42
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints42.end()){
            
            terrainX=xPoints42[counter];
            terrainY=yPoints42[counter];
            terrainZ=zPoints42[counter];
            
			
            
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
    
    //Square 43
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints43.end()){
            
            terrainX=xPoints43[counter];
            terrainY=yPoints43[counter];
            terrainZ=zPoints43[counter];
            
			
            
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
    
    //Square 44
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints44.end()){
            
            terrainX=xPoints44[counter];
            terrainY=yPoints44[counter];
            terrainZ=zPoints44[counter];
            
			
            
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
    
    //Square 45
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints45.end()){
            
            terrainX=xPoints45[counter];
            terrainY=yPoints45[counter];
            terrainZ=zPoints45[counter];
            
			
            
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
    
    //Square 46
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints46.end()){
            
            terrainX=xPoints46[counter];
            terrainY=yPoints46[counter];
            terrainZ=zPoints46[counter];
            
			
            
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
    
    //Square 47
    
    if (xCamera > 768 && xCamera < 897 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints47.end()){
            
            terrainX=xPoints47[counter];
            terrainY=yPoints47[counter];
            terrainZ=zPoints47[counter];
            
			
            
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
    
    //Square 48
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 640 && zCamera <769){
        
        while (xvecIter != xPoints48.end()){
            
            terrainX=xPoints48[counter];
            terrainY=yPoints48[counter];
            terrainZ=zPoints48[counter];
            
			
            
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
    
    //Square 49
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints49.end()){
            
            terrainX=xPoints49[counter];
            terrainY=yPoints49[counter];
            terrainZ=zPoints49[counter];
            
			
            
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
    
    //Square 50
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints50.end()){
            
            terrainX=xPoints50[counter];
            terrainY=yPoints50[counter];
            terrainZ=zPoints50[counter];
            
			
            
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
    
    //Square 51
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints51.end()){
            
            terrainX=xPoints51[counter];
            terrainY=yPoints51[counter];
            terrainZ=zPoints51[counter];
            
			
            
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
    
    //Square 52
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints52.end()){
            
            terrainX=xPoints52[counter];
            terrainY=yPoints52[counter];
            terrainZ=zPoints52[counter];
            
			
            
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
    
    //Square 53
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints53.end()){
            
            terrainX=xPoints53[counter];
            terrainY=yPoints53[counter];
            terrainZ=zPoints53[counter];
            
			
            
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
    
    //Square 54
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints54.end()){
            
            terrainX=xPoints54[counter];
            terrainY=yPoints54[counter];
            terrainZ=zPoints54[counter];
            
			
            
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
    
    //Square 55
    
    if (xCamera > 768 && xCamera < 897 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints55.end()){
            
            terrainX=xPoints55[counter];
            terrainY=yPoints55[counter];
            terrainZ=zPoints55[counter];
            
			
            
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
    
    //Square 56
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 768 && zCamera <897){
        
        while (xvecIter != xPoints56.end()){
            
            terrainX=xPoints56[counter];
            terrainY=yPoints56[counter];
            terrainZ=zPoints56[counter];
            
			
            
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
    
    //Square 57
    
    if (xCamera > 0 && xCamera < 129 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints57.end()){
            
            terrainX=xPoints57[counter];
            terrainY=yPoints57[counter];
            terrainZ=zPoints57[counter];
            
			
            
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
    
    //Square 58
    
    if (xCamera > 128 && xCamera < 257 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints58.end()){
            
            terrainX=xPoints58[counter];
            terrainY=yPoints58[counter];
            terrainZ=zPoints58[counter];
            
			
            
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
    
    //Square 59
    
    if (xCamera > 256 && xCamera < 385 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints59.end()){
            
            terrainX=xPoints59[counter];
            terrainY=yPoints59[counter];
            terrainZ=zPoints59[counter];
            
			
            
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
    
    //Square 60
    
    if (xCamera > 384 && xCamera < 513 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints60.end()){
            
            terrainX=xPoints60[counter];
            terrainY=yPoints60[counter];
            terrainZ=zPoints60[counter];
            
			
            
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
    
    //Square 61
    
    if (xCamera > 512 && xCamera < 641 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints61.end()){
            
            terrainX=xPoints61[counter];
            terrainY=yPoints61[counter];
            terrainZ=zPoints61[counter];
            
			
            
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
    
    //Square 62
    
    if (xCamera > 640 && xCamera < 769 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints62.end()){
            
            terrainX=xPoints62[counter];
            terrainY=yPoints62[counter];
            terrainZ=zPoints62[counter];
            
			
            
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
    
    //Square 63
    
    if (xCamera > 768 && xCamera < 897 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints63.end()){
            
            terrainX=xPoints63[counter];
            terrainY=yPoints63[counter];
            terrainZ=zPoints63[counter];
            
			
            
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
    
    //Square 64
    
    if (xCamera > 896 && xCamera < 1025 && zCamera > 896 && zCamera <1025){
        
        while (xvecIter != xPoints64.end()){
            
            terrainX=xPoints64[counter];
            terrainY=yPoints64[counter];
            terrainZ=zPoints64[counter];
            
			
            
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

    return 0;
}

void HeightField::render(void){
//this will render the heightfield as a series of coordinate points

    counter1=0;

    // Collision detection points
    // glBegin(GL_POINTS);
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
         //   glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
            //Square 1
            //this series of if statements reads in the points into the appropriate vectors
            if (hMapX > 0 && hMapX < 129 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints1.push_back(hMapX);
                    yPoints1.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints1.push_back(hMapZ);
                }
            }
            //Square 2
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints2.push_back(hMapX);
                    yPoints2.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints2.push_back(hMapZ);
                }
            }
            //Square 3
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints3.push_back(hMapX);
                    yPoints3.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints3.push_back(hMapZ);
                }
            }
            //Square 4
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints4.push_back(hMapX);
                    yPoints4.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints4.push_back(hMapZ);
                }
            }
            //Square 5
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints5.push_back(hMapX);
                    yPoints5.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints5.push_back(hMapZ);
                }
            }
            //Square 6
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints6.push_back(hMapX);
                    yPoints6.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints6.push_back(hMapZ);
                }
            }
            //Square 7
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints7.push_back(hMapX);
                    yPoints7.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints7.push_back(hMapZ);
                }
            }
            //Square 8
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 0 && hMapZ <129){
                if (counter1%10==0){
                    xPoints8.push_back(hMapX);
                    yPoints8.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints8.push_back(hMapZ);
                }
            }
            //Square 9
            else if (hMapX > 0 && hMapX < 129 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints9.push_back(hMapX);
                    yPoints9.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints9.push_back(hMapZ);
                }
            }
            //Square 10
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints10.push_back(hMapX);
                    yPoints10.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints10.push_back(hMapZ);
                }
            }
            //Square 11
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints11.push_back(hMapX);
                    yPoints11.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints11.push_back(hMapZ);
                }
            }
            //Square 12
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints12.push_back(hMapX);
                    yPoints12.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints12.push_back(hMapZ);
                }
            }
            //Square 13
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints13.push_back(hMapX);
                    yPoints13.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints13.push_back(hMapZ);
                }
            }
            //Square 14
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints14.push_back(hMapX);
                    yPoints14.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints14.push_back(hMapZ);
                }
            }
            //Square 15
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints15.push_back(hMapX);
                    yPoints15.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints15.push_back(hMapZ);
                }
            }
            //Square 16
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 128 && hMapZ <257){
                if (counter1%10==0){
                    xPoints16.push_back(hMapX);
                    yPoints16.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints16.push_back(hMapZ);
                }
            }
            //Square 17
            else if (hMapX > 0 && hMapX < 129 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints17.push_back(hMapX);
                    yPoints17.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints17.push_back(hMapZ);
                }
            }
            //Square 18
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints18.push_back(hMapX);
                    yPoints18.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints18.push_back(hMapZ);
                }
            }
            //Square 19
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints19.push_back(hMapX);
                    yPoints19.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints19.push_back(hMapZ);
                }
            }
            //Square 20
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints20.push_back(hMapX);
                    yPoints20.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints20.push_back(hMapZ);
                }
            }
            //Square 21
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints21.push_back(hMapX);
                    yPoints21.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints21.push_back(hMapZ);
                }
            }
            //Square 22
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints22.push_back(hMapX);
                    yPoints22.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints22.push_back(hMapZ);
                }
            }
            //Square 23
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints23.push_back(hMapX);
                    yPoints23.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints23.push_back(hMapZ);
                }
            }
            //Square 24
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 256 && hMapZ <385){
                if (counter1%10==0){
                    xPoints24.push_back(hMapX);
                    yPoints24.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints24.push_back(hMapZ);
                }
            }
            //Square 25
            else if (hMapX > 0 && hMapX < 129 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints25.push_back(hMapX);
                    yPoints25.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints25.push_back(hMapZ);
                }
            }
            //Square 26
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints26.push_back(hMapX);
                    yPoints26.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints26.push_back(hMapZ);
                }
            }
            //Square 27
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints27.push_back(hMapX);
                    yPoints27.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints27.push_back(hMapZ);
                }
            }
            //Square 28
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints28.push_back(hMapX);
                    yPoints28.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints28.push_back(hMapZ);
                }
            }
            //Square 29
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints29.push_back(hMapX);
                    yPoints29.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints29.push_back(hMapZ);
                }
            }
            //Square 30
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints30.push_back(hMapX);
                    yPoints30.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints30.push_back(hMapZ);
                }
            }
            //Square 31
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints31.push_back(hMapX);
                    yPoints31.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints31.push_back(hMapZ);
                }
            }
            //Square 32
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 384 && hMapZ <513){
                if (counter1%10==0){
                    xPoints32.push_back(hMapX);
                    yPoints32.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints32.push_back(hMapZ);
                }
            }
            //Square 33
            else if (hMapX > 0 && hMapX < 129 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints33.push_back(hMapX);
                    yPoints33.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints33.push_back(hMapZ);
                }
            }
            //Square 34
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints34.push_back(hMapX);
                    yPoints34.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints34.push_back(hMapZ);
                }
            }
            //Square 35
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints35.push_back(hMapX);
                    yPoints35.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints35.push_back(hMapZ);
                }
            }
            //Square 36
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints36.push_back(hMapX);
                    yPoints36.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints36.push_back(hMapZ);
                }
            }
            //Square 37
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints37.push_back(hMapX);
                    yPoints37.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints37.push_back(hMapZ);
                }
            }
            //Square 38
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints38.push_back(hMapX);
                    yPoints38.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints38.push_back(hMapZ);
                }
            }
            //Square 39
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints39.push_back(hMapX);
                    yPoints39.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints39.push_back(hMapZ);
                }
            }
            //Square 40
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 512 && hMapZ <641){
                if (counter1%10==0){
                    xPoints40.push_back(hMapX);
                    yPoints40.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints40.push_back(hMapZ);
                }
            }
            //Square 41
            else if (hMapX > 0 && hMapX < 129 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints41.push_back(hMapX);
                    yPoints41.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints41.push_back(hMapZ);
                }
            }
            //Square 42
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints42.push_back(hMapX);
                    yPoints42.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints42.push_back(hMapZ);
                }
            }
            //Square 43
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints43.push_back(hMapX);
                    yPoints43.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints43.push_back(hMapZ);
                }
            }
            //Square 44
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints44.push_back(hMapX);
                    yPoints44.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints44.push_back(hMapZ);
                }
            }
            //Square 45
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints45.push_back(hMapX);
                    yPoints45.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints45.push_back(hMapZ);
                }
            }
            //Square 46
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints46.push_back(hMapX);
                    yPoints46.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints46.push_back(hMapZ);
                }
            }
            //Square 47
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints47.push_back(hMapX);
                    yPoints47.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints47.push_back(hMapZ);
                }
            }
            //Square 48
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 640 && hMapZ <769){
                if (counter1%10==0){
                    xPoints48.push_back(hMapX);
                    yPoints48.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints48.push_back(hMapZ);
                }
            }
            //Square 49
            else if (hMapX > 0 && hMapX < 129 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints49.push_back(hMapX);
                    yPoints49.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints49.push_back(hMapZ);
                }
            }
            //Square 50
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints50.push_back(hMapX);
                    yPoints50.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints50.push_back(hMapZ);
                }
            }
            //Square 51
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints51.push_back(hMapX);
                    yPoints51.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints51.push_back(hMapZ);
                }
            }
            //Square 52
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints52.push_back(hMapX);
                    yPoints52.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints52.push_back(hMapZ);
                }
            }
            //Square 53
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints53.push_back(hMapX);
                    yPoints53.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints53.push_back(hMapZ);
                }
            }
            //Square 54
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints54.push_back(hMapX);
                    yPoints54.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints54.push_back(hMapZ);
                }
            }
            //Square 55
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints55.push_back(hMapX);
                    yPoints55.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints55.push_back(hMapZ);
                }
            }
            //Square 56
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 768 && hMapZ <897){
                if (counter1%10==0){
                    xPoints56.push_back(hMapX);
                    yPoints56.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints56.push_back(hMapZ);
                }
            }
            //Square 57
            else if (hMapX > 0 && hMapX < 129 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints57.push_back(hMapX);
                    yPoints57.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints57.push_back(hMapZ);
                }
            }
            //Square 58
            else if (hMapX > 128 && hMapX < 257 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints58.push_back(hMapX);
                    yPoints58.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints58.push_back(hMapZ);
                }
            }
            //Square 59
            else if (hMapX > 256 && hMapX < 385 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints59.push_back(hMapX);
                    yPoints59.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints59.push_back(hMapZ);
                }
            }
            //Square 60
            else if (hMapX > 384 && hMapX < 513 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints60.push_back(hMapX);
                    yPoints60.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints60.push_back(hMapZ);
                }
            }
            //Square 61
            else if (hMapX > 512 && hMapX < 641 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints61.push_back(hMapX);
                    yPoints61.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints61.push_back(hMapZ);
                }
            }
            //Square 62
            else if (hMapX > 640 && hMapX < 769 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints62.push_back(hMapX);
                    yPoints62.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints62.push_back(hMapZ);
                }
            }
            //Square 63
            else if (hMapX > 768 && hMapX < 897 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints63.push_back(hMapX);
                    yPoints63.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints63.push_back(hMapZ);
                }
            }
            //Square 64
            else if (hMapX > 896 && hMapX < 1025 && hMapZ > 896 && hMapZ <1025){
                if (counter1%10==0){
                    xPoints64.push_back(hMapX);
                    yPoints64.push_back(hHeightField[hMapX][hMapZ]);
                    zPoints64.push_back(hMapZ);
                }
            }
            counter1++;
        }
    }
	//glEnd();

    // Draw texture triangles
    // Old
    /*
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f((float)hMapX / hmWidth, (float)hMapZ / hmHeight);
                glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);

                glTexCoord2f((float)hMapX / hmWidth, (float)(hMapZ + 1) / hmHeight);
                glVertex3f(hMapX, hHeightField[hMapX][hMapZ + 1], hMapZ + 1);

                glTexCoord2f((float)(hMapX + 1) / hmWidth, (float)hMapZ / hmHeight);
                glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ], hMapZ);

                glTexCoord2f((float)(hMapX + 1) / hmWidth, (float)(hMapZ + 1) / hmHeight);
                glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ + 1], hMapZ + 1);
            glEnd();
        }
    }
    glDisable(GL_TEXTURE_2D); */
    // New
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOTexCoords);
    glTexCoordPointer(2, GL_FLOAT, 0, (char *)NULL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vhVBOVertices);
    glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);

    glDrawArrays(GL_TRIANGLES, 0, vhVertexCount);

    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    /*
    GLfloat light0_ambient[] = {0.1f, 0.1f, 0.3f, 1.0f};
    GLfloat light0_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0_position[] = {1000.0, 500.0, 500.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    */
}
