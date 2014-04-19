
#ifndef CAMERA_H
#define CAMERA_H
#include <string>

class camera{

	public:
	camera(); //constructor
	void screenshot(char *, short, short); //screenshot function
	void setupScreenshot(); //sets up the filename for the screenshot function
    void stringIncrement(std::string&); //increments the filename string
    
	private:
    std::string fileName;
};


#endif
