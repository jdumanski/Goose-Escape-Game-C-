//THIS IS THE START OF THE gooseEscapeActors.hpp FILE
#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"



/*
    Modify this class to contain more characteristics of the "actor".  Add
    functions that will be useful for playing the game that are specific to
    the Actor.
    
    Feel free to add additional Classes to your program.
*/

/* 
    Going further:  Learn the other syntax for implementing a class that is
    more appropriate for working with multiple files, and improve the class code.
*/

class Actor
{
  private:
    int actorChar;      
    int location_x, location_y;
    int speed;
    bool active;

  public:
    Actor()
    {
        actorChar = int('A');
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        speed = SPEED1;
        put_actor();
        active = true;
    }

    Actor(char initPlayerChar, int x0, int y0, int speed)
    {
        change_char(initPlayerChar);
        location_x = MIN_SCREEN_X;
        location_y = MIN_SCREEN_Y;
        changeSpeed(speed);
        active = true;
        update_location(x0,y0);
    }

    bool get_active() const
    {
    	return active;
	}

	void set_active(bool cond)
	{
		active = cond;
	}
	
	int get_char() const
	{
		return actorChar;
	}
	
    void changeSpeed(int newSpeed)
    {
    	if(newSpeed==SPEED1||newSpeed==SPEED2)
    	{
    		speed = newSpeed;
		}
	}
	
	int get_speed() const
	{
		return speed;
	}
	
    int get_x() const
    {
        return location_x;
    }
    
    int get_y() const
    {
        return location_y;
    }
    
    int set_x(int newLocationX)
    {
    	if(newLocationX<=NUM_BOARD_X)
    	{
    		location_x = newLocationX;
    	}
	}
	
	int set_y(int newLocationY)
	{
		if(newLocationY<=NUM_BOARD_Y)
    	{
    		location_y = newLocationY;
    	}
	}
    
    
    string get_location_string() const
    {
        char buffer[80];
        itoa(location_x,buffer,10);
        string formatted_location = "(" + string(buffer) + ",";
        itoa(location_y,buffer,10);
        formatted_location += string(buffer) + ")";
        return formatted_location;
    }
    
    void change_char(char new_actor_char)
    {
        actorChar = min(int('~'),max(int(new_actor_char),int(' ')));
    }

    bool can_move(int delta_x, int delta_y) const
    {
        int new_x = location_x + delta_x;
        int new_y = location_y + delta_y;

        return new_x >= MIN_BOARD_X && new_x <= MAX_BOARD_X
          && new_y >= MIN_BOARD_Y && new_y <= MAX_BOARD_Y;
    }

    void update_location(int delta_x, int delta_y)
    {
        if (can_move(delta_x, delta_y))
        {
            terminal_clear_area(location_x, location_y, 1, 1);
            location_x += delta_x;
            location_y += delta_y;
            put_actor();
        }
    }
    
    void new_location(int newX, int newY)
    {
    	location_x = newX;
		location_y = newY;
		put_actor();
	}
    
    void put_actor() const
    {
        terminal_put(location_x, location_y, actorChar);
        terminal_refresh();
    }
    
};
#endif

//THIS IS THE END OF THE gooseEscapeActors.hpp FILE
