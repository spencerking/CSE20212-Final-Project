//
//  Xatu.h
//  
//
//  Created by Spencer King on 4/21/14.
//
//

#ifndef XATU_H
#define XATU_H

//#include "models.h"
#include "Object.h"
#include <iostream>

class Xatu{// : public models{ //inherits from models
public:
    Xatu(); //constructor
    void init(); //init function
    void move(); //movement function
    void render(); //draw function
    
private:
    Object* xatu;
    
};

#endif /* defined(____Xatu__) */
