//
//  heightfield.cpp
//  
//
//  Created by Spencer King on 3/31/14.
//
//

#include <stdio.h>
#include <gl/gl.h>
#include "heightfield.h"


bool HeightField::Create(char *hFileName, int hWidth, const int hHeight){
    
    
    hmHeight=hHeight;
    hmWidth=hWidth;
    
    FILE *fp;
    fp = fopen(hFileName, "rb");
    fread(hHeightField, 1, hWidth * hHeight, fp);
    fclose(fp);
    for (int hMapX = 0; hMapX<hWidth; hMapX++){
        for (int hMapZ=0; hMapZ<hHeight; hMapZ++){
            printf("%d, %d, %d\n", hMapX, hMapZ, hHeightField[hMapX][hMapZ]);
        }
    }
    return true;
    
}

void HeightField::Render(void){
    
    //this will render the terrain as points in space
    //points are created on the X and Z axes at the appropriate Y positions
    /*
    glBegin(GL_POINTS);
    for (int hMapX=0; hMapX<hmWidth; hMapX++){
        for (int hMapZ=0; hMapZ<hmHeight; hMapZ++){
            glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
        }
    }
    glEnd();
    */
    
    
    //this will render the terrain using polygons
    //it fills in the gaps between vertices
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
    glVertex3f(hMapX, hHeightField[hMapX][hMapZ+1], hMapZ+1);
    glVertex3f(hMapX+1, hHeightField[hMapX+1][hMapZ], hMapZ);
    glVertex3f(hMapX+1, hHeightField[hMapX+1][hMapZ+1], hMapZ+1);
    glEnd();
}