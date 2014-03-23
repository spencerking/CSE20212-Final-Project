//
//  IntroRoom.cpp
//  
//
//  Created by Spencer King on 3/23/14.
//
//

#include "IntroRoom.h"


//default constructor
IntroRoom::IntroRoom(){
    IntroRoom::drawRoom();
    
}


//draws the basic walls of the room
void IntroRoom::drawRoom(){
    
    glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
    //ground
    glVertex3f(-20.0f, 0.0f, -20.0f);
    glVertex3f(-20.0f, 0.0f,  20.0f);
    glVertex3f( 20.0f, 0.0f,  20.0f);
    glVertex3f( 20.0f, 0.0f, -20.0f);
    //ceiling
    glVertex3f(-20.0f, 20.0f, -20.0f);
    glVertex3f(-20.0f, 20.0f,  20.0f);
    glVertex3f( 20.0f, 20.0f,  20.0f);
    glVertex3f( 20.0f, 20.0f, -20.0f);
    //front wall
    glVertex3f(20.0f, 20.0f, 20.0f);
    glVertex3f(-20.0f, 20.0f, 20.0f);
    glVertex3f( 20.0f, 0.0f, 20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);
    //back wall
    glVertex3f(20.0f, 20.0f, -20.0f);
    glVertex3f(-20.0f, 20.0f, -20.0f);
    glVertex3f( 20.0f, 0.0f, -20.0f);
    glVertex3f(-20.0f, 0.0f, -20.0f);
    //right wall
    glVertex3f(20.0f, 20.0f, 20.0f);
    glVertex3f(20.0f, 20.0f, -20.0f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    glVertex3f(20.0f, 0.0f, -20.0f);
    //left wall
    glVertex3f(-20.0f, 20.0f, 20.0f);
    glVertex3f(-20.0f, 20.0f, -20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);
    glVertex3f(-20.0f, 0.0f, -20.0f);
	glEnd();
    
}