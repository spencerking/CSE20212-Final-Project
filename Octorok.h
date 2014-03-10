//
//  Octorok.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef OCTOROK_H
#define OCTOROK_H

#include "Enemy.h"
#include <iostream>

class Octorok : public Enemy{ //inherits from Enemy
    
public:
    
    Octorok(); //constructor
    virtual void display(); //display function
    virtual void attack(); //attack function
    
    
private:
    
    
    

#endif
