//
//  ElderScott.h
//
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef ELDERSCOTT_H
#define ELDERSCOTT_H

#include "Character.h"
#include <iostream>

class ElderScott : public Character{ //inherits from Character
    
public:
    ElderScott(); //constructor
    virtual void display(); //display function
    virtual void move(); //different characters move differently
    void speak(); //allows the Elder to speak his wise words
    
    
private:
    
    
    
}

#endif
