//
//  Item.h
//  
//
//  Created by Spencer King on 3/9/14.
//
//

#ifndef ITEM_H
#define ITEM_H

#include <iostream>

class Item{
    
public:
    Item(); //constructor
    virtual void display()=0; //display function
    virtual void use()=0; //each item has a different affect
    int itemQuantity; //variable for quantity
    
private:
    
    
    
}

#endif
