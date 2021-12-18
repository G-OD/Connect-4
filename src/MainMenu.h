#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>

#include "Graphics.h"
#include "Button.h"

class Game;
class Button;

class MainMenu
{
	private:
		static Game *game;
		static const int MAIN_MENU_BUTTON_WIDTH = 250;
		static const int MAIN_MENU_BUTTON_HEIGHT = 50;
		static float MAIN_MENU_BUTTON_OFFSET;
		static std::vector<Button> buttons;

	public:
		MainMenu() {}
		MainMenu(Game *game, float offset);

		static void start();

		static void render();
		
		static void mouseClick(int button, int state, int xPos, int yPos);
};

#endif