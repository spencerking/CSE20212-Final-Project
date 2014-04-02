//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html

//#include <windows.h>
//the following typedef eliminates the need for windows.h
typedef unsigned char MAP; //this somehow stores the heighfield

class HeightField {
    
public:
	bool Create(char *hFileName, const int hWidth, const int hHeight); //reads in the file
    
	void Render(void); //renders the map
    
	MAP hHeightField[1024][1024]; //stores the map data
    
private:
	int hmHeight;
	int hmWidth;
    
};