//
//  Weapon.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>

class Weapon{
    
public:
    
    Weapon(); //constructor
    virtual void display()=0; //display function
    int strength; //determines the amount of damage a weapon does
    int weaponQuantity; //quantity, if applicable
    
    
private:
    
    
}


#endif