#ifndef MODELS_H
#define MODELS_H

#include "Object.h"
#include <iostream>
#include <string>

class Models {
    
    
public:
    Models(); //constructor takes filename and location parameters
    void init(float, float, float); //initialize a model
    void move(float, float, float); //movement function
    void render(); //render function
    void setFilename(std::string); //sets the filename
    float getXpos(); //gets the x-coordinate
    float getYpos(); //gets the y-coordinate
    float getZpos(); //gets the z-coordinate
    
private:
    Object * model;
    string filename;    
        
};

#endif 