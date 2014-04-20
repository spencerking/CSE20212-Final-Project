//
//  models.h
//  
//
//  Created by Spencer King on 4/20/14.
//
//

#ifndef MODELS_H
#define MODELS_H

#include <iostream>


class models {
    
    
public:
    models(); //constructor
    virtual void display()=0; //display function
    virtual void move()=0; //movement function
    virtual void draw()=0; //draw function
    
private:
    
    
    
}

#endif /* defined(____models__) */
