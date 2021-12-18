#include "Game.h"
#include "Options.h"

Game *Options::game;
float Options::MAIN_MENU_BUTTON_OFFSET;
std::vector<Button> Options::buttons;
std::vector<RadioButton> Options::radioButtons;
std::vector<NumberSelector> Options::numberSelectors;

Options::Options(Game *g)
{
	game = g;

	buttons.clear();
	radioButtons.clear();
	numberSelectors.clear();

	buttons.push_back(Button(-250.0f, -300.0f, BUTTON_WIDTH, BUTTON_HEIGHT, "Reset Progress", 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f));
	buttons.push_back(Button(250.0f, -300.0f, BUTTON_WIDTH, BUTTON_HEIGHT, "Default Settings", 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f));
	buttons.push_back(Button(-300.0f, -425.0f, QUIT_BUTTON_WIDTH, BUTTON_HEIGHT, "Save", 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f));
	buttons.push_back(Button(0.0f, -425.0f, QUIT_BUTTON_WIDTH, BUTTON_HEIGHT, "Quit", 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f));
	buttons.push_back(Button(300.0f, -425.0f, QUIT_BUTTON_WIDTH, BUTTON_HEIGHT, "Save & Quit", 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f));

	std::vector<const char *> strings;

	strings.push_back("AI");
	strings.push_back("Local Player");
	radioButtons.push_back(RadioButton(-400.0f, 400.0f, 20.0f, 8.0f, strings, game->settings.opponent, 0.0f, 0.0f, 0.0f));

	strings.clear();
	
	strings.push_back("Easy");
	strings.push_back("Medium");
	strings.push_back("Hard");
	strings.push_back("Impossible");
	radioButtons.push_back(RadioButton(-400.0f, 300.0f, 20.0f, 8.0f, strings, game->settings.aiDifficulty, 0.0f, 0.0f, 0.0f));

	numberSelectors.push_back(NumberSelector(0.0f, 210.0f, 100.0f, 30.0f, 10.0f, game->settings.matchTimeAllowed , 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f));
	numberSelectors.push_back(NumberSelector(0.0f, 110.0f, 100.0f, 30.0f, 10.0f, game->settings.turnTimeAllowed, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f));
	numberSelectors.push_back(NumberSelector(0.0f, 10.0f, 100.0f, 30.0f, 10.0f, game->settings.rowToWin, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f));
	numberSelectors.push_back(NumberSelector(0.0f, -90.0f, 100.0f, 30.0f, 10.0f, game->settings.gameBoardWidth, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f));
	numberSelectors.push_back(NumberSelector(0.0f, -190.0f, 100.0f, 30.0f, 10.0f, game->settings.gameBoardHeight, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f));
}

void Options::start()
{
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(NULL);
	glutMotionFunc(NULL);
	glutDisplayFunc(render);
	glutMouseFunc(mouseClick);
}

void Options::render()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen of all colour to the value of glClearColor (which I set to black)
	
	Graphics::drawText(-400.0f, 450.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Settings", true, 0.0f, 0.0f, 0.0f);
	Graphics::drawText(0.0f, 450.0f, GLUT_BITMAP_8_BY_13, "Opponent", true, 0.0f, 0.0f, 0.0f);
	Graphics::drawText(0.0f, 350.0f, GLUT_BITMAP_8_BY_13, "AI Difficulty", true, 0.0f, 0.0f, 0.0f);
	Graphics::drawText(0.0f, 250.0f, GLUT_BITMAP_8_BY_13, "Match Time Limit (minutes)", true, 0.0f, 0.0f, 0.0f);
	Graphics::drawText(0.0f, 150.0f, GLUT_BITMAP_8_BY_13, "Turn Time Limit (seconds)", true, 0.0f, 0.0f, 0.0f);
	Graphics::drawText(0.0f, 50.0f, GLUT_BITMAP_8_BY_13, "Row Count To Win", true, 0.0f, 0.0f, 0.0f);
	Graphics::drawText(0.0f, -50.0f, GLUT_BITMAP_8_BY_13, "Game Board Width", true, 0.0f, 0.0f, 0.0f);
	Graphics::drawText(0.0f, -150.0f, GLUT_BITMAP_8_BY_13, "Game Board Height", true, 0.0f, 0.0f, 0.0f);

	for (auto &it: buttons)
		it.render();

	for (auto &it: radioButtons)
		it.render();

	for (auto &it: numberSelectors)
		it.render();

	glutSwapBuffers(); // Update screen
}

