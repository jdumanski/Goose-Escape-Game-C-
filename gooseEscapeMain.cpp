//THIS IS THE START OF THE gooseEscapeMain.cpp FILE
#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
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
	Actor player(PLAYER_CHAR, PLAYERX_START, PLAYERY_START, SPEED1); 
	
	//make the monster
	Actor monster(MONSTER_CHAR, MONSTERX_START, MONSTERY_START, SPEED1);
		//declares array for game board
  	int gameBoard[NUM_BOARD_Y][NUM_BOARD_X] = {0};
  	
	int randomX = 0;
	int randomY = 0;
	randomLocation(randomX, randomY, gameBoard);

	Actor speedPowerUp(SPEED_CHAR, randomX, randomY, SPEED1);
  	gameBoard[WINY][WINX] = WINNER;
  	wallSet(WALL1Y, WALL1X, WALLTHICK, WALL1_LENGTH, gameBoard, PUT_WALL);
  	wallSet(WALL2Y, WALL2X, WALL2_LENGTH, WALLTHICK, gameBoard, PUT_WALL);
	wallSet(WALL3Y, WALL3X, WALLTHICK, WALL1_LENGTH, gameBoard, PUT_WALL);	
	wallSet(WALL4Y, WALL4X, WALL2_LENGTH, WALLTHICK, gameBoard, PUT_WALL);
  	
	//printing all non moving entities to game board
	print(gameBoard);
  	
	// Printing the instructions
    out.writeLine("Escape the Goose! ");
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");
	//this variable stores the user key press values
	int powSpeedCounter = 0;
    int keyEntered = TK_UP;
    int turnCount = -2;
    bool keyStroke = true;
    int showPow = -1;
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
          && !captured(player,monster) && !win(player))
	{	
	    // get player key press
	    keyEntered = terminal_read();
        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
        	/*ensures that the monster character does not replace the
        	winner or wall characters when it passes through them*/
        	print(gameBoard);
        	if(monster.get_x()==speedPowerUp.get_x()&&monster.get_y()==speedPowerUp.get_y())
        	{
        		showPow = 2;
        	}
		    if(showPow > 0)
		   	{
		      	showPow--;
			}
			if(showPow==0)
			{
				terminal_put(randomX, randomY, SPEED_CHAR);
				showPow = -1;
			}
            // move the player
    	    movePlayer(keyEntered, player, gameBoard);
    	    //moves the monster to chase the player
    	    if(keyEntered==TK_UP||keyEntered==TK_DOWN||keyEntered==TK_LEFT||
    	    keyEntered==TK_RIGHT)
			{
				if(keyStroke==true)
				{
    	    		chasingPerson(player, monster, gameBoard);	
    	    	}
    	    
    	    	if(player.get_x()==speedPowerUp.get_x()&&player.get_y()==speedPowerUp.get_y())
    	    	{
    	    		playerHitSpeedPow(player, speedPowerUp, turnCount, powSpeedCounter);
    	    	}
    	    	
				if(turnCount>0)
				{
					turnCount--;
					if(turnCount==0&&powSpeedCounter<5)
					{
						speedPowerUp.set_active(true);
						player.changeSpeed(SPEED1);
						randomLocation(randomX, randomY, gameBoard);
						speedPowerUp.new_location(randomX, randomY);
						turnCount = -1;
					}
					else if(powSpeedCounter==5)
					{
						player.changeSpeed(SPEED1);
						wallSet(WALL4Y, WALL4X, WALL2_LENGTH, WALLTHICK, gameBoard, DELETE_WALL);
						powSpeedCounter++;
					}
				}	
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
