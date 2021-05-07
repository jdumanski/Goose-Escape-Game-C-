//THIS THE START OF THE gooseEscapeGamePlay.cpp FILE
#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;

//function thats prints things to the game board-will be used for powerups in week 2
void setup(int x_coord, int y_coord, int arrayIndicator, 
char entity, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
	gameBoard[y_coord][x_coord] = arrayIndicator;
    terminal_put(x_coord,y_coord,entity);
}

//this function ends the game and outputs a message when the player is caught
bool captured(Actor const & player, Actor const & monster)
{
	bool capture = false;
	if(player.get_x() == monster.get_x() && player.get_y() == monster.get_y())
	{
		out.writeLine("The geese have eaten you :/");
		capture = true;
	}
    return capture;
}

//this functions moves the player depending of the user input using the arrow keys
void movePlayer(int key, Actor & player, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -2;
    else if (key == TK_DOWN)
        yMove = 2;
    else if (key == TK_LEFT)
        xMove = -2;
    else if (key == TK_RIGHT)
        xMove = 2;
    /*this if statement only allows the player to move to valid locations. The
    player cannot go through walls or off of the screen*/
    if (player.can_move(xMove, yMove) 
      && gameBoard[player.get_y()+yMove][player.get_x()+xMove] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

/*this function ends the game and outputs a message when the player 
reaches the safe space and wins*/
bool win(Actor const & player)
{
	bool win = false;
	if((player.get_x() == WINX && player.get_y() == WINY))
	{
		out.writeLine("you win :)");
		win = true;
	}
	return win;
}

//sets up the wall obstacles
void wallSet(int row, int col, int thickness, int wall_length,
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
	
	for(int count = 0; count < thickness; count++)
	{
		int store = col;
		while(store < col+wall_length)
		{
			gameBoard[row+count][store] = SHALL_NOT_PASS;
			terminal_put(store,row+count,WALL_CHAR);
			store++;
		}
	}
}

//this function contains an algorithm that makes the monster chase the player
void chasingPerson(Actor const & player, Actor & monster, 
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
	if(monster.get_x()>player.get_x()) // Monster is to the right of player
	{
		if(monster.get_y()>player.get_y()) // Monster is below player
		{
			monster.update_location(-1,-1);
		}
		else if(monster.get_y()<player.get_y()) // Monster is above player
		{
			monster.update_location(-1,1);
		}
		else  // Monster is leveled horizontally with player
		{
			monster.update_location(-1,0);
		}
	}
	else if(monster.get_x()<player.get_x()) // Monster is to the left of player
	{
		if(monster.get_y()>player.get_y()) // Monster is below player
		{
			monster.update_location(1,-1);
		}
		else if(monster.get_y()<player.get_y()) // Monster is above player
		{
			monster.update_location(1,1);
		}
		else // monster is leveled with player horizontally
		{
			monster.update_location(1,0);  
		}
	}
	else // Monster is aligned vertically with the player
	{
		// Monster is below the player
		if(monster.get_y()>player.get_y()) 
		{
			monster.update_location(0,-1);
		}
		// Monster is above the player
		else if(monster.get_y()<player.get_y()) 
		{
			monster.update_location(0,1);
		}
	}
}
//THIS THE END OF THE gooseEscapeGamePlay.cpp FILE
