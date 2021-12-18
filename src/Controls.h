#ifndef CONTROLS_H
#define CONTROLS_H

#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include "Game.h"
#include "Board.h"

class Game;
class Board;

class Controls
{
	private:
		static Game *game;
		static Board *board;

	public:
		Controls() {}
		~Controls() {}

		static void setGame(Game *g);
		static void setBoard(Board *b);

		void aiPlayMove();

		// Place counter into column and change player turn
		static void playColumn(int x);

		// Keyboard controls
		static void keyboard(unsigned char key, int x, int y);

		// Move counter at the top with the mouse
		static void mouseMove(int xPos, int yPos);

		// Mouse click controls
		static void mouseClick(int button, int state, int xPos, int yPos);
};

#endif