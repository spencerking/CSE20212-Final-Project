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
void Pikachu::init(){
    pikachu = new Object();
	pikachu->loadObjectFile("Pikachu.obj");
    pikachu->getLocation()->setX(876.902);
    pikachu->getLocation()->setY(1.9367);
    pikachu->getLocation()->setZ(704.263);
}

//movement function
void Pikachu::move(){
    
}

//draw function
void Pikachu::render(){
    glTranslatef(pikachu->getLocation()->getX(), pikachu->getLocation()->getY(), pikachu->getLocation()->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    pikachu->render();
}
