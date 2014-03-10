//
//  Bomb.h
//
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef BOMB_H
#define BOMB_H

#include "Item.h"
#include <iostream>

class Bomb : public Item{ //inherits from Item
public:
    Bomb(); //constructor
    virtual void display(); //display function
    virtual void use(); //function for item's use
    
    
    
private:
    
    
    
}

#endif
