//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html
#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <vector>
using namespace std; 
//#include <windows.h>
//the following typedef eliminates the need for windows.h
typedef unsigned char MAP; //this somehow stores the heighfield
//define the 2d and 3d vectors
typedef vector<int> intVector;
typedef vector<intVector> twoDimVector;
typedef vector<vector<intVector> > threeDVector;

class HeightField {
    
public:
	bool Create(char *hFileName, const int hWidth, const int hHeight); //reads in the file
    
	void Render(void); //renders the map
    
	MAP hHeightField[1024][1024]; //stores the map data

	//threeDVector Points; //3d vector
	//twoDimVector Points2; //2d vector
	//vector<int> Points;     	

private:
	int hmHeight;
	int hmWidth;
    
};

#endif
