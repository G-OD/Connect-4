#include <iostream>

#include "Game.h"

/*
	Main function
*/
int main(int argc, char *argv[])
{
	Game *game = new Game();
	
	game->Init(argc, argv);

	return 0;
}