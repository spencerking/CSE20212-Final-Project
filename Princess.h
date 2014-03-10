//
//  Princess.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef PRINCESS_H
#define PRINCESS_H

#include "Character.h"
#include <iostream>

class Princess : public Character{ //inherits from Character
    
public:
    Princess(); //constructor
    virtual void display(); //display function
    virtual void move(); //movement function
    void speak(); //let's the Princess speak
    
    
private:
    
    
    
}

#endif
