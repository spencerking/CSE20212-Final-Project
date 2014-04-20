//
//  pikachu.cpp
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

#include "models.h"
#include "pikachu.h"
#include "Object.h"


//default constructor
pikachu::pikachu(){
    Object* Pikachu;
    unsigned int pikachutexture;
}

//display function
void pikachu::display(){
    Pikachu = new Object();
	Pikachu->loadObjectFile("Pikachu.obj");
    Pikachu->getLocation()->setX(876.902);
    Pikachu->getLocation()->setY(1.9367);
    Pikachu->getLocation()->setZ(704.263);
}

//movement function
void pikachu::move(){
    
}

//draw function
void pikachu::draw(){
    glTranslatef(Pikachu->getLocation()->getX(), Pikachu->getLocation()->getY(), Pikachu->getLocation()->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    Pikachu->draw();
}