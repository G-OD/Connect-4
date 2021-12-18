#ifndef OPTIONS_H
#define OPTIONS_H

#include "Graphics.h"
#include "Button.h"
#include "RadioButton.h"
#include "NumberSelector.h"

class Game;
class Button;
class RadioButton;
class NumberSelector;

class Options
{
	private:
		static Game *game;
		static const int QUIT_BUTTON_WIDTH = 100;
		static const int BUTTON_WIDTH = 200;
		static const int BUTTON_HEIGHT = 50;

		static float MAIN_MENU_BUTTON_OFFSET;
		static std::vector<Button> buttons;
		static std::vector<RadioButton> radioButtons;
		static std::vector<NumberSelector> numberSelectors;

	public:
		Options() {}
		Options(Game *game);

		static void start();

		static void render();
		
		static void keyboard(unsigned char key, int x, int y);

		static void mouseClick(int button, int state, int xPos, int yPos);
};

#endif