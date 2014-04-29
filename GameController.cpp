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
    pikachu = new Models();
    pikachu2 = new Models();
    pikachu3 = new Models();
    pikachu4 = new Models();
    pikachu5 = new Models();
    pikachu6 = new Models();
    pikachu7 = new Models();
    pikachu8 = new Models();
    wooper = new Models();
    diglet = new Models();
    flareon = new Models();
    muk = new Models();
    charizard = new Models();
    charizard2 = new Models();
    yanma = new Models();
    xatu = new Models();
    xatu2 = new Models();
    flaafy = new Models();
    tree1 = new Models();
    plant1 = new Models();
    plant2 = new Models();
    plant3 = new Models();
    plant4 = new Models();
    plant5 = new Models();
    plant6 = new Models();
    plant7 = new Models();
    plant8 = new Models();
    flower = new Models();

    
    groundPokemon.push_back(pikachu);
    groundPokemon.push_back(pikachu2);
    groundPokemon.push_back(pikachu3);
    groundPokemon.push_back(pikachu4);
    groundPokemon.push_back(pikachu5);
    groundPokemon.push_back(pikachu6);
    groundPokemon.push_back(wooper);
    groundPokemon.push_back(diglet);
    groundPokemon.push_back(flareon);
    groundPokemon.push_back(muk);
    
    airPokemon.push_back(charizard);
    airPokemon.push_back(charizard2);
    airPokemon.push_back(yanma);

    
    motionlessModels.push_back(pikachu7);
    motionlessModels.push_back(pikachu8);
    motionlessModels.push_back(xatu);
    motionlessModels.push_back(xatu2);
    motionlessModels.push_back(flaafy);
    motionlessModels.push_back(tree1);
    motionlessModels.push_back(plant1);
    motionlessModels.push_back(plant2);
    motionlessModels.push_back(plant3);
    motionlessModels.push_back(plant4);
    motionlessModels.push_back(plant5);
    motionlessModels.push_back(plant6);
    motionlessModels.push_back(plant7);
    motionlessModels.push_back(plant8);
    motionlessModels.push_back(flower);
    
    
    wooper->setFilename("wooper.obj");
	pikachu->setFilename("Pikachu.obj");
	pikachu2->setFilename("Pikachu.obj");
	pikachu3->setFilename("Pikachu.obj");
	pikachu4->setFilename("Pikachu.obj");
	pikachu5->setFilename("Pikachu.obj");
    pikachu6->setFilename("Pikachu.obj");
    pikachu7->setFilename("Pikachu.obj");
    pikachu8->setFilename("Pikachu.obj");
	xatu->setFilename("xatu.obj");
    xatu2->setFilename("xatu.obj");
	diglet->setFilename("Diglett.obj");
    flaafy->setFilename("flaafy.obj");
    charizard->setFilename("charizard.obj");
    charizard2->setFilename("charizard.obj");
    yanma->setFilename("yanma.obj");
    flareon->setFilename("flareon.obj");
    muk->setFilename("muk.obj");
    tree1->setFilename("Tree.obj");
    
    plant1->setFilename("Hemp.obj");
    plant2->setFilename("Hemp.obj");
    plant3->setFilename("Hemp.obj");
    plant4->setFilename("Hemp.obj");
    plant5->setFilename("Hemp.obj");
    plant6->setFilename("Hemp.obj");
    plant7->setFilename("Hemp.obj");
    plant8->setFilename("Hemp.obj");
    //rock.setFilename("Large Rock.obj");
    flower->setFilename("SouthernFlower.obj");


}

