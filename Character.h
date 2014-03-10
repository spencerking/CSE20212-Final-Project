//
//  Character.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>

class Character{
    
public:
    Character(); //constructor
    virtual void display()=0; //display function
    virtual void move()=0; //different characters move differently
    
    
    
private:
    
    
    
}

#endif 
