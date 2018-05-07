#include "environment.h"

int main() {
	sf::RenderWindow window( sf::VideoMode( 440, 440 ), "Space to move, Backspace to reset.");
	Environment environment(&window);
	environment.start();
	return 0;
}