//render function
void GameController::GameRender(){
    
    vector<Models*>::iterator groundRenderIter;
    vector<Models*>::iterator airRenderIter;
    vector<Models*>::iterator motionlessRenderIter;
    
	glPushMatrix();
	glDisable(GL_LIGHTING);
	//skybox.render();
	hField.render();
	glEnable(GL_LIGHTING);

  
    //render the ground pokemon
    for(int n = 0; n < groundPokemon.size(); n++) {
        Models* groundRenderIter = groundPokemon[n];
            
        groundRenderIter->render();
        
    }
    
    //render the air pokemon
    for(int n = 0; n < airPokemon.size(); n++) {
        Models* airRenderIter = airPokemon[n];
        
        airRenderIter->render();
        
    }
    
    //render all other models
    for(int n = 0; n < motionlessModels.size(); n++) {
        Models* motionlessRenderIter = motionlessModels[n];
        
        motionlessRenderIter->render();
        
    }
    
    glPopMatrix();


}

//init function
void GameController::GameInit(){
	// Init objects

	pikachu->init(876.902, 1.9367, 704.263);
	pikachu2->init(870.902, 1.9367, 704.263);
	pikachu3->init(864.902, 1.9367, 704.263);
	pikachu4->init(858.902, 1.9367, 704.263);
	pikachu5->init(852.902, 1.9367, 704.263);
	pikachu6->init(882.902, 1.9367, 704.263);
    pikachu7->init(315.101, 255.311, 400.397);
    pikachu8->init(357.35, 212.789, 461.827);
	xatu->init(673.699, 222.815, 272.079);
    xatu2->init(443.58, 247.087, 774.515);
	wooper->init(898.486, 2.2964, 361.856);
	diglet->init(933.58, 2.2538, 351.413);
    flaafy->init(731.374, 84.9367, 431.661);
    charizard->init(510.612, 6.9801, 73.1485);
    charizard2->init(42.5802, 4.4871, 968.945);
    yanma->init(734.951, 218.833, 431.761);
    flareon->init(705.482, 3.8517, 784.499);
    muk->init(52.3041, 15.3588, 108.124);
    tree1->init(950, 2, 200);

    plant1->init(415.529,29.2095,610.513);
    plant2->init(415.529,29.2095,600.513);
    plant3->init(425.529,29.2095,600.513);
    plant4->init(425.529,29.2095,610.513);
    plant5->init(421.529,29.2095,610.513);
    plant6->init(421.529,29.2095,600.513);
    plant7->init(415.529,30.2095,604.513);
    plant8->init(425.529,30.2095,605.513);
    flower->init(420.0,30.0,605.0);
    //rock.init(908.0,6.81,400.551);


	//skybox.init();
	hField.init("Heightfield/heightField.raw", 1024, 1024, 8);
    sound.init();

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
    
    vector<Models*>::iterator groundIter;
    vector<Models*>::iterator airIter;

    //I wanted to iterate through all pokémon and give each a different movement
    //makes it more random instead of just assigning the same thing to all pokémon
    //of a specific type
    
    //random movement for ground based pokemon
    for(int n = 0; n < groundPokemon.size(); n++) {
        Models* groundIter = groundPokemon[n];
        if (rand()%100<20){
            xChange=5.0;
            yChange=10.0;
            zChange=2.0;
        }
        else if (rand()%100>20 && rand()%100<30){
            xChange=10.0;
            yChange=10.0;
            zChange=8.0;
        }
        else if (rand()%100>30 && rand()%100<40){
            xChange=-10.0;
            yChange=10.0;
            zChange=-8.0;
        }
        else if (rand()%100>40 && rand()%100<50){
            xChange=-6.0;
            yChange=10.0;
            zChange=8.0;
        }
        else if (rand()%100>50 && rand()%100<60){
            xChange=-9.0;
            yChange=10.0;
            zChange=4.0;
        }
        else if (rand()%100>50 && rand()%100<60){
            xChange=3.0;
            yChange=10.0;
            zChange=-6.0;
        }
        else{
            xChange=9.0;
            yChange=10.0;
            zChange=0.0;
        }

        xCurrent=groundIter->getXpos();
        yCurrent=groundIter->getYpos();
        zCurrent=groundIter->getZpos();

        xFuture=xChange+xCurrent;
        yFuture=yChange+yCurrent;
        zFuture=zChange+zCurrent;
     
        if (GameController::GameCollision(xFuture, yFuture, zFuture)){
            //cout << "collision detected"<<endl;
        }
        else{
            //cout <<"collision free"<<endl;
        
            groundIter->move(xFuture, yFuture-10, zFuture);

        }
       
     
    }
    
    //random movement for air based pokemon
    for(int n = 0; n < airPokemon.size(); n++) {
        Models* airIter = airPokemon[n];
        if (rand()%100<20){
            xChange=5.0;
            yChange=10.0;
            zChange=2.0;
        }
        else if (rand()%100>20 && rand()%100<30){
            xChange=10.0;
            yChange=10.0;
            zChange=8.0;
        }
        else if (rand()%100>30 && rand()%100<40){
            xChange=-10.0;
            yChange=20.0;
            zChange=-8.0;
        }
        else if (rand()%100>40 && rand()%100<50){
            xChange=-6.0;
            yChange=-10.0;
            zChange=8.0;
        }
        else if (rand()%100>50 && rand()%100<60){
            xChange=0.0;
            yChange=-20.0;
            zChange=0.0;
        }
        else if (rand()%100>60 && rand()%100<70){
            xChange=0.0;
            yChange=-20.0;
            zChange=-10.0;
        }
        else if (rand()%100>70 && rand()%100<80){
            xChange=-9.0;
            yChange=-10.0;
            zChange=-3.0;
        }
        else{
            xChange=9.0;
            yChange=-10.0;
            zChange=0.0;
        }
        
        xCurrent=airIter->getXpos();
        yCurrent=airIter->getYpos();
        zCurrent=airIter->getZpos();

        xFuture=xChange+xCurrent;
        yFuture=yChange+yCurrent;
        zFuture=zChange+zCurrent;
        
        if (GameController::GameCollision(xFuture, yFuture, zFuture)){
            //cout << "collision detected"<<endl;
        }
        else{
            //cout <<"collision free"<<endl;
            
            airIter->move(xFuture, yFuture, zFuture);
            
        }
        
        
    }


    
}

