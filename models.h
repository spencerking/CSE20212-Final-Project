//
//  models.h
//  
//
//  Created by Spencer King on 4/20/14.
//
//

#ifndef MODELS_H
#define MODELS_H

#include "Object.h"
#include <iostream>
#include <string>
#include "Heightfield.h"


class Models {
    
    
public:
    Models(); //constructor takes filename and location parameters
    void init(float, float, float);
    void move(float, float, float); //movement function
    void render(); //render function
    void setFilename(std::string);
    float getXpos();
    float getYpos();
    float getZpos();
    
private:
    Object * model;
    string filename;
    HeightField hField;
    
        
};

#endif /* defined(____models__) */
