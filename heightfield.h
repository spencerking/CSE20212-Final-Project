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

	vector<int> xPoints3;
	vector<int> yPoints3;
	vector<int> zPoints3;
    
    vector<int> xPoints4;
	vector<int> yPoints4;
	vector<int> zPoints4;
    
	vector<int> xPoints5;
	vector<int> yPoints5;
	vector<int> zPoints5;
    
	vector<int> xPoints6;
	vector<int> yPoints6;
	vector<int> zPoints6;
    
    vector<int> xPoints7;
	vector<int> yPoints7;
	vector<int> zPoints7;
    
	vector<int> xPoints8;
	vector<int> yPoints8;
	vector<int> zPoints8;
    
    vector<int> xPoints9;
	vector<int> yPoints9;
	vector<int> zPoints9;
    
	vector<int> xPoints10;
	vector<int> yPoints10;
	vector<int> zPoints10;
    
	vector<int> xPoints11;
	vector<int> yPoints11;
	vector<int> zPoints11;
    
    vector<int> xPoints12;
	vector<int> yPoints12;
	vector<int> zPoints12;
    
	vector<int> xPoints13;
	vector<int> yPoints13;
	vector<int> zPoints13;
    
	vector<int> xPoints14;
	vector<int> yPoints14;
	vector<int> zPoints14;
    
    vector<int> xPoints15;
	vector<int> yPoints15;
	vector<int> zPoints15;
    
	vector<int> xPoints16;
	vector<int> yPoints16;
	vector<int> zPoints16;
    
    vector<int> xPoints17;
	vector<int> yPoints17;
	vector<int> zPoints17;
    
	vector<int> xPoints18;
	vector<int> yPoints18;
	vector<int> zPoints18;
    
	vector<int> xPoints19;
	vector<int> yPoints19;
	vector<int> zPoints19;
    
    vector<int> xPoints20;
	vector<int> yPoints20;
	vector<int> zPoints20;
    
	vector<int> xPoints21;
	vector<int> yPoints21;
	vector<int> zPoints21;
    
	vector<int> xPoints22;
	vector<int> yPoints22;
	vector<int> zPoints22;
    
    vector<int> xPoints23;
	vector<int> yPoints23;
	vector<int> zPoints23;
    
	vector<int> xPoints24;
	vector<int> yPoints24;
	vector<int> zPoints24;
    
    vector<int> xPoints25;
	vector<int> yPoints25;
	vector<int> zPoints25;
    
	vector<int> xPoints26;
	vector<int> yPoints26;
	vector<int> zPoints26;
    
	vector<int> xPoints27;
	vector<int> yPoints27;
	vector<int> zPoints27;
    
    vector<int> xPoints28;
	vector<int> yPoints28;
	vector<int> zPoints28;
    
	vector<int> xPoints29;
	vector<int> yPoints29;
	vector<int> zPoints29;
    
	vector<int> xPoints30;
	vector<int> yPoints30;
	vector<int> zPoints30;
    
    vector<int> xPoints31;
	vector<int> yPoints31;
	vector<int> zPoints31;
    
	vector<int> xPoints32;
	vector<int> yPoints32;
	vector<int> zPoints32;
    
    vector<int> xPoints33;
	vector<int> yPoints33;
	vector<int> zPoints33;
    
	vector<int> xPoints34;
	vector<int> yPoints34;
	vector<int> zPoints34;
    
	vector<int> xPoints35;
	vector<int> yPoints35;
	vector<int> zPoints35;
    
    vector<int> xPoints36;
	vector<int> yPoints36;
	vector<int> zPoints36;
    
	vector<int> xPoints37;
	vector<int> yPoints37;
	vector<int> zPoints37;
    
	vector<int> xPoints38;
	vector<int> yPoints38;
	vector<int> zPoints38;
    
    vector<int> xPoints39;
	vector<int> yPoints39;
	vector<int> zPoints39;
    
	vector<int> xPoints40;
	vector<int> yPoints40;
	vector<int> zPoints40;
    
    vector<int> xPoints41;
	vector<int> yPoints41;
	vector<int> zPoints41;
    
	vector<int> xPoints42;
	vector<int> yPoints42;
	vector<int> zPoints42;
    
	vector<int> xPoints43;
	vector<int> yPoints43;
	vector<int> zPoints43;
    
    vector<int> xPoints44;
	vector<int> yPoints44;
	vector<int> zPoints44;
    
	vector<int> xPoints45;
	vector<int> yPoints45;
	vector<int> zPoints45;
    
	vector<int> xPoints46;
	vector<int> yPoints46;
	vector<int> zPoints46;
    
    vector<int> xPoints47;
	vector<int> yPoints47;
	vector<int> zPoints47;
    
	vector<int> xPoints48;
	vector<int> yPoints48;
	vector<int> zPoints48;
    
    vector<int> xPoints49;
	vector<int> yPoints49;
	vector<int> zPoints49;
    
	vector<int> xPoints50;
	vector<int> yPoints50;
	vector<int> zPoints50;
    
	vector<int> xPoints51;
	vector<int> yPoints51;
	vector<int> zPoints51;
    
    vector<int> xPoints52;
	vector<int> yPoints52;
	vector<int> zPoints52;
    
	vector<int> xPoints53;
	vector<int> yPoints53;
	vector<int> zPoints53;
    
	vector<int> xPoints54;
	vector<int> yPoints54;
	vector<int> zPoints54;
    
    vector<int> xPoints55;
	vector<int> yPoints55;
	vector<int> zPoints55;
    
	vector<int> xPoints56;
	vector<int> yPoints56;
	vector<int> zPoints56;
    
    vector<int> xPoints57;
	vector<int> yPoints57;
	vector<int> zPoints57;
    
	vector<int> xPoints58;
	vector<int> yPoints58;
	vector<int> zPoints58;
    
	vector<int> xPoints59;
	vector<int> yPoints59;
	vector<int> zPoints59;
    
    vector<int> xPoints60;
	vector<int> yPoints60;
	vector<int> zPoints60;
    
	vector<int> xPoints61;
	vector<int> yPoints61;
	vector<int> zPoints61;
    
	vector<int> xPoints62;
	vector<int> yPoints62;
	vector<int> zPoints62;
    
    vector<int> xPoints63;
	vector<int> yPoints63;
	vector<int> zPoints63;
    
	vector<int> xPoints64;
	vector<int> yPoints64;
	vector<int> zPoints64;
    
    int counter1;
   /* int counter2;
    int counter3;
    int counter4;
    int counter5;
    int counter6;
    int counter7;
    int counter8;
    int counter9;
    int counter10;
    int counter11;
    int counter12;
    int counter13;
    int counter14;
    int counter15;
    int counter16;
    int counter17;
    int counter18;
    int counter19;
    int counter20;
    int counter21;
    int counter22;
    int counter23;
    int counter24;
    int counter25;
    int counter26;
    int counter27;
    int counter28;
    int counter29;
    int counter30;
    int counter31;
    int counter32;
    int counter33;
    int counter34;
    int counter35;
    int counter36;
    int counter37;
    int counter38;
    int counter39;
    int counter40;
    int counter41;
    int counter42;
    int counter43;
    int counter44;
    int counter45;
    int counter46;
    int counter47;
    int counter48;
    int counter49;
    int counter50;
    int counter51;
    int counter52;
    int counter53;
    int counter54;
    int counter55;
    int counter56;
    int counter57;
    int counter58;
    int counter59;
    int counter60;
    int counter61;
    int counter62;
    int counter63;
    int counter64;*/
};

#endif
