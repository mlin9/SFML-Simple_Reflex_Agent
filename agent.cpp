/* Agent class:

- Agent Object
- Contains sensor and actuator functions.
- Uses symbolic components of the Grid Environment Object.

PUBLIC MEMBERS:

- Agent()
Constructor for the Agent class.

- void init(int dirtmap[GRID_WIDTH][GRID_HEIGHT])
Initialization function. Retrieves the starting position of the Agent.

- bool sense(int dirtmap[GRID_WIDTH][GRID_HEIGHT])
Sensor function. Detects dirt, changes directions and selects the closest dirt tile.

- bool actuate(int (&dirtmap)[GRID_WIDTH][GRID_HEIGHT])
Actuator function. Navigates the Agent through the symbolic dirt matrix.

- int get_trace()
Value function. Returns the score of the agent.

PRIVATE MEMBERS:

- int direction
Code variable to track direction of the Agent.

- int trace
Integer variable to track Agent score.

- sf::Vector2i position
Vector variable to track Agent position.

- sf::Vector2i target
Vector variable to track closest dirt tile.

- bool dirt_found
Boolean variable to track Agent state.

End of Contents   */

#include "agent.h"

using namespace std;

Agent::Agent()
{
	direction = NORTH;
	trace = 0;
}

void Agent::init(int dirtmap[GRID_WIDTH][GRID_HEIGHT])
{
	//Finds Position
	for(int pos_x = 0; pos_x < GRID_WIDTH; pos_x++)
	{
		for(int pos_y = 0; pos_y < GRID_HEIGHT; pos_y++)
		{
			if(dirtmap[pos_x][pos_y] == AGENT)
			{
				position.x = pos_x;
				position.y = pos_y;
			}
		}
	}
}

bool Agent::sense(int dirtmap[GRID_WIDTH][GRID_HEIGHT])
{
	//Track minimum distance
	int minimum = 99;
	
	//Look East for Dirt
	for(int index = position.x; index < GRID_WIDTH-1; index++)
	{
		if(dirtmap[index][position.y] == DIRTY)
		{
			dirt_found = true;
			target.x = index;
			target.y = position.y;
			minimum = index - position.x;
			direction = EAST;
			break;
		}
	}
		
	//Look South for Dirt
	for(int index = position.y; index < GRID_HEIGHT-1; index++)
	{
		if(dirtmap[position.x][index] == DIRTY)
		{
			dirt_found = true;
			target.x = position.x;
			target.y = index;
			if(minimum > index - position.y)
			{
				minimum = index - position.y;
				direction = SOUTH;
			}
			break;
		}
	}
		
	//Look West for Dirt
	for(int index = position.x; index >= 0; index--)
	{
		if(dirtmap[index][position.y] == DIRTY)
		{
			dirt_found = true;
			target.x = index;
			target.y = position.y;
			if(minimum > position.x - index)
			{
				minimum = position.x - index;
				direction = WEST;
			}
			break;
		}
	}
		
	//Look North for Dirt
	for(int index = position.y; index >= 0; index--)
	{
		if(dirtmap[position.x][index] == DIRTY)
		{
			dirt_found = true;
			target.x = position.x;
			target.y = index;
			if(minimum > position.y - index)
			{
				direction = NORTH;
			}
			break;
		}
	}
	
	return dirt_found;
}
bool Agent::actuate(int (&dirtmap)[GRID_WIDTH][GRID_HEIGHT])
{
	if(dirt_found)
	{
		//Tile underneath is Done
		dirtmap[position.x][position.y] = DONE;
		
		//Just make a single step
		switch(direction)
		{
			case EAST:
				if(position.x < GRID_WIDTH-1)
				{
					position.x++;
				}
				else
				{
					dirt_found = false;
				}
			break;
			case SOUTH:
				if(position.y < GRID_HEIGHT-1)
				{
					position.y++;
				}
				else
				{
					dirt_found = false;
				}
			break;
			case WEST:
				if(position.x > 0)
				{
					position.x--;
				}
				else
				{
					dirt_found = false;
				}
			break;
			case NORTH:
				if(position.y > 0)
				{
					position.y--;
				}
				else
				{
					dirt_found = false;
				}
			break;
		}
		
		//Update dirtmap and score
		dirtmap[position.x][position.y] = AGENT;
		trace++;
		
		//Reset Agent Direction & Sensors if Dirty
		if(dirtmap[position.x][position.y] == DIRTY)
		{
			dirt_found = false;
		}
	}
	else
	{
		//Move in a clockwise fashion if dirt cannot be detected
		dirtmap[position.x][position.y] = DONE;
		
		switch(direction)
		{
			case EAST:
				if(position.x < GRID_WIDTH-1)
				{
					position.x++;
				}
				else
				{
					direction = SOUTH;
					dirt_found = false;
				}
			break;
			case SOUTH:
				if(position.y < GRID_HEIGHT-1)
				{
					position.y++;
				}
				else
				{
					direction = WEST;
					dirt_found = false;
				}
			break;
			case WEST:
				if(position.x > 0)
				{
					position.x--;
				}
				else
				{
					direction = NORTH;
					dirt_found = false;
				}
			break;
			case NORTH:
				if(position.y > 0)
				{
					position.y--;
				}
				else
				{
					direction = EAST;
					dirt_found = false;
				}
			break;
		}
		
		dirtmap[position.x][position.y] = AGENT;
	}

	return dirt_found;
}

//Get score
int Agent::get_trace()
{
	return trace;
}
