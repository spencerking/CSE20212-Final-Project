#include <GL/glew.h>
#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#elif WIN32
	#include <windows.h>
	#include <wingdi.h>
	#include <GL/gl.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#include "Hero"
// include rest

using namespace std;

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(-1,-1);
	glutInitWindowSize(1000,1000); // Change later
	glutCreateWindow("Game");

	if (glewInit() != GLEW_OK) {
		cout << "Error initializing GLEW" << endl;
		return 0;
	}

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Actual game stuff
	hero = new Hero();
	hero->loadObjectFile("link.obj");
	
}