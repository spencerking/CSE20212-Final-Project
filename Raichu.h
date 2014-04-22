//
//  Raichu.h
//  
//
//  Created by Spencer King on 4/21/14.
//
//


#ifndef RAICHU_H
#define RAICHU_H

//#include "models.h"
#include "Object.h"
#include <iostream>

class Raichu{// : public models{ //inherits from models
public:
    Raichu(); //constructor
    void init(float, float, float); //init function
    void move(); //movement function
    void render(); //draw function
    
private:
    Object* raichu;
    
};

#endif /* defined(____Raichu__) */
