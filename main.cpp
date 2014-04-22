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
#include "Object.h"
#include "Skybox.h"
#include "Heightfield.h"
#include "Camera.h"
#include "Sound.h"
#include "Pikachu.h"
#include "Xatu.h"
#include "Wooper.h"
#include "Raichu.h"


//global variables for camera control and starting position
float xpos = 1000.00;
float ypos = 51.594;
float zpos = 320.00;
float xrot = 758;
float yrot = 238;
float angle=0.0;
float previousx;
float previousy;

float bounce;
float cScale = 5.0; //multiplier for the speed of camera movement

//instantiate objects
Skybox skybox;
HeightField hField;
Camera camera;
Pikachu pikachu;
Pikachu pikachu2;
Pikachu pikachu3;
Pikachu pikachu4;
Pikachu pikachu5;
Xatu xatu;
Wooper wooper;
//Raichu raichu;
Sound sound;

//basic camera function
//this is straight from the swiftless tutorial
void cameraFunc (void) {
	int posX = (int)xpos;
	int posZ = (int)zpos;
    
	glRotatef(xrot,1.0,0.0,0.0); //rotates on the x-axis
	glRotatef(yrot,0.0,1.0,0.0); //rotates on the y-axis
	glTranslated(-xpos,-ypos,-zpos); //translates the screen to the current camera positon
}

//basic display function
void display (void) {
	glClearColor (0.0,0.0,0.0,1.0); //black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
   	glLoadIdentity();
    
    cameraFunc();
	glPushMatrix();
        skybox.render();
        hField.render();
        pikachu.render();
        pikachu2.render();
        pikachu3.render();
        pikachu4.render();
        pikachu5.render();
        xatu.render();
        wooper.render();
        //raichu.render();
	glPopMatrix();
    
	glutSwapBuffers();
}

//initialization function
void init (void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
    pikachu.init(876.902, 1.9367, 704.263);
    pikachu2.init(870.902, 1.9367, 704.263);
    pikachu3.init(864.902, 1.9367, 704.263);
    pikachu4.init(858.902, 1.9367, 704.263);
    pikachu5.init(852.902, 1.9367, 704.263);
    xatu.init(673.699, 222.815, 272.079);
    wooper.init(898.486, 2.2964, 361.856);
    //raichu.init(882.902, 1.9367, 704.263);
    skybox.init();
	hField.init("Heightfield/heightField.raw", 1024, 1024, 8);
    sound.init();
}


//mouse control function based on the swiftless tutorials
void orientMe(int x, int y) {
	//calculates the differences between the current x and y positions
	//and the previous x and y positions
 	int diffx = x-previousx;
 	int diffy = y-previousy;

    //this prevents the camera from being inverted
    //but it also makes the movement less smooth
   /* if (diffx<-M_PI){
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
    }*/
    
	//the previous x and y positions become the current x and y positions
    previousx = x;
    previousy = y;
    xrot += (float) diffy;
    yrot += (float) diffx;
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
        
        if (hField.collisionDetection(xposFuture, yposFuture, zposFuture)) {
            
        }
        else {
            xpos += float(sin(yrotrad)) * cScale;
            zpos -= float(cos(yrotrad)) * cScale;
            ypos -= float(sin(xrotrad));
            cout<< "x= "<<xpos<<"y= "<<ypos<<"z= "<<zpos<<endl;
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
        
        if (hField.collisionDetection(xposFuture, yposFuture, zposFuture)) {
            
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
        
        if (hField.collisionDetection(xposFuture, ypos, zposFuture)) {
            
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
        
        if (hField.collisionDetection(xposFuture, ypos, zposFuture)) {
            
        }
        else {
            xpos -= float(cos(yrotrad)) * cScale;
            zpos -= float(sin(yrotrad)) * cScale;
        }
 	}
 
}

//allows for altitude change with up and down arrow keys
void arrowKeys(int key, int x, int y){
    float yposFuture;
    switch(key) {
        //moves the camera directly upwards
        case GLUT_KEY_UP :
            yposFuture=ypos;
            yposFuture += 5.00;
            if (hField.collisionDetection(xpos, yposFuture, zpos)) {
                
            }
            else {
                ypos+=5.00;
            }
            break;
        //moves the camera directly downwards
        case GLUT_KEY_DOWN:
            yposFuture=ypos;
            yposFuture -= 5.00;
            if (hField.collisionDetection(xpos, yposFuture, zpos)) {
                
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
   	glutMainLoop ();
   	return 0;
}
