#include "Controls.h"

Game *Controls::game = NULL;
Board *Controls::board = NULL;

void Controls::setGame(Game *g)
{
	game = g;
}

void Controls::setBoard(Board *b)
{
	board = b;
}

// Place counter into column and change player turn
void Controls::playColumn(int x)
{
	if (board->playColumn(x, game->getPlayerTurn()))
	{
		board->print();

		if (board->checkWin(game->getPlayerTurn(), true))
		{
			board->disallowPlay(); // Check to see if player has won
			glutPostRedisplay(); // Rerender the scene
			return;
		}

		game->changePlayerTurn();
		game->setTurnTime();

		if (game->getAISetting())
			game->aiPlayMove();

		glutPostRedisplay(); // Rerender the scene
	}
}

// Keyboard controls
void Controls::keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		// Quit game
		case 'q':
			game->gotoMainMenu();
			break;
		// Reset game
		case 'r':
			game->reset();
			break;
		// Save game
		case 's':
			game->saveGame();
			break;
		// Load game
		case 'l':
			game->loadGame();
			break;
		// Play columns with the keyboard 1-7
		case '1':
			playColumn(key - '0' - 1); // Convert unsigned character to integer by subtracting the ASCII value of
									   // 0 (48) from the character and then takes away 1 for the playColumn column
									   // index. Example. User presses 4 (ASCII value of 52) 52 - 48 = 4.
			break;
		case '2':
			playColumn(key - '0' - 1);
			break;
		case '3':
			playColumn(key - '0' - 1);
			break;
		case '4':
			playColumn(key - '0' - 1);
			break;
		case '5':
			playColumn(key - '0' - 1);
			break;
		case '6':
			playColumn(key - '0' - 1);
			break;
		case '7':
			playColumn(key - '0' - 1);
			break;
	}
}

// Move counter at the top with the mouse
void Controls::mouseMove(int xPos, int yPos)
{	
	game->setMouseCounterXPos((game->WINDOW_WIDTH * game->getWindowAspectRatio() * 2) * ((float)xPos / game->getWindowWidth()) - game->WINDOW_WIDTH * game->getWindowAspectRatio()); // Use linear interpolation
																				// to find the coordinates in relative to the mouse position
	glutPostRedisplay(); // Rerender scene
}

// Mouse click controls
void Controls::mouseClick(int button, int state, int xPos, int yPos)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float mousePos = (game->WINDOW_WIDTH * game->getWindowAspectRatio() * 2) * ((float)xPos / game->getWindowWidth()) - game->WINDOW_WIDTH * game->getWindowAspectRatio();
		
		int pos = 0;
		float spaceOffsetX = 0;
		for (int i = 0; i < board->getWidth(); ++i)
		{
			spaceOffsetX += game->GAME_BOARD_X_OFFSET;
			if (mousePos <= game->GAME_BOARD_X + spaceOffsetX + game->GAME_BOARD_BORDER_SPACE)
				break;
			++pos;
		}
		
		playColumn(pos);
	}
} 