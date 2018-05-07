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
#include "grid.h"
#include <ctime>
#include <string>

#define CLEAN 0
#define DIRTY 1
#define AGENT 2
#define DONE 3

using namespace std;

/*   Constructors   */
Grid::Grid(sf::RenderWindow *input_window, sf::Vector2f input_tile_size, sf::Color input_tile_color)
{
	screen = input_window;
	tile_size = input_tile_size;
	tile_color = input_tile_color;
	
	init();
}

Grid::Grid(sf::RenderWindow *input_window, sf::Vector2f input_tile_size)
{
	screen = input_window;
	tile_size = input_tile_size;
	tile_color = sf::Color::White;
	
	init();
}

Grid::Grid(sf::RenderWindow *input_window, float input_tile_length)
{
	screen = input_window;
	tile_size.x = input_tile_length;
	tile_size.y = input_tile_length;
	tile_color = sf::Color::White;
	
	init();
}
/*   End Constructors   */

/*   Graphics Function   */
void Grid::draw()
{
	for(int pos_x = 0; pos_x < GRID_WIDTH; pos_x++)
	{
		for(int pos_y = 0; pos_y < GRID_HEIGHT; pos_y++)
		{
			screen->draw(tiles[pos_x][pos_y]);
			screen->draw(dirt[pos_x][pos_y]);
			screen->draw(text);
		}
	}
}

/*   Initialization   */
void Grid::init()
{
	//Buffer Variables
	sf::Vector2f position;
	bool dirty;
	int agent_tile;

	//Load Textures
	if (!dirt_texture.loadFromFile("dirt_texture.png") 
	|| !agent_texture.loadFromFile("agent_texture.png")
	|| !clean_texture.loadFromFile("clean_texture.png")
	|| !font.loadFromFile("TNR.ttf"))
	{
		exit(EXIT_FAILURE);
	}
	
	//Generate Random Agent Position
	srand(time(NULL));
	agent_tile = rand()%64;
	
	for(int pos_x = 0; pos_x < GRID_WIDTH; pos_x++)
	{
		for(int pos_y = 0; pos_y < GRID_HEIGHT; pos_y++)
		{
			//Initialize Position Buffer
			position.x = (pos_x * tile_size.x * 1.1);
			position.y = (pos_y * tile_size.y * 1.1);
			
			//Initialize Tile
			tiles[pos_x][pos_y].setSize(tile_size);
			tiles[pos_x][pos_y].setFillColor(tile_color);
			tiles[pos_x][pos_y].setPosition(position);
			
			//Generate Random True/False
			dirty = rand()%2;
			
			if(agent_tile == 0) //Initialize Agent
			{
				dirt[pos_x][pos_y].setTexture(agent_texture);
				dirt[pos_x][pos_y].setPosition(position);
				dirtmap[pos_x][pos_y] = AGENT;
			}
			else if(dirty) //Initialize Dirty Tile
			{
				dirt[pos_x][pos_y].setTexture(dirt_texture);
				dirt[pos_x][pos_y].setPosition(position);
				dirtmap[pos_x][pos_y] = DIRTY;
			}
			else //Initialize Clean Tile
			{
				dirtmap[pos_x][pos_y] = CLEAN;
			}
			
			//Countdown to Random Agent Position
			agent_tile--;
		}
	}
	
	//Initialize Agent
	agent.init(dirtmap);
	
	//Initialize Text
	text.setFont(font);
	text.setCharacterSize(40);
	text.setColor(sf::Color::Red);
	text.setPosition(440 - 80, 20);
}

/*   Main Function   */
void Grid::update()
{
	sf::Vector2f position;

	agent.sense(dirtmap);
	agent.actuate(dirtmap);

	/*   Update the graphical matrix   */
	for(int pos_x = 0; pos_x < GRID_WIDTH; pos_x++)
	{
		for(int pos_y = 0; pos_y < GRID_HEIGHT; pos_y++)
		{
			position = tiles[pos_x][pos_y].getPosition();
		
			switch(dirtmap[pos_x][pos_y])
			{
				case DIRTY:
					dirt[pos_x][pos_y].setTexture(dirt_texture);
					dirt[pos_x][pos_y].setPosition(position);
				break;
				case AGENT:
					dirt[pos_x][pos_y].setTexture(agent_texture);
					dirt[pos_x][pos_y].setPosition(position);
				break;
				case DONE:
					dirt[pos_x][pos_y].setTexture(clean_texture);
					dirt[pos_x][pos_y].setPosition(position);
				break;
			}
		}
	}
	
	text.setString(to_string((int)agent.get_trace()));
}

void Grid::writestats()
{
	string output = text.getString() + ",\n";
	filewriter.write_to("stats.csv", output);
}
