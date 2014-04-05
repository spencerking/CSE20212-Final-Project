
#ifndef CAMERA_H
#define CAMERA_H

class camera{

	public:
	camera(); //constructor
	void screenshot(char *, short, short);
	void setupScreenshot();

	private:
	int screenCounter;

};


#endif
