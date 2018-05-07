/* Grid class:

- Grid Environment Object.
- Contains graphical and symbolic components for the Environment.
- Contains the agent and its interactions.

PUBLIC MEMBERS:

- Grid(sf::RenderWindow *input_window, sf::Vector2f input_tile_size, sf::Color input_tile_color)
- Grid(sf::RenderWindow *input_window, sf::Vector2f input_tile_size)
- Grid(sf::RenderWindow *input_window, float input_tile_length)
Constructors for the Grid class. Accepts the rendering window, tile size and tile color as arguments.

- void draw()
Graphics function. References the rendering window to draw graphical components.

- void update()
Main function. Contains the agent and its interactions, makes changes to symbolic and graphical components.

- void init():
Initialization function. Generates and initializes all symbolic and graphical components.

PRIVATE MEMBERS:

- Agent agent
Agent object.

- sf::RectangleShape tiles[GRID_WIDTH][GRID_HEIGHT]
Graphical matrix variable for the tile background. This is simply a backdrop for the Environment (no direct interaction).

- sf::Sprite dirt[GRID_WIDTH][GRID_HEIGHT]
Graphical matrix variable for agent, dirt and clean tile representations.

- int dirtmap[GRID_WIDTH][GRID_HEIGHT]
Symbolic matrix variable for agent, dirt and clean tile representations.

- sf::RenderWindow *screen
Pointer variable that references the rendering window, enabling it to draw graphics.

- sf::Vector2f tile_size
Graphics vector variable that defines the dimensions of each tile.

- sf::Color tile_color
- sf::Texture dirt_texture
- sf::Texture agent_texture
- sf::Texture clean_texture
- sf::Font font
- sf::Text text
Graphic object variables that provide textures and colors for visualization.

End of Contents   */

#include <SFML/Graphics.hpp>
#include "agent.h"
#include "filewriter.h"

#ifndef GRID_H
#define GRID_H

#define GRID_HEIGHT 8
#define GRID_WIDTH 8

using namespace std;

class Grid
{
	public:
		//Constructors
		Grid(sf::RenderWindow *input_window, sf::Vector2f input_tile_size, sf::Color input_tile_color);
		Grid(sf::RenderWindow *input_window, sf::Vector2f input_tile_size);
		Grid(sf::RenderWindow *input_window, float input_tile_length);
		//Public Functions
		void draw();
		void update();
		void init();
		void writestats();
	private:
		//Agent Object
		Agent agent;
		//Member Matrix Variables
		sf::RectangleShape tiles[GRID_WIDTH][GRID_HEIGHT];
		sf::Sprite dirt[GRID_WIDTH][GRID_HEIGHT];
		int dirtmap[GRID_WIDTH][GRID_HEIGHT];
		//Member Graphical Variables
		sf::RenderWindow *screen;
		sf::Vector2f tile_size;
		sf::Color tile_color;
		sf::Texture dirt_texture;
		sf::Texture agent_texture;
		sf::Texture clean_texture;
		sf::Font font;
		sf::Text text;
		//Output File
		FileWriter filewriter;
		
};

#endif
