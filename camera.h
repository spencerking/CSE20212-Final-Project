
#ifndef CAMERA_H
#define CAMERA_H
#include <string>

class camera{

	public:
	camera(); //constructor
	void screenshot(char *, short, short);
	void setupScreenshot();
    void stringIncrement(std::string&);
    
	private:
    std::string fileName;
};


#endif
