//
//  Xatu.cpp
//  
//
//  Created by Spencer King on 4/21/14.
//
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
//#include "models.h"
#include "Xatu.h"
#include "Object.h"

//default constructor
Xatu::Xatu(){
    
}

//display function
void Xatu::init(){
    xatu = new Object();
	xatu->loadObjectFile("xatu.obj");
    xatu->getLocation()->setX(680.128);
    xatu->getLocation()->setY(241.622);
    xatu->getLocation()->setZ(271.506);
}

//movement function
void Xatu::move(){
    
}

//draw function
void Xatu::render(){
    glTranslatef(xatu->getLocation()->getX(), xatu->getLocation()->getY(), xatu->getLocation()->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    xatu->render();
}