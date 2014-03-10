//
//  Dragon.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef DRAGON_H
#define DRAGON_H
#include "Enemy.h"

#include <iostream>


class Dragon : public Enemy{ //inherits from Enemy
    
    
public:
    Dragon(); //constructor
    virtual void display(); //display function
    virtual void attack(); //attack function
    
private:
    
    
    
}

#endif
