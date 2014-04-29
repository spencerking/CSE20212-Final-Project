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

//default constructor
GameController::GameController(){
	srand(time(NULL)); //seeds with time
    
    //push all of the appropriate models into vectors
    groundPokemon.push_back(pikachu);
    groundPokemon.push_back(pikachu2);
    groundPokemon.push_back(pikachu3);
    groundPokemon.push_back(pikachu4);
    groundPokemon.push_back(pikachu5);
    groundPokemon.push_back(pikachu6);
    groundPokemon.push_back(wooper);
    groundPokemon.push_back(diglet);
   // groundPokemon.push_back(eevee);
    groundPokemon.push_back(flareon);
    groundPokemon.push_back(muk);
    
    airPokemon.push_back(charizard);
    airPokemon.push_back(charizard2);
   // airPokemon.push_back(beedrill);
    airPokemon.push_back(yanma);
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
    pikachu7.render();
    pikachu8.render();
	xatu.render();
    xatu2.render();
	wooper.render();
	diglet.render();

    //snorlax.render();
   // eevee.render();
    flaafy.render();
    charizard.render();
    charizard2.render();
   // beedrill.render();
    yanma.render();
    flareon.render();
    muk.render();
    tree1.render();
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
    pikachu7.init(315.101, 255.311, 400.397);
    pikachu8.init(357.35, 212.789, 461.827);
	xatu.init(673.699, 222.815, 272.079);
    xatu2.init(443.58, 247.087, 774.515);
	wooper.init(898.486, 2.2964, 361.856);
	diglet.init(933.58, 2.2538, 351.413);
    //snorlax.init(699.59, 17.1487, 58.7353);
   // eevee.init(424.491, 24.2074, 217.821);
    flaafy.init(731.374, 84.9367, 431.661);
    charizard.init(510.612, 6.9801, 73.1485);
    charizard2.init(42.5802, 4.4871, 968.945);
   // beedrill.init(734.951, 218.833, 431.761);
    yanma.init(734.951, 218.833, 431.761);
    flareon.init(705.482, 3.8517, 784.499);
    muk.init(52.3041, 15.3588, 108.124);
    tree1.init(950, 2, 200);
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
    
    vector<Models>::iterator groundIter;

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
    
    //SEG FAULTS
    //I wanted to iterate through all pokémon and give each a different movement
    //makes it more random instead of just assigning the same thing to all pokémon
    //of a specific type
    /*
    for (groundIter =groundPokemon.begin(); groundIter != groundPokemon.end(); ++groundIter){
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
        cout<<"before current"<<endl;
        xCurrent=groundIter->getXpos();
        cout<<"after xcurrent"<<endl;
        yCurrent=groundIter->getYpos();
        zCurrent=groundIter->getZpos();
        cout<<"before future"<<endl;
        xFuture=xChange+xCurrent;
        yFuture=yChange+yCurrent;
        zFuture=zChange+zCurrent;
        cout<<"before collision check"<<endl;
     
        if (GameController::GameCollision(xFuture, yFuture, zFuture)){
     
        }
        else{
        
            groundIter->move(xFuture, yFuture, zFuture);

        }
       
     
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
    pikachu7.setFilename("Pikachu.obj");
    pikachu8.setFilename("Pikachu.obj");
	xatu.setFilename("xatu.obj");
    xatu2.setFilename("xatu.obj");
	diglet.setFilename("Diglett.obj");
    //snorlax.setFilename("Snorlax.obj");
    //eevee.setFilename("eevee.obj");
    flaafy.setFilename("flaafy.obj");
    charizard.setFilename("charizard.obj");
    charizard2.setFilename("charizard.obj");
    //beedrill.setFilename("beedrill.obj");
    yanma.setFilename("yanma.obj");
    flareon.setFilename("flareon.obj");
    muk.setFilename("muk.obj");
    tree1.setFilename("Tree.obj");
}
