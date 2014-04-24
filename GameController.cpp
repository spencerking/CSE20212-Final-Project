#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include "GameController.h"
//#include "Global.h"



//default constructor
GameController::GameController(){
	
	
}

//render function
void GameController::GameRender(){
<<<<<<< Updated upstream
	glPushMatrix();
	skybox.render();
	glDisable(GL_LIGHTING);
	hField.render();
	glEnable(GL_LIGHTING);
	pikachu.render();
	pikachu2.render();
	pikachu3.render();
	pikachu4.render();
	pikachu5.render();
	pikachu6.render();
	xatu.render();
	wooper.render();
	PikachuTest.render();
	diglet.render();
	//raichu.render();
	glPopMatrix();
=======
    
    glPushMatrix();
    skybox.render();
    hField.render();
    pikachu.render();
    pikachu2.render();
    pikachu3.render();
    pikachu4.render();
    pikachu5.render();
    pikachu6.render();
    xatu.render();
    wooper.render();
    PikachuTest.render();
    diglet.render();
    
    //raichu.render();
	glPopMatrix();


}

//init function
void GameController::GameInit(){
	// Init objects
	pikachu.init(876.902, 1.9367, 704.263);
	pikachu2.init(870.902, 1.9367, 704.263);
	pikachu3.init(864.902, 1.9367, 704.263);
	pikachu4.init(858.902, 1.9367, 704.263);
	pikachu5.init(852.902, 1.9367, 704.263);
	pikachu6.init(757.385, 84.2711, 503.428);
	xatu.init(673.699, 222.815, 272.079);
	wooper.init(898.486, 2.2964, 361.856);
	PikachuTest.init(882.902, 1.9367, 704.263);
	diglet.init(933.58, 11.2538, 351.413);
	//raichu.init(882.902, 1.9367, 704.263);
	skybox.init();

    
    // Init objects
    pikachu.init(876.902, 1.9367, 704.263);
    pikachu2.init(870.902, 1.9367, 704.263);
    pikachu3.init(864.902, 1.9367, 704.263);
    pikachu4.init(858.902, 1.9367, 704.263);
    pikachu5.init(852.902, 1.9367, 704.263);
    pikachu6.init(757.385, 84.2711, 503.428);
    xatu.init(673.699, 222.815, 272.079);
    wooper.init(898.486, 2.2964, 361.856);
    PikachuTest.init(882.902, 1.9367, 704.263);
    diglet.init(933.58, 1.2538, 351.413);
    //raichu.init(882.902, 1.9367, 704.263);
    skybox.init();
	hField.init("Heightfield/heightField.raw", 1024, 1024, 8);
	
}

//collision detection function
int GameController::GameCollision(float x, float y, float z){
	
	if (hField.collisionDetection(x, y, z)){
		return 1;
	}
	else {
		return 0;
	}
	
}

//handles arrow key input
void GameController::GameArrowKeys(int key, int x, int y){
	/*float yposFuture;
	switch(key) {
			//moves the camera directly upwards
		case GLUT_KEY_UP :
			yposFuture=ypos;
			yposFuture += 5.00;
			if (GameController::GameCollision(xpos, yposFuture, zpos)) {
				
			}
			else {
				ypos+=5.00;
			}
			break;
			//moves the camera directly downwards
		case GLUT_KEY_DOWN:
			yposFuture=ypos;
			yposFuture -= 5.00;
			if (GameController::GameCollision(xpos, yposFuture, zpos)) {
				
			}
			else {
				ypos-=5.00;
			}
			break;
	}*/
}
/*

//handles keyboard input
void GameController::GameKeyboard(unsigned char key, int x, int y){
	
}
*/

void GameController::GameSetNames() {
  
	PikachuTest.setFilename("Pikachu.obj");
	wooper.setFilename("wooper.obj");
	pikachu.setFilename("Pikachu.obj");
	pikachu2.setFilename("Pikachu.obj");
	pikachu3.setFilename("Pikachu.obj");
	pikachu4.setFilename("Pikachu.obj");
	pikachu5.setFilename("Pikachu.obj");
	pikachu6.setFilename("Pikachu.obj");
	xatu.setFilename("xatu.obj");
	diglet.setFilename("Diglett.obj");
}
