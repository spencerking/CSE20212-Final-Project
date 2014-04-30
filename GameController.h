#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <vector>
#include <math.h>
#include "Heightfield.h"
#include "Sound.h"
#include "Camera.h"
#include "models.h"



class GameController{
public:
    GameController(); //default constructor
    void GameRender(); //renders everying displayed in the game
    void GameInit(); //initializes everything in the game
    int GameCollision(float, float, float); //collision detection
    void GameArrowKeys(int, int, int); //handles arrow key input
    void GameKeyboardInput(unsigned char, int, int); //handles keyboard input
    void GameMouseOrientation(int, int); //handles the change in mouse orientation
    void GameUpdateCamera(void); //updates the camera
    void GameMoveModels(); //moves models
    void GameBGM(); //plays the BGM
    void GameShutterSound(); //plays the shutter sound
    void GameScreenshot(); //takes a screenshot
    
private:
    HeightField hField;
    Sound sound;
    Camera camera;
    Models *pikachu;
    Models *pikachu2;
    Models *pikachu3;
    Models *pikachu4;
    Models *pikachu5;
    Models *pikachu6;
    Models *pikachu7;
    Models *pikachu8;
    Models *xatu; 
    Models *xatu2;
    Models *wooper;
    Models *diglet;
    Models *flaafy; 
    Models *charizard; 
    Models *charizard2;
    Models *yanma; 
    Models *flareon; 
    Models *muk;
    Models *tree1;
    Models *latios;
    Models *blaziken;
    Models *typhlosion;
    Models *quilava;
    Models *luckitung;
    
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
