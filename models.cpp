//
//  models.cpp
//  
//
//  Created by Spencer King on 4/20/14.
//
//

#include "models.h"

Models::Models() {
	
}

void Models::setFilename(std::string name) {
	filename = name;
}

//default constructor
void Models::init(float x, float y, float z){
	model = new Object();
	   model->loadObjectFile(filename);
	model->getLocation()->setX(x);
	model->getLocation()->setY(y);
	model->getLocation()->setZ(z);
}

void Models::move() {

}

void Models::render() {
	glPushMatrix();
	glTranslatef(model->getLocation()->getX(), model->getLocation()->getY(), model->getLocation()->getZ());
	glRotatef(90.0, 0.0, 1.0, 0.0);
	model->render();
	glPopMatrix();
}
