//
//  Wooper.h
//  
//
//  Created by Spencer King on 4/21/14.
//
//

#ifndef WOOPER_H
#define WOOPER_H

//#include "models.h"
#include "Object.h"
#include <iostream>

class Wooper{// : public models{ //inherits from models
public:
    Wooper(); //constructor
    void init(float, float, float); //init function
    void move(); //movement function
    void render(); //draw function
    
private:
    Object* wooper;
    
};

#endif /* defined(____Wooper__) */
