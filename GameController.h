#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <vector>
#include <math.h>
#include "Heightfield.h"
#include "Sound.h"
#include "Camera.h"
//#include "Skybox.h"
#include "models.h"



class GameController{
public:
    GameController(); //default constructor
    void GameRender(); //renders everying displayed in the game
    void GameInit(); //initializes everything in the game
    int GameCollision(float, float, float); //collision detection
    void GameArrowKeys(int, int, int); //handles arrow key input
  //  void GameSetNames();
    void GameKeyboardInput(unsigned char, int, int); //handles keyboard input
    void GameMouseOrientation(int, int); //handles the change in mouse orientation
    void GameUpdateCamera(void); //updates the camera
    void GameMoveModels(); //moves models
    void GameBGM(); //plays the BGM
    void GameShutterSound(); //plays the shutter sound
    void GameScreenshot(); //takes a screenshot
    
private:
    //Skybox skybox;
    HeightField hField;
    Sound sound;
    Camera camera;
    Models *pikachu;
    Models *pikachu2;
    Models *pikachu3;
    Models *pikachu4;
    Models *pikachu5;
    Models *pikachu6;
    Models *pikachu7; //this one is on a mountain, don't let it move
    Models *pikachu8; //same
    Models *xatu; //the textures don't load completely correctly
    Models *xatu2;
    Models *wooper;
    Models *diglet;
    Models *flaafy; //texture is mostly correct
    Models *charizard; //texture is mostly correct
    Models *charizard2;
    Models *yanma; //kinda big, textures aren't too bad
    Models *flareon; //pretty big, textures are a little messed up
    Models *muk;
    Models *tree1;
    
    vector<Models*> groundPokemon; //vector for storing pokémon that move in x and z direction
    vector<Models*> airPokemon; //vector for pokémon that can move in any direction
    vector<Models*> motionlessModels; //vector of models that won't move

    Models *plant1;
    Models *plant2;
    Models *plant3;
    Models *plant4;
    Models *plant5;
    Models *plant6;
    Models *plant7;
    Models *plant8;
    Models *flower;
  
    
};


#endif 
