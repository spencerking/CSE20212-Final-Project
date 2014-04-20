//
//  pikachu.h
//  
//
//  Created by Spencer King on 4/20/14.
//
//

#ifndef PIKACHU_H
#define PIKACHU_H

#include "models.h"
#include <iostream>

class pikachu : public models{ //inherits from models
public:
    pikachu(); //constructor
    virtual void display(); //display function
    virtual void move(); //movement function
    virtual void draw(); //draw function
    
private:
    
    
    
};




#endif /* defined(____pikachu__) */
