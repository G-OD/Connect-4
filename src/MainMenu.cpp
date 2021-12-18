#include "Game.h"
#include "MainMenu.h"

Game *MainMenu::game; // Pointer to main class
float MainMenu::MAIN_MENU_BUTTON_OFFSET; // Spacing offset
std::vector<Button> MainMenu::buttons;

MainMenu::MainMenu(Game *g, float o)
{
	game = g;
	MAIN_MENU_BUTTON_OFFSET = o;

	buttons.clear(); // Make sure the buttons array is empty by clearing

	const char *titles[] = { "Start Game", "Statistics", "Options", "Exit Game" }; // Menu button options
	float offset = 0; // Offset amount to move object down

	// Create the buttons and append them to and array
	for (int i = 0; i < (int)(sizeof(titles) / sizeof(titles[0])); ++i)
	{
		offset += MAIN_MENU_BUTTON_OFFSET; // Add to the offset to move the buttons down by an even amount
		buttons.push_back(Button(0.0f, Game::WINDOW_HEIGHT - offset, MAIN_MENU_BUTTON_WIDTH, MAIN_MENU_BUTTON_HEIGHT, titles[i], 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.0f)); // Create and append the button to the main array
	}
}

// Change the render and mouse functions to the main menu handlers
void MainMenu::start()
{
	glutKeyboardFunc(NULL); // Set keyboard function to NULL since it's not needed
	glutPassiveMotionFunc(NULL); // No need to monitor mouse movement on every movement
	glutDisplayFunc(render); // Set render function to one in class
	glutMouseFunc(mouseClick); // Set up mouse handler for main menu
}

// Render the buttons onto the screen
void MainMenu::render()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the screen of all colour to the value of glClearColor (which I set to black)
	
	// Iterate through every button
	for (auto& it: buttons)
		it.render();

	glutSwapBuffers(); // Update screen
}

// Mouse button handler
void MainMenu::mouseClick(int button, int state, int xPos, int yPos)
{
	// On mouse down
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// Start game
		if (buttons[0].click(xPos, yPos))
			game->gotoGame();
		// Options
		else if (buttons[2].click(xPos, yPos))
			game->gotoOptions();
		// Exit game
		else if (buttons[3].click(xPos, yPos))
			game->Exit();
	}
}