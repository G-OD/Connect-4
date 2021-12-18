#include "Graphics.h"

Game *Graphics::game = NULL;
Board *Graphics::board = NULL;
float Graphics::MAIN_MENU_BUTTON_OFFSET;

Graphics::Graphics(Game *g, Board *b)
{
	game = g;
	board = b;

	MAIN_MENU_BUTTON_OFFSET = ((float)game->WINDOW_HEIGHT * 2) / (4 + 1);
}

void Graphics::setGame(Game *g)
{
	game = g;
}

void Graphics::setBoard(Board *b)
{
	board = b;
}

GLfloat Graphics::getWindowAspectRatio()
{
	return game->getWindowAspectRatio();
}

/*
	Window redraw handling function to prevent stretching
*/
void Graphics::reshapeWindow(int width, int height)
{
	if (height == 0) height = 1; // Avoid dividing by 0
	
	if (height < game->WINDOW_HEIGHT || height > width)
		glutReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_WIDTH));
	if (width < game->WINDOW_WIDTH)
		glutReshapeWindow(game->WINDOW_WIDTH, glutGet(GLUT_WINDOW_HEIGHT));

	game->setWindowAspectRatio((GLfloat)width / (GLfloat)height); // Calculate aspect ratio of the window
	game->setWindowWidth();
	game->setWindowHeight();
	
	// Set the viewport to the width and height of the window
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Reshape content inside of window and prevent streching by multiplying the max X coordinate by the aspect ratio to expand the game space, not strech it
	glOrtho(-game->WINDOW_WIDTH * game->getWindowAspectRatio(), game->WINDOW_WIDTH * game->getWindowAspectRatio(), -game->WINDOW_HEIGHT, game->WINDOW_HEIGHT, 0.0f, 1.0f);
}

/*
	Draw line
*/
void Graphics::drawLine(float xPos1, float yPos1, float xPos2, float yPos2, float red, float green, float blue)
{
	glBegin(GL_LINES);
	glColor3f(red, green, blue);
	glVertex2f(xPos1, yPos1);
	glVertex2f(xPos2, yPos2);
	glEnd();
}

/*
	Draw circle
*/
void Graphics::drawCircle(float xPos, float yPos, float radius, float red, float green, float blue)
{
	glBegin(GL_POLYGON);
	glColor3f(red, green, blue);
	// 360 degrees in circle
	for (int i = 0; i < 360; ++i)
		glVertex2f(radius * cos(i * M_PI / 180.0f) + xPos, radius * sin(i * M_PI / 180.0f) + yPos);
	glEnd();
}

void Graphics::drawRect(float xPos, float yPos, float width, float height, float red, float green, float blue)
{
	glBegin(GL_POLYGON);
	glColor3f(red, green, blue);
	glVertex2f(xPos - width, yPos + height);
	glVertex2f(xPos + width, yPos + height);
	glVertex2f(xPos + width, yPos - height);
	glVertex2f(xPos - width, yPos - height);
	glEnd();
}

int Graphics::drawText(float x, float y, void *font, const char *string, bool center, float red, float green, float blue)
{
	glColor3f(red, green, blue);

	const unsigned char *newString = reinterpret_cast<const unsigned char*>(string);
	int len = glutBitmapLength(font, newString);

	if (center)
		glRasterPos2f(x - len, y);
	else
		glRasterPos2f(x, y);

	for (int i = 0; i < (int)strlen(string); i++)
	    glutBitmapCharacter(font, (int)string[i]);

	return len;
}

void Graphics::renderGameBoard()
{
	float red, green, blue; // Colours for counter
	
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen of all colour to the value of glClearColor (which I set to black)
	
	// Draw blue game board
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(game->GAME_BOARD_X + game->GAME_BOARD_BORDER_SPACE, game->GAME_BOARD_Y - game->GAME_BOARD_BORDER_SPACE);
	glVertex2f(-game->GAME_BOARD_X - game->GAME_BOARD_BORDER_SPACE, game->GAME_BOARD_Y - game->GAME_BOARD_BORDER_SPACE);
	glVertex2f(-game->GAME_BOARD_X - game->GAME_BOARD_BORDER_SPACE, -game->GAME_BOARD_Y + game->GAME_BOARD_BORDER_SPACE);
	glVertex2f(game->GAME_BOARD_X + game->GAME_BOARD_BORDER_SPACE, -game->GAME_BOARD_Y + game->GAME_BOARD_BORDER_SPACE);
	glEnd();
	
	// Draw game board spaces evenly
	float spaceOffsetX = 0;
	
	for (int x = 0; x < board->getWidth(); ++x)
	{
		spaceOffsetX += game->GAME_BOARD_X_OFFSET;
		float spaceOffsetY = 0;
		
		for (int y = board->getHeight() - 1; y >= 0; --y)
		{
			spaceOffsetY += game->GAME_BOARD_Y_OFFSET;
			
			// Set the colour of the space depending on state
			switch(board->getValue(x, y))
			{
				case 0:
					red = 1.0f; green = 1.0f; blue = 1.0f;
					break;
				case 1:
					red = 1.0f; green = 0.0f; blue = 0.0f;
					break;
				case 2:
					red = 1.0f; green = 0.5f; blue = 0.0f;
					break;
				case 3:
					red = 0.0f; green = 1.0f; blue = 0.0f;
					break;
			}

			// Draw space
			drawCircle(game->GAME_BOARD_X + spaceOffsetX, game->GAME_BOARD_Y - spaceOffsetY, game->COUNTER_SPACE_RADIUS, red, green, blue);
		}
	}

	// Counter at top of board which responds to mouse movement
	if (game->getPlayerTurn() == 1) { // Colour
		red = 1.0f; green = 0.0f; blue = 0.0f;
	} else {
		red = 1.0f; green = 0.5f; blue = 0.0f;
	}
	
	// Draw counter
	drawCircle(game->getMouseCounterXPos(), game->WINDOW_HEIGHT - game->GAME_BOARD_BORDER_SPACE, game->COUNTER_SPACE_RADIUS, red, green, blue);

	glutSwapBuffers(); // Update screen
}