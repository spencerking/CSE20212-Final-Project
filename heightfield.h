//
//  heightfield.h
//  
//
//  Created by Spencer King on 3/31/14.
//
//

#ifndef ____heightfield__
#define ____heightfield__

#include <iostream>
//#include <windows.h>
//windows.h is needed for the BYTE variable type to load in the heightfield.raw image file, we need to either find a replacement for the header or define BYTE ourselves

class HeightField {
    
public:
    bool Create(char *hFileName, int hWidth, const int hHeight);
    void Render(void);
    BYTE hheightField[1024][1024];
    
private:
    //these hold the heigh and width of the height field
    int hmHeight;
    int hmWidth;
    
};

#endif /* defined(____heightfield__) */
