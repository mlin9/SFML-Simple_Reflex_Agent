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

#include <SFML/Graphics.hpp>

#ifndef AGENT_H
#define AGENT_H

#define CLEAN 0
#define DIRTY 1
#define AGENT 2
#define DONE 3

#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3

#define GRID_WIDTH 8
#define GRID_HEIGHT 8

class Agent
{
	public:
		Agent();
		void init(int dirtmap[GRID_WIDTH][GRID_HEIGHT]);
		bool sense(int dirtmap[GRID_WIDTH][GRID_HEIGHT]);
		bool actuate(int (&dirtmap)[GRID_WIDTH][GRID_HEIGHT]);
		int get_trace();
	private:
		int direction;
		int trace;
		sf::Vector2i position;
		sf::Vector2i target;
		bool dirt_found;
};

#endif
