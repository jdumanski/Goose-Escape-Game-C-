//THIS IS THE START OF THE gooseEscapeGamePlay.hpp FILE
#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

/*This file is all about the game world.  You will modify this to add
    constants and function prototypes.  Modify gooseGamePlay.cpp to
	actually add functionality.
*/

/*
    Declare constants to indicate various game world features in the board
    array.  Modify them to fit what you would like to do in the game.  You can
    change the type if you choose to store your game board as something other
    than intengers.
*/	
// Going further:  Learn how to use an enum for these values
//represents the walls int he game board array
const char SHALL_NOT_PASS = 1; 
//these are the coordinates of the safe space character
const int WINX = 56;
const int WINY = 10;
//represents the winner/safe space in the game board array
const int WINNER = 2;
//the x and y values of the top left corner of wall1, and wall length and thickness
const int WALL1Y = 5;
const int WALL1X = 30;
const int WALL1THICK = 3;
const int WALL1_LENGTH = 20;
//declares starting coordinates of the player and monster
const int PLAYERX_START = 10;
const int PLAYERY_START = 10;
const int MONSTERX_START = 70;
const int MONSTERY_START = 20;

//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('W');

//descriptions of all functions listed below are in the corresponding cpp file
bool win(Actor const & player);

void chasingPerson(Actor const & player, Actor & monster, 
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

bool captured(Actor const & player, Actor const & monster);

void setup(int x_coord, int y_coord, int arrayIndicator, 
char entity, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

void movePlayer(int key, Actor & player, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

void wallSet(int row, int col, int thickness, int wall_length,
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

#endif

//THIS IS THE END OF THE gooseEscapeGamePlay.hpp FILE
