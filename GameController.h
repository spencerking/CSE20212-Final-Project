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
    Models xatu; //the textures don't load completely correctly
    Models wooper;
    Models diglet;
    //Models snorlax; //the textures don't load at all, the model is the right shape
    //Models eevee; //textures don't load, is ridiculously huge
    Models flaafy; //texture is mostly correct
    Models charizard; //texture is mostly correct
    //Models beedrill; //model is massive
    Models yanma; //kinda big, textures aren't too bad
    Models flareon; //pretty big, textures are a little messed up
    Models tree1;
    
    vector<Models> groundPokemon; //vector for storing pokémon that move in x and z direction
    vector<Models> airPokemon; //vector for pokémon that can move in any direction
    
};


#endif 
