//#include <GL/glew.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
// Windows headers?
//#include "Hero"
// include rest
#include "IntroRoom.h"
#include <iostream>

using namespace std;


void gameEngine(void){
    IntroRoom::IntroRoom();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,360); // Change later
	glutCreateWindow("Game");

	/*if (glewInit() != GLEW_OK) {
		cout << "Error initializing GLEW" << endl;
		return 0;
	}*/

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Actual game stuff
	//hero = new Hero();
	//hero->loadObjectFile("link.obj");
    glutDisplayFunc(gameEngine);
    glutIdleFunc(gameEngine);
    glutMainLoop();
	
}