//plays the BGM
void GameController::GameBGM(){
    sound.music();
    
}


//plays the shutter sound
void GameController::GameShutterSound(){
   sound.shutter();
    
}

//takes a screenshot
void GameController::GameScreenshot(){
    camera.setupScreenshot();
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


/*
void GameController::GameSetNames() {
  

	wooper->setFilename("wooper.obj");
	pikachu->setFilename("Pikachu.obj");
	pikachu2->setFilename("Pikachu.obj");
	pikachu3->setFilename("Pikachu.obj");
	pikachu4->setFilename("Pikachu.obj");
	pikachu5->setFilename("Pikachu.obj");
    pikachu6->setFilename("Pikachu.obj");
    pikachu7->setFilename("Pikachu.obj");
    pikachu8->setFilename("Pikachu.obj");
	xatu->setFilename("xatu.obj");
    xatu2->setFilename("xatu.obj");
	diglet->setFilename("Diglett.obj");
    flaafy->setFilename("flaafy.obj");
    charizard->setFilename("charizard.obj");
    charizard2->setFilename("charizard.obj");
    yanma->setFilename("yanma.obj");
    flareon->setFilename("flareon.obj");
    muk->setFilename("muk.obj");
    tree1->setFilename("Tree.obj");

    plant1->setFilename("Hemp.obj");
    plant2->setFilename("Hemp.obj");
    plant3->setFilename("Hemp.obj");
    plant4->setFilename("Hemp.obj");
    plant5->setFilename("Hemp.obj");
    plant6->setFilename("Hemp.obj");
    plant7->setFilename("Hemp.obj");
    plant8->setFilename("Hemp.obj");
    //rock.setFilename("Large Rock.obj");
    flower->setFilename("SouthernFlower.obj");

}*/