// Keyboard controls
void Options::keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		// Quit game
		case 'q':
			game->gotoMainMenu();
			break;
	}
}

void Options::mouseClick(int button, int state, int xPos, int yPos)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (buttons[1].click(xPos, yPos))
		{
			#ifdef _WIN32
			const int choice = MessageBox(NULL, "Are you sure you want to reset to default settings?", "Reset?", MB_YESNO);

			switch(choice)
			{
				case IDYES:
					game->resetSettings();

					radioButtons[0].setValue(game->defaultSettings.opponent);
					radioButtons[1].setValue(game->defaultSettings.aiDifficulty);
					numberSelectors[0].setValue(game->defaultSettings.matchTimeAllowed);
					numberSelectors[1].setValue(game->defaultSettings.turnTimeAllowed);
					numberSelectors[2].setValue(game->defaultSettings.rowToWin);
					numberSelectors[3].setValue(game->defaultSettings.gameBoardWidth);
					numberSelectors[4].setValue(game->defaultSettings.gameBoardHeight);
					break;
			}
			#else
			game->resetSettings();

			radioButtons[0].setValue(game->defaultSettings.opponent);
			radioButtons[1].setValue(game->defaultSettings.aiDifficulty);
			numberSelectors[0].setValue(game->defaultSettings.matchTimeAllowed);
			numberSelectors[1].setValue(game->defaultSettings.turnTimeAllowed);
			numberSelectors[2].setValue(game->defaultSettings.rowToWin);
			numberSelectors[3].setValue(game->defaultSettings.gameBoardWidth);
			numberSelectors[4].setValue(game->defaultSettings.gameBoardHeight);
			#endif
		}
		else if (buttons[2].click(xPos, yPos) || buttons[4].click(xPos, yPos))
		{
			#ifdef _WIN32
			const int choice = MessageBox(NULL, "Are you sure you want to save your settings?", "Save?", MB_YESNO);

			switch(choice)
			{
				case IDYES:
					game->settings.opponent = radioButtons[0].getValue();
					game->settings.aiDifficulty = radioButtons[1].getValue();
					game->settings.matchTimeAllowed = numberSelectors[0].getValue();
					game->settings.turnTimeAllowed = numberSelectors[1].getValue();
					game->settings.rowToWin = numberSelectors[2].getValue();
					game->settings.gameBoardWidth = numberSelectors[3].getValue();
					game->settings.gameBoardHeight = numberSelectors[4].getValue();
					
					game->saveSettings();

					if (buttons[4].click(xPos, yPos))
						game->gotoMainMenu();
					break;
			}
			#else

			game->settings.opponent = radioButtons[0].getValue();
					game->settings.aiDifficulty = radioButtons[1].getValue();
					game->settings.matchTimeAllowed = numberSelectors[0].getValue();
					game->settings.turnTimeAllowed = numberSelectors[1].getValue();
					game->settings.rowToWin = numberSelectors[2].getValue();
					game->settings.gameBoardWidth = numberSelectors[3].getValue();
					game->settings.gameBoardHeight = numberSelectors[4].getValue();

			game->saveSettings();

			if (buttons[4].click(xPos, yPos))
				game->gotoMainMenu();
			
			#endif
		}
		else if (buttons[3].click(xPos, yPos))
		{
			#ifdef _WIN32
			const int choice = MessageBox(NULL, "Are you sure you want to quit without saving your settings?", "Quit?", MB_YESNO);

			switch(choice)
			{
				case IDYES:
					game->gotoMainMenu();
					break;
			}

			#else
			game->gotoMainMenu();
			#endif
		}

		for (auto &it: radioButtons)
			it.click(xPos, yPos);

		for (auto &it: numberSelectors)
			it.click(xPos, yPos);

		glutPostRedisplay();
	}
}