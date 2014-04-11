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


class HeightField {
    
public:
	bool Create(char *hFileName, const int hWidth, const int hHeight); //reads in the file
    
	void Render(void); //renders the map
    
	MAP hHeightField[1024][1024]; //stores the map data

	int collisionDetection(float, float, float);
   	

private:
	int hmHeight;
	int hmWidth;

	vector<int> xPoints1;
	vector<int> yPoints1;
	vector<int> zPoints1;
    
	vector<int> xPoints2;
	vector<int> yPoints2;
	vector<int> zPoints2;

	vector<int> xPoints896;
	vector<int> yPoints896;
	vector<int> zPoints896;
};

#endif
