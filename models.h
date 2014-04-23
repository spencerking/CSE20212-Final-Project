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


class Models {
    
    
public:
    Models(); //constructor takes filename and location parameters
    void init(float, float, float);
    void move(); //movement function
    void render(); //render function
    void setFilename(std::string);
    
private:
    Object * model;
    string filename;
        
};

#endif /* defined(____models__) */
