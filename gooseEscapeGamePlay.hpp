//THIS IS THE START OF THE gooseEscapeGamePlay.hpp FILE
#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include <cstdlib>
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
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1; 
//these are the coordinates of the safe space character
const int WINX = 38;
const int WINY = 9;
//represents the winner/safe space in the game board array
const int WINNER = 2;
//the x and y values of the top left corner of wall1, and wall length and thickness
const int WALL1Y = 5;
const int WALL1X = 30;
const int WALLTHICK = 3;
const int WALL1_LENGTH = 20;

const int WALL2Y = 5;
const int WALL2X = 27;
const int WALL2_LENGTH = 9;

const int WALL3Y = 11;
const int WALL3X = 30;

const int WALL4Y = 5;
const int WALL4X = 47;
const int WALL4_LENGTH = 3;

//declares starting coordinates of the player and monster
const int PLAYERX_START = 10;
const int PLAYERY_START = 10;
const int MONSTERX_START = 70;
const int MONSTERY_START = 20;

const int POWER_UP_LENGTH = 12;

const char PUT_WALL = 'P';
const char DELETE_WALL = 'D';

//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('W');
const int SPEED_CHAR = int('P');
//descriptions of all functions listed below are in the corresponding cpp file

bool win(Actor const & player);

void randomLocation(int & randXcoord, int & randYcoord, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

void chasingPerson(Actor const & player, Actor & monster, 
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

bool captured(Actor const & player, Actor const & monster);


void movePlayer(int key, Actor & player, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

void wallSet(int row, int col, int thickness, int wall_length,
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X], char action);

void randomMove(Actor speedPowerUp);

void playerHitSpeedPow(Actor & player, Actor & powerUp, int & turnCount, int & powSpeedCounter);
void print(int gameBoard[NUM_BOARD_Y][NUM_BOARD_X]);

#endif

//THIS IS THE END OF THE gooseEscapeGamePlay.hpp FILE
