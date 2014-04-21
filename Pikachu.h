//
//  Pikachu.h
//  
//
//  Created by Spencer King on 4/20/14.
//
//

#ifndef PIKACHU_H
#define PIKACHU_H

//#include "models.h"
#include "Object.h"
#include <iostream>

class Pikachu{// : public models{ //inherits from models
public:
    Pikachu(); //constructor
    void init(); //init function
    void move(); //movement function
    void render(); //draw function
    
private:
    Object* pikachu;
    
};

#endif /* defined(____Pikachu__) */
