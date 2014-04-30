#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <assert.h>
#include <unistd.h>
//#include "Global.h"
//#include "Skybox.h"
//#include "Camera.h"
//#include "Sound.h"
#include "GameController.h"
//#include "intro.h"

//#define WINDOW_W 1000
//#define WINDOW_H 800

//instantiate objects
//Camera camera;
GameController gamecontroller;
//Sound sound;
//Intro intro;


//basic display function
void display (void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 3D scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //cameraFunc();
    gamecontroller.GameUpdateCamera();
    
   // intro.renderTitlescreen();

    gamecontroller.GameRender();

    // 2D UI
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0,WINDOW_W,WINDOW_H,0,0,1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            //glBegin(GL_QUADS);
            //glColor4f(0,0,0,shutterAlpha);
            glRectf(5,25,25,5);
            //glEnd();
        glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
	glutSwapBuffers();
}

//initialization function
void init (void) {
    // Init lighting
    GLfloat light0_ambient[] = {0.1f, 0.1f, 0.3f, 1.0f};
    GLfloat light0_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0_position[] = {1030.0, 500.0, 300.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    GLfloat local_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat local_view[] = {0.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, local_ambient);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    //intro.initTitlescreen();

   // gamecontroller.GameSetNames();
    gamecontroller.GameInit();
    //sound.init();
}


//mouse control function based on the swiftless tutorials
void orientMe(int x, int y) {
    gamecontroller.GameMouseOrientation(x, y);

}

//keyboard function based on swiftless and Emrich's tutorials

void keyboard (unsigned char key, int x, int y) {
    gamecontroller.GameKeyboardInput(key, x, y);
	 
}

//allows for altitude change with up and down arrow keys
void arrowKeys(int key, int x, int y){
    
    gamecontroller.GameArrowKeys(key, x, y);
   
    
}

//a standard function for handling reshaping of the window
void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode (GL_MODELVIEW);
}

//the main function
int main (int argc, char **argv) {
   	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition(0, 0);
   	glutCreateWindow("Pokémon Snap: The Sequel");
	init();
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
   	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowKeys);
	glutPassiveMotionFunc(orientMe);
   	glutMainLoop();
   	return 0;
}
