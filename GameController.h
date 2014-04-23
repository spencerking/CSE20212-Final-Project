

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include "Heightfield.h"
#include "Camera.h"
#include "Skybox.h"
#include "Pikachu.h"
#include "Xatu.h"
#include "Wooper.h"
#include "Raichu.h"
class GameController{
public:
    GameController(); //default constructor
    void GameRender(); //renders everying displayed in the game
    void GameInit(); //initializes everything in the game
    int GameCollision(float, float, float); //collision detection
    void GameArrowKeys(int, int, int); //handles arrow key input
   // void GameKeyboardInput(unsigned char, int, int); //handles keyboard input
    
private:
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
   
    
};


#endif 