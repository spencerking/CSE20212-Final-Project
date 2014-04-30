#include "models.h"

//default constructor
Models::Models() {
	
}

//sets the model's filename
void Models::setFilename(std::string name) {
	filename = name;
}

//initialize a model
void Models::init(float x, float y, float z){
	model = new Object();
    model->loadObjectFile(filename);
	model->getLocation()->setX(x);
	model->getLocation()->setY(y);
	model->getLocation()->setZ(z);
}

//returns the current x-coordinate
float Models::getXpos(){
    float xcurrent = model->getLocation()->getX();
    return xcurrent;
}

//returns the current y-coordinate
float Models::getYpos(){
    float ycurrent = model->getLocation()->getY();
    return ycurrent;
}

//returns the current z-coordinate
float Models::getZpos(){
    float zcurrent = model->getLocation()->getZ();
    return zcurrent;
}

//changes a model's current position
void Models::move(float xChange, float yChange, float zChange) {
    model->getLocation()->setX(xChange);
    model->getLocation()->setY(yChange);
    model->getLocation()->setZ(zChange);
}

//renders a model
void Models::render() {
	glPushMatrix();
	glTranslatef(model->getLocation()->getX(), model->getLocation()->getY(), model->getLocation()->getZ());
	glRotatef(90.0, 0.0, 1.0, 0.0);
	model->render();
	glPopMatrix();
}

