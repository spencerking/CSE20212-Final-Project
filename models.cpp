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

float Models::getXpos(){
    float xcurrent = model->getLocation()->getX();
    return xcurrent;
}

float Models::getYpos(){
    float ycurrent = model->getLocation()->getY();
    return ycurrent;
}

float Models::getZpos(){
    float zcurrent = model->getLocation()->getZ();
    return zcurrent;
}

void Models::move(float xChange, float yChange, float zChange) {
    /*
    float xcurrent = model->getLocation()->getX();
	float ycurrent = model->getLocation()->getY();
	float zcurrent = model->getLocation()->getZ();
    
    float xfuture = xcurrent+xChange;
    float yfuture = ycurrent+yChange;
    float zfuture = zcurrent+zChange;
    cout<<"calling func"<<endl;
    if (hField.collisionDetection(xfuture, yfuture, zfuture)){
        cout << "collision"<<endl;
    }
    else{
        cout<<"collision free"<<endl;
        model->getLocation()->setX(xfuture);
        model->getLocation()->setY(yfuture);
        model->getLocation()->setZ(zfuture);
    }
    */
    model->getLocation()->setX(xChange);
    model->getLocation()->setY(yChange);
    model->getLocation()->setZ(zChange);
}

void Models::render() {
	glPushMatrix();
	glTranslatef(model->getLocation()->getX(), model->getLocation()->getY(), model->getLocation()->getZ());
	glRotatef(90.0, 0.0, 1.0, 0.0);
	model->render();
	glPopMatrix();
}

