//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html
#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <assert.h>

#include "heightfield.h"
#include "camera.h"



//global variables for camera control
//we will have to play with these to get everything set up how we want
float xpos = 851.078;
float ypos = 351.594;
float zpos = 281.033; 
float xrot = 758;
float yrot = 238;
float angle=0.0;
float previousx;
float previousy;

float bounce;
float cScale = 1.0;

//instantiate objects
HeightField hField;
camera camera1;

//basic camera function
//this is straight from the swiftless tutorial
void camera (void) {
	int posX = (int)xpos;
	int posZ = (int)zpos;
    
	glRotatef(xrot,1.0,0.0,0.0); //rotates on the x-axis
	glRotatef(yrot,0.0,1.0,0.0); //rotates on the y-axis
	glTranslated(-xpos,-ypos,-zpos); //translates the screen to the current camera positon
}

//basic display function
void display (void) {
	glClearColor (0.0,0.0,0.0,1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	glLoadIdentity();
	camera();
    
	glPushMatrix();
	hField.Render();
	glPopMatrix();
    
	glutSwapBuffers();
}

//initialization function
void Init (void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    
	hField.Create("heightField2.raw", 1024, 1024);
}

//mouse control function based on the swiftless tutorials
void orientMe(int x, int y) {

	//calculates the differences between the current x and y positions
	//and the previous x and y positions
 	int diffx=x-previousx;
 	int diffy=y-previousy;

	//the previous x and y positions become the current x and y positions
 	previousx=x;
	 previousy=y;
	 xrot += (float) diffy;
 	yrot += (float) diffx;
}


//keyboard function based on swiftless and Emrich's tutorials

void keyboard (unsigned char key, int x, int y) {
	if (key == 'e'){
		camera1.setupScreenshot();
	}
    
    if (key == 'q'){
        cout << "Thank you for playing!" <<endl;
        exit(1);
    }
 
 	if (key == 'w')
 	{
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        float xposFuture = xpos + float(sin(yrotrad)) * cScale;
        float zposFuture = zpos - float(cos(yrotrad)) * cScale;
        float yposFuture = ypos - float(sin(xrotrad));
        
        if (hField.collisionDetection(xposFuture, yposFuture, zposFuture)){
            
        }
        else{
            xpos += float(sin(yrotrad)) * cScale;
            zpos -= float(cos(yrotrad)) * cScale;
            ypos -= float(sin(xrotrad));
            bounce += 0.04;
        }
	 }
 
 	if (key == 's')
 	{
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        float xposFuture = xpos - float(sin(yrotrad)) * cScale;
        float zposFuture = zpos + float(cos(yrotrad)) * cScale;
        float yposFuture = ypos + float(sin(xrotrad));
        
        if (hField.collisionDetection(xposFuture, yposFuture, zposFuture)){
            
        }
        else{
            xpos -= float(sin(yrotrad)) * cScale;
            zpos += float(cos(yrotrad)) * cScale;
            ypos += float(sin(xrotrad));
            bounce += 0.04;
        }
 	}
 
 	if (key == 'd')
 	{
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        float xposFuture = xpos + float(cos(yrotrad)) * cScale;
        float zposFuture = zpos + float(sin(yrotrad)) * cScale;
        
        if (hField.collisionDetection(xposFuture, ypos, zposFuture)){
            
        }
        else{
            xpos += float(cos(yrotrad)) * cScale;
            zpos += float(sin(yrotrad)) * cScale;
        }
 	}
 
 	if (key == 'a')
 	{
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        float xposFuture = xpos - float(cos(yrotrad)) * cScale;
        float zposFuture = zpos - float(sin(yrotrad)) * cScale;
        
        if (hField.collisionDetection(xposFuture, ypos, zposFuture)){
            
        }
        else{
            xpos -= float(cos(yrotrad)) * cScale;
            zpos -= float(sin(yrotrad)) * cScale;
        }
 	}
 
}

//a standard function for handling reshaping of the window
//we will probably want w and h to be global variables
//this is for the benefit of screenshot function as it needs w and h
//basically, as the screen is reshaped we need to adapt the screenshot function
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
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
   	glutCreateWindow("A basic OpenGL Window");
	Init();
   	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(orientMe);
   	glutMainLoop ();
   	return 0;
}
