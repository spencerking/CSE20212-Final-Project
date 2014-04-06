//significant assistance from: http://www.swiftless.com/tutorials/terrain/3_rendering.html
#include <GL/gl.h>
#include <GL/glut.h>

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
//this is straight from the swiftless tutorial, we will definitely have our own
void camera (void) {
	int posX = (int)xpos;
	int posZ = (int)zpos;
    
	glRotatef(xrot,1.0,0.0,0.0); //rotates on the x-axis
	glRotatef(yrot,0.0,1.0,0.0); //rotates on the y-axis
	glTranslated(-xpos,-ypos,-zpos); //translates the screen to the current camera positon
}

//basic display function, this is also straight from swiftless
//what we already had was very similar to this
//I doubt we can vary this too much
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
//same comments as the display function
void Init (void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    
	hField.Create("heightField.raw", 1024, 1024);
}

//this is how swiftless handled mouse control of the camera
//I already have the basics figured out with arrow keys
//we might want to look into figuring out exactly how this works later
//if we do, we should probably write our own function

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



//I think we already have the keyboard figured out based on Emrich's tutorials
//this is still a good reference though

void keyboard (unsigned char key, int x, int y) {
	if (key=='q'){
		camera1.setupScreenshot();
	}
 
 	if (key == 'w')
 	{
 		float xrotrad, yrotrad;
 		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad)) * cScale;
 		zpos -= float(cos(yrotrad)) * cScale;
		ypos -= float(sin(xrotrad)) ;
 		bounce += 0.04;
		//hField.collisionDetection(xpos, ypos, zpos);
		//cout << xpos << ypos << zpos<<endl;
	 }
 
 	if (key == 's')
 	{
 		float xrotrad, yrotrad;
 		yrotrad = (yrot / 180 * 3.141592654f);
 		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad)) * cScale;
 		zpos += float(cos(yrotrad)) * cScale;
 		ypos += float(sin(xrotrad));
 		bounce += 0.04;
		//hField.collisionDetection(xpos, ypos, zpos);
 	}
 
 	if (key == 'd')
 	{
 		float yrotrad;
 		yrotrad = (yrot / 180 * 3.141592654f);
 		xpos += float(cos(yrotrad)) * cScale;
 		zpos += float(sin(yrotrad)) * cScale;
		//hField.collisionDetection(xpos, ypos, zpos);
 	}
 
 	if (key == 'a')
 	{
 		float yrotrad;
 		yrotrad = (yrot / 180 * 3.141592654f);
 		xpos -= float(cos(yrotrad)) * cScale;
 		zpos -= float(sin(yrotrad)) * cScale;
		//hField.collisionDetection(xpos, ypos, zpos);
 	}
 
}

//a standard function for handling reshaping of the window
//our reshape function was nearly identical to this
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

//the main function, these seem to be pretty standard
//again, ours was nearly identical
int main (int argc, char **argv) {
   	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(1500, 1500);
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
