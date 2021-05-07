//THIS IS THE START OF THE gooseEscapeMain.cpp FILE
#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

Console out;

int main()
{
    terminal_open();
  	terminal_set(SETUP_MESSAGE);
  	
    //make the player
	Actor player(PLAYER_CHAR, PLAYERX_START, PLAYERY_START); 
	
	//make the monster
	Actor monster(MONSTER_CHAR, MONSTERX_START, MONSTERY_START);

	//declares array for game board
  	int gameBoard[NUM_BOARD_Y][NUM_BOARD_X] = {0};
  	
	//printing wall1 to game board
	wallSet(WALL1Y, WALL1X, WALL1THICK, WALL1_LENGTH, gameBoard);

	//makes safe space 
	setup(WINX, WINY, WINNER, WIN_CHAR, gameBoard);
  	
	// Printing the instructions
    out.writeLine("Escape the Goose! ");
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");

	//this variable stores the user key press values
    int keyEntered = TK_UP;
	
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
                    && !captured(player,monster) && !win(player))
	{	
	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
        	/*ensures that the monster character does not replace the
        	winner or wall characters when it passes through them*/
        	wallSet(WALL1Y, WALL1X, WALL1THICK, WALL1_LENGTH, gameBoard);
        	terminal_put(WINX, WINY, WIN_CHAR);
            // move the player
    	    movePlayer(keyEntered, player, gameBoard);
    	    //moves the monster to chase the player
    	    if(keyEntered==TK_UP||keyEntered==TK_DOWN||keyEntered==TK_LEFT||
    	    keyEntered==TK_RIGHT)
			{
    	    	chasingPerson(player, monster, gameBoard);
			}	
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
        out.writeLine("Game has ended");
	
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }
	//game is done and is closed
    terminal_close();
}
//THIS IS THE END OF THE gooseEscapeMain.cpp FILE
