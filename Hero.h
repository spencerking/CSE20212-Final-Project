//
//  Hero.h
//
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include <string>
#include <iostream>

class Hero : public Character{ //inherits from Character
public:
    Hero(); //constructor
    virtual void display(); //display function    
    virtual void move(); //movement function
    void getName(string); //get Hero's name from player
    void rightHandAttack(); //attack with weapon in right hand
    void leftHandAttack(); //attack with weapon in left hand
    
private:
    string heroName;
    
    
}

#endif
