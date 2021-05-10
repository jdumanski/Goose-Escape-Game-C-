//THIS THE START OF THE gooseEscapeGamePlay.cpp FILE
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;

void print(int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
	for(int coord_Y = 0; coord_Y < NUM_BOARD_Y; coord_Y++)
	{
		for(int coord_X = 0; coord_X < NUM_BOARD_X; coord_X++)
		{
			if(gameBoard[coord_Y][coord_X]==SHALL_NOT_PASS)
			{
				terminal_put(coord_X, coord_Y, WALL_CHAR);
			}
			else if(gameBoard[coord_Y][coord_X]==WINNER)
			{
				terminal_put(coord_X, coord_Y, WIN_CHAR);
			}
		}
	}
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

void randomLocation(int & randXcoord, int & randYcoord, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
	bool search = true;
	srand(time(0));
	do
	{
		randXcoord = (rand()%NUM_BOARD_X);
		randYcoord = (rand()%NUM_BOARD_Y);
		if((randXcoord > WALL4X+WALLTHICK || randXcoord < WALL2X) && 
		(randYcoord > WALL3Y+WALLTHICK || randYcoord < WALL1Y))
		{
			search = false;	
		}
	}
	while(search);
}

void playerHitSpeedPow(Actor & player, Actor & powerUp, int & turnCount,
int & powSpeedCounter)
{
	if(powerUp.get_active()==true)
	{
		powSpeedCounter++;
		player.changeSpeed(SPEED2);
		turnCount = POWER_UP_LENGTH;
		powerUp.set_active(false);	
	}
}

//this functions moves the player depending of the user input using the arrow keys
void movePlayer(int key, Actor & player, int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
    int yMove = 0, xMove = 0;
    int pSpeed = player.get_speed();
    if (key == TK_UP)
        yMove = -pSpeed;
    else if (key == TK_DOWN)
        yMove = pSpeed;
    else if (key == TK_LEFT)
        xMove = -pSpeed;
    else if (key == TK_RIGHT)
        xMove = pSpeed;
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
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X], char action)
{	
	for(int count = 0; count < thickness; count++)
	{
		int store = col;
		while(store < col+wall_length)
		{
			if(action=='P')
			{
				gameBoard[row+count][store] = SHALL_NOT_PASS;
			}
			else if(action=='D')
			{
				gameBoard[row+count][store] = EMPTY;
				terminal_clear_area(col, row, wall_length, thickness);
			}
			store++;
		}
	}
}

//this function contains an algorithm that makes the monster chase the player
void chasingPerson(Actor const & player, Actor & monster, 
int gameBoard[NUM_BOARD_Y][NUM_BOARD_X])
{
	int mSpeed = monster.get_speed();
	if(monster.get_x()>player.get_x()) // Monster is to the right of player
	{
		if(monster.get_y()>player.get_y()) // Monster is below player
		{
			monster.update_location(-mSpeed,-mSpeed);
		}
		else if(monster.get_y()<player.get_y()) // Monster is above player
		{
			monster.update_location(-mSpeed,mSpeed);
		}
		else  // Monster is leveled horizontally with player
		{
			monster.update_location(-mSpeed,0);
		}
	}
	else if(monster.get_x()<player.get_x()) // Monster is to the left of player
	{
		if(monster.get_y()>player.get_y()) // Monster is below player
		{
			monster.update_location(mSpeed,-mSpeed);
		}
		else if(monster.get_y()<player.get_y()) // Monster is above player
		{
			monster.update_location(mSpeed,mSpeed);
		}
		else // monster is leveled with player horizontally
		{
			monster.update_location(mSpeed,0);  
		}
	}
	else // Monster is aligned vertically with the player
	{
		// Monster is below the player
		if(monster.get_y()>player.get_y()) 
		{
			monster.update_location(0,-mSpeed);
		}
		// Monster is above the player
		else if(monster.get_y()<player.get_y()) 
		{
			monster.update_location(0,mSpeed);
		}
	}
}
//THIS THE END OF THE gooseEscapeGamePlay.cpp FILE
