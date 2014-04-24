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
#include "Global.h"
#include "Skybox.h"
#include "Camera.h"
#include "Sound.h"
#include "GameController.h"

//instantiate objects
Camera camera;
GameController gamecontroller;
Sound sound;

//basic camera function
//this is straight from the swiftless tutorial
void cameraFunc (void) {
	//int posX = (int)xpos;
	//int posZ = (int)zpos;
    //Unused
    
	glRotatef(xrot,0.1,0.0,0.0); //rotates on the x-axis
	glRotatef(yrot,0.0,0.1,0.0); //rotates on the y-axis
	glTranslated(-xpos,-ypos,-zpos); //translates the screen to the current camera positon
}

//basic display function
void display (void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
    
    cameraFunc();
 
    gamecontroller.GameRender();
    
	glutSwapBuffers();
}

//initialization function
void init (void) {
    // Init lighting
    GLfloat light0_ambient[] = {0.1f, 0.1f, 0.3f, 1.0f};
    GLfloat light0_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0_position[] = {1000.0, 1000.0, 500.0, 0.0};
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
	glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    gamecontroller.GameInit();
    sound.init();
}


//mouse control function based on the swiftless tutorials
void orientMe(int x, int y) {
	//calculates the differences between the current x and y positions
	//and the previous x and y positions
 	float diffx = ((float)x-previousx)*0.5f;
 	float diffy = ((float)y-previousy)*0.5f;

    xrot += diffy;
    yrot += diffx;

    //this prevents the camera from being inverted
    //but it also makes the movement less smooth
    if (diffx<-M_PI){
        diffx += M_PI*2;
    }
    if (diffx>M_PI){
        diffx -= M_PI*2;
    }
    if (diffy<-M_PI*0.49){
        diffy = -M_PI*0.49;
    }
    if (diffy>M_PI*0.49){
        diffy = M_PI*0.49;
    }
    
	//the previous x and y positions become the current x and y positions
    previousx = x;
    previousy = y;
}

//keyboard function based on swiftless and Emrich's tutorials

void keyboard (unsigned char key, int x, int y) {
	if (key == 'e') { //takes a screenshot and play shutter sound
		camera.setupScreenshot();
        sound.shutter();
	}

    if (key == 'm') { //toggle music
        sound.music();
    }
    
    if (key == 'q') { //quits the game
        cout << "Thank you for playing!" << endl;
        exit(1);
    }
 
 	if (key == 'w') //moves the camera forwards
 	{
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * M_PI);
        xrotrad = (xrot / 180 * M_PI);
        float xposFuture = xpos + float(sin(yrotrad)) * cScale;
        float zposFuture = zpos - float(cos(yrotrad)) * cScale;
        float yposFuture = ypos - float(sin(xrotrad));
        
        if (gamecontroller.GameCollision(xposFuture, yposFuture, zposFuture)) {
            
        }
        else {
            xpos += float(sin(yrotrad)) * cScale;
            zpos -= float(cos(yrotrad)) * cScale;
            ypos -= float(sin(xrotrad));
            cout<< "x= "<<xpos<<" y= "<<ypos<<" z= "<<zpos<<endl;
            bounce += 0.04;
        }
	 }
 
 	if (key == 's') //moves the camera backwards
 	{
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * M_PI);
        xrotrad = (xrot / 180 * M_PI);
        float xposFuture = xpos - float(sin(yrotrad)) * cScale;
        float zposFuture = zpos + float(cos(yrotrad)) * cScale;
        float yposFuture = ypos + float(sin(xrotrad));
        
        if (gamecontroller.GameCollision(xposFuture, yposFuture, zposFuture)) {
            
        }
        else {
            xpos -= float(sin(yrotrad)) * cScale;
            zpos += float(cos(yrotrad)) * cScale;
            ypos += float(sin(xrotrad));
            bounce += 0.04;
        }
 	}
 
 	if (key == 'd') //moves the camera to the right
 	{
        float yrotrad;
        yrotrad = (yrot / 180 * M_PI);
        float xposFuture = xpos + float(cos(yrotrad)) * cScale;
        float zposFuture = zpos + float(sin(yrotrad)) * cScale;
        
        if (gamecontroller.GameCollision(xposFuture, ypos, zposFuture)) {
            
        }
        else {
            xpos += float(cos(yrotrad)) * cScale;
            zpos += float(sin(yrotrad)) * cScale;
        }
 	}
 
 	if (key == 'a') //moves the camera to the left
 	{
        float yrotrad;
        yrotrad = (yrot / 180 * M_PI);
        float xposFuture = xpos - float(cos(yrotrad)) * cScale;
        float zposFuture = zpos - float(sin(yrotrad)) * cScale;
        
        if (gamecontroller.GameCollision(xposFuture, ypos, zposFuture)) {
            
        }
        else {
            xpos -= float(cos(yrotrad)) * cScale;
            zpos -= float(sin(yrotrad)) * cScale;
        }
 	}
 
}

//allows for altitude change with up and down arrow keys
void arrowKeys(int key, int x, int y){
    
    //gamecontroller.GameArrowKeys(key, x, y);
    float yposFuture;
    switch(key) {
        //moves the camera directly upwards
        case GLUT_KEY_UP :
            yposFuture=ypos;
            yposFuture += 5.00;
            if (gamecontroller.GameCollision(xpos, yposFuture, zpos)) {
                
            }
            else {
                ypos+=5.00;
            }
            break;
        //moves the camera directly downwards
        case GLUT_KEY_DOWN:
            yposFuture=ypos;
            yposFuture -= 5.00;
            if (gamecontroller.GameCollision(xpos, yposFuture, zpos)) {
                
            }
            else {
                ypos-=5.00;
            }
            break;
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
	glutInitWindowSize(1000, 800);
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
