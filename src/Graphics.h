#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <cstring>

#include "Game.h"
#include "Board.h"
#include "Graphics.h"

class Game;


struct Colour
{
	float red;
	float green;
	float blue;
};


class Graphics
{
	private:
		static Game *game;
		static Board *board;
	
	public:
		static float MAIN_MENU_BUTTON_OFFSET;

		Graphics(Game *g, Board *b);
		~Graphics() {}

		static void setGame(Game *game);
		static void setBoard(Board *board);

		static GLfloat getWindowAspectRatio();
		
		static void reshapeWindow(int width, int height);

		static void drawLine(float xPos1, float yPos1, float xPos2, float yPos2, float red, float green, float blue);
		static int drawText(float x, float y, void *font, const char *string, bool center, float red, float green, float blue);
		static void drawCircle(float xPos, float yPos, float radius, float red, float green, float blue);
		static void drawRect(float xPos, float yPos, float width, float height, float red, float green, float blue);
		
		static void renderGameBoard();
};

#endif