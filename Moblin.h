//
//  Moblin.h
//
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef MOBLIN_H
#define MOBLIN_H

#include "Enemy.h"
#include <iostream>

class Moblin : public Enemy{ //inherits from Enemy
    
public:
    
    Moblin(); //constructor
    virtual void display(); //display function
    virtual void attack(); //attack function
    
    
private:
    
    
    
    
#endif
