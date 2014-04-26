

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <vector>
#include "Heightfield.h"
#include "Camera.h"
#include "Skybox.h"
#include "models.h"


class GameController{
public:
    GameController(); //default constructor
    void GameRender(); //renders everying displayed in the game
    void GameInit(); //initializes everything in the game
    int GameCollision(float, float, float); //collision detection
    void GameArrowKeys(int, int, int); //handles arrow key input
    void GameSetNames();
   // void GameKeyboardInput(unsigned char, int, int); //handles keyboard input
    void GameMoveModels(); //moves models
    
private:
    Skybox skybox;
    HeightField hField;
    Camera camera;
    Models pikachu;
    Models pikachu2;
    Models pikachu3;
    Models pikachu4;
    Models pikachu5;
    Models pikachu6;
    Models xatu;
    Models wooper;
    Models PikachuTest;
    Models diglet;
    //Raichu raichu;
   
    vector<Models> groundPokemon;
    
};


#endif 
