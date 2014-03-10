//
//  Enemy.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>

class Enemy {
    
public:
    Enemy(); //constructor
    virtual void display()=0; //display function
    virtual void attack()=0; //each enemy has a unique attack
    void move(); //function for movement
    void itemDrop(); //function to determine item drops
    int health; //health variable
    
    
private:
    
    
    
}



#endif 
