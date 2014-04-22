//
//  Raichu.cpp
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
#include "Raichu.h"
#include "Object.h"

//default constructor
Raichu::Raichu(){
    
}

//display function
void Raichu::init(float x, float y, float z){
    raichu = new Object();
	raichu->loadObjectFile("raichu.obj");
    raichu->getLocation()->setX(x);
    raichu->getLocation()->setY(y);
    raichu->getLocation()->setZ(z);
}

//movement function
void Raichu::move(){
    
}

//draw function
void Raichu::render(){
    glPushMatrix();
    glTranslatef(raichu->getLocation()->getX(), raichu->getLocation()->getY(), raichu->getLocation()->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    raichu->render();
    glPopMatrix();
}