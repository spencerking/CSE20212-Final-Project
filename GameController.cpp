#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include "GameController.h"
#include <vector>
#include <iterator>
#include <iostream>
//#include "Global.h"
float ynew=2.2964;


//default constructor
GameController::GameController(){
	srand(time(NULL)); //seeds with time
    groundPokemon.push_back(pikachu);
    groundPokemon.push_back(pikachu2);
    groundPokemon.push_back(pikachu3);
    groundPokemon.push_back(pikachu4);
    groundPokemon.push_back(pikachu5);
    groundPokemon.push_back(pikachu6);
    groundPokemon.push_back(wooper);
    groundPokemon.push_back(diglet);
   // groundPokemon.push_back(eevee);
}

//render function
void GameController::GameRender(){
	glPushMatrix();
	glDisable(GL_LIGHTING);
	skybox.render();
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
	diglet.render();
	//raichu.render();
    snorlax.render();
   // eevee.render();
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
	pikachu6.init(882.902, 1.9367, 704.263);
	xatu.init(673.699, 222.815, 272.079);
	wooper.init(898.486, 2.2964, 361.856);
	diglet.init(933.58, 11.2538, 351.413);
	//raichu.init(882.902, 1.9367, 704.263);
    snorlax.init(699.59, 17.1487, 58.7353);
   // eevee.init(424.491, 24.2074, 217.821);
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

//model movement function
void GameController::GameMoveModels(){
    
    float xChange;
    float yChange;
    float zChange;
    float xCurrent;
    float yCurrent;
    float zCurrent;
    float xFuture;
    float yFuture;
    float zFuture;
    
    vector<int>::const_iterator groundIter;

     if (rand()%100<50){
        xChange=-5.0;
        yChange=5.0;
        zChange=0.0;
         cout<<"wooper up back"<<endl;
    }
    else {
        xChange=0.0;
        yChange=10.0;
        zChange=0.0;
        cout<<"wooper way up"<<endl;
    }

    xCurrent=wooper.getXpos();
    yCurrent=wooper.getYpos();
    zCurrent=wooper.getZpos();
    
    xFuture=xChange+xCurrent;
    yFuture=yChange+yCurrent;
    zFuture=zChange+zCurrent;
    
    if (GameController::GameCollision(xFuture, yFuture, zFuture)){
        
    }
    else{
            wooper.move(xFuture, yFuture, zFuture);
    }
    
    //I wanted to iterate through all pokémon and give each a different movement
    //makes it more random instead of just assigning the same thing to all pokémon
    //of a specific type
    /*
    while (groundIter != groundPokemon.end()){
        if (rand()%100<50){
            xChange=-5.0;
            yChange=0.0;
            zChange=0.0;
        }
        else {
            xChange=0.0;
            yChange=5.0;
            zChange=0.0;
        }
        groundPokemon[groundIter.move(xChange, yChange, zChange)];
        
    }*/

    
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
  
	wooper.setFilename("wooper.obj");
	pikachu.setFilename("Pikachu.obj");
	pikachu2.setFilename("Pikachu.obj");
	pikachu3.setFilename("Pikachu.obj");
	pikachu4.setFilename("Pikachu.obj");
	pikachu5.setFilename("Pikachu.obj");
    pikachu6.setFilename("Pikachu.obj");
	xatu.setFilename("xatu.obj");
	diglet.setFilename("Diglett.obj");
    snorlax.setFilename("Snorlax.obj");
    //eevee.setFilename("eevee.obj");
}
