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
    Object* Pikachu;
    unsigned int Pikachutexture;
}

//display function
void Pikachu::display(){
    Pikachu = new Object();
	Pikachu->loadObjectFile("Pokemon/Pikachu/Pikachu.obj");
    Pikachu->getLocation()->setX(876.902);
    Pikachu->getLocation()->setY(1.9367);
    Pikachu->getLocation()->setZ(704.263);
}

//movement function
void Pikachu::move(){
    
}

//draw function
void Pikachu::draw(){
    glTranslatef(Pikachu->getLocation()->getX(), Pikachu->getLocation()->getY(), Pikachu->getLocation()->getZ());
    glRotatef(90.0, 0.0, 1.0, 0.0);
    Pikachu->draw();
}
