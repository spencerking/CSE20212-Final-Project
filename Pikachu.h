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
#include "object.h"
#include <iostream>

class Pikachu{// : public models{ //inherits from models
public:
    Pikachu(); //constructor
     void display(); //display function
    void move(); //movement function
    void draw(); //draw function
    
private:
    Object* Pikachu;
    
};




#endif /* defined(____Pikachu__) */
