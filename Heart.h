//
//  Heart.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef HEART_H
#define HEART_H

#include "Item.h"
#include <iostream>

class Heart : public Item{ //inherits from Item
public:
    Heart(); //constructor
    virtual void display(); //display function
    virtual void use(); //function for item's use
    
    
    
private:
    
    
    
}

#endif
