//
//  Pikachu.cpp
//  
//
//  Created by Spencer King on 4/20/14.
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
#include "Pikachu.h"
#include "Object.h"

//default constructor
Pikachu::Pikachu(){
    
}

//display function
void Pikachu::init(float x, float y, float z){
    pikachu = new Object();
	pikachu->loadObjectFile("Pikachu.obj");
    pikachu->getLocation()->setX(x);
    pikachu->getLocation()->setY(y);
    pikachu->getLocation()->setZ(z);
}

//movement function
void Pikachu::move(){
    
}

//draw function
void Pikachu::render(){
    glPushMatrix();
    glTranslatef(pikachu->getLocation()->getX(), pikachu->getLocation()->getY(), pikachu->getLocation()->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    pikachu->render();
    glPopMatrix();
}
