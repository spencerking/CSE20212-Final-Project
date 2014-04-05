//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html
#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 
//#include <windows.h>
//the following typedef eliminates the need for windows.h
typedef unsigned char MAP; //this somehow stores the heighfield
//define the 2d and 3d vectors
//typedef vector<int> intVector;
//typedef vector<intVector> twoDimVector;
//typedef vector<vector<intVector> > threeDVector;

class HeightField {
    
public:
	bool Create(char *hFileName, const int hWidth, const int hHeight); //reads in the file
    
	void Render(void); //renders the map
    
	MAP hHeightField[1024][1024]; //stores the map data

	int collisionDetection(float, float, float);
   	

private:
	int hmHeight;
	int hmWidth;
	float terrainRadius;
	float cameraRadius;

	vector<int> xPoints;
	vector<int> yPoints;
	vector<int> zPoints;
    
};

#endif
