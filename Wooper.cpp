//
//  Wooper.cpp
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
#include "Wooper.h"
#include "Object.h"

//default constructor
Wooper::Wooper(){
    
}

//display function
void Wooper::init(float x, float y, float z){
    wooper = new Object();
	wooper->loadObjectFile("wooper.obj");
    wooper->getLocation()->setX(x);
    wooper->getLocation()->setY(y);
    wooper->getLocation()->setZ(z);
}

//movement function
void Wooper::move(){
    
}

//draw function
void Wooper::render(){
    glPushMatrix();
    glTranslatef(wooper->getLocation()->getX(), wooper->getLocation()->getY(), wooper->getLocation()->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    wooper->render();
    glPopMatrix();
}