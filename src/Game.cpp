#include "Game.h"

DefaultSettings Game::defaultSettings;
// Settings Game::settings;
int Game::currentWindowWidth = 0;
int Game::currentWindowHeight = 0;
bool Game::gameRunning = false;
Board *Game::board;
std::chrono::time_point<std::chrono::high_resolution_clock> Game::clock;
double Game::matchTimeAllowed = 300.0f;
double Game::turnTimeAllowed = 10.0f;
std::chrono::time_point<std::chrono::high_resolution_clock> Game::lastTurnTime;

Game::Game()
{
	board = new Board(7, 6, 4);

	ai = new AI();

	graphics = new Graphics(this, board);
	graphics->setGame(this);
	graphics->setBoard(board);

	controls = new Controls();
	controls->setGame(this);
	controls->setBoard(board);

	GAME_BOARD_X_OFFSET = -(GAME_BOARD_X * 2) / (board->getWidth() + 1);
	GAME_BOARD_Y_OFFSET = (GAME_BOARD_Y * 2) / (board->getHeight() + 1);
}

Game::~Game()
{
	delete board;
	delete graphics;
	delete controls;
}

void Game::Init(int argc, char **argv)
{
	glutInit(&argc, argv); // Init glut
	// glutSetOption(GLUT_MULTISAMPLE, 0); // Set antialiasing multisamples to 8
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB /*| GLUT_MULTISAMPLE*/); // Init glut display mode to double screen buffering, RGB colours and multisampling (antialiasing)
	
	// Set the window size then create it
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Connect 4");
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set the background colour to black

	glutReshapeFunc(graphics->reshapeWindow); // Window reshape function

	loadSettings();

	gotoMainMenu();
	// gotoOptions();

	glutMainLoop(); // Execute the main glut loop to start drawing
}

// void Game::initBoard()
// {
// 	delete board;
// 	board = new Board();
// }

void Game::Exit()
{
	delete this;
	exit(0);
}

void Game::setWindowWidth()
{
	currentWindowWidth = glutGet(GLUT_WINDOW_WIDTH);
}

void Game::setWindowHeight()
{
	currentWindowHeight = glutGet(GLUT_WINDOW_HEIGHT);
}

int Game::getWindowWidth()
{
	return currentWindowWidth;
}

int Game::getWindowHeight()
{
	return currentWindowHeight;
}

void Game::resetSettings()
{
	settings.opponent = defaultSettings.opponent;
	settings.aiDifficulty = defaultSettings.aiDifficulty;
	settings.matchTimeAllowed = defaultSettings.matchTimeAllowed;
	settings.turnTimeAllowed = defaultSettings.turnTimeAllowed;
	settings.rowToWin = defaultSettings.rowToWin;
	settings.gameBoardWidth = defaultSettings.gameBoardWidth;
	settings.gameBoardHeight = defaultSettings.gameBoardHeight;
}

void Game::loadSettings()
{
	FILE *fp = fopen("settings.dat", "r");

	// Check if settings file exists
	if (fp != NULL)
	{
		char buffer[15];
		for (int i = 0; i < 7; ++i)
		{
			if (fgets(buffer, 15, fp) == NULL)
			{
				fclose(fp);
				resetSettings();
				fp = fopen("settings.dat", "r");
				i = -1;
				continue;
			}

			bool notNumber = false;
			for (size_t i = 0; i < strlen(buffer) - 1; ++i)
			{
				if (std::isdigit(buffer[i]) != 1)
				{
					notNumber = true;
					break;
				}
			}

			if (notNumber)
			{
				fclose(fp);
				resetSettings();
				fp = fopen("settings.dat", "r");
				i = -1;
				continue;
			}

			int value = std::atoi(buffer);
			switch(i)
			{
				case 0:
					settings.opponent = value;
					break;
				case 1:
					settings.aiDifficulty = value;
					break;
				case 2:
					settings.matchTimeAllowed = value;
					break;
				case 3:
					settings.turnTimeAllowed = value;
					break;
				case 4:
					settings.rowToWin = value;
					break;
				case 5:
					settings.gameBoardWidth = value;
					break;
				case 6:
					settings.gameBoardHeight = value;
					break;
			}
		}

		fclose(fp);
	}
	else
	{
		resetSettings();
		saveSettings();
	}
}

void Game::saveSettings()
{
	FILE *fp = fopen("settings.dat", "w");

	fprintf(fp, "%d\n", settings.opponent);
	fprintf(fp, "%d\n", settings.aiDifficulty);
	fprintf(fp, "%d\n", settings.matchTimeAllowed);
	fprintf(fp, "%d\n", settings.turnTimeAllowed);
	fprintf(fp, "%d\n", settings.rowToWin);
	fprintf(fp, "%d\n", settings.gameBoardWidth);
	fprintf(fp, "%d\n", settings.gameBoardHeight);

	fclose(fp);
}

Settings Game::getSettings()
{
	return settings;
}

void Game::gotoMainMenu()
{
	board->reinit(settings.gameBoardWidth, settings.gameBoardHeight, settings.rowToWin);

	gameRunning = false;
	MainMenu mainMenu = MainMenu(this, Graphics::MAIN_MENU_BUTTON_OFFSET);
	mainMenu.start();
	mainMenu.render();
}

void Game::gotoGame()
{
	reset();

	GAME_BOARD_X_OFFSET = -(GAME_BOARD_X * 2) / (board->getWidth() + 1);
	GAME_BOARD_Y_OFFSET = (GAME_BOARD_Y * 2) / (board->getHeight() + 1);

	aiOn = (settings.opponent == 1) ? false : true;
	matchTimeAllowed = settings.matchTimeAllowed * 60;
	turnTimeAllowed = settings.turnTimeAllowed;

	glutDisplayFunc(graphics->renderGameBoard);
	glutKeyboardFunc(controls->keyboard); // Keyboard controls
	glutPassiveMotionFunc(controls->mouseMove); // Move counter at top with mouse function
	glutMotionFunc(controls->mouseMove);
	glutMouseFunc(controls->mouseClick); // Place counter
	glutTimerFunc(1000.0f / FPS, timer, 0);

	gameRunning = true;
}

void Game::gotoOptions()
{
	loadSettings();
	Options options = Options(this);
	options.start();
	options.render();
}

void Game::setTurnTime()
{
	lastTurnTime = Clock::now();
}

void Game::timer(int state)
{
	double matchDuration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - clock).count() / 1000.0f;
	double turnTimeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastTurnTime).count() / 1000.0f;

	if (matchDuration >= matchTimeAllowed || turnTimeDuration >= turnTimeAllowed)
	{
		board->disallowPlay();
		gameRunning = false;
	}

	std::cout << "Match Time Left: " << matchTimeAllowed - matchDuration << std::endl;
	std::cout << "Turn Time Left: " << turnTimeAllowed - turnTimeDuration << std::endl;

	if (gameRunning)
		glutTimerFunc(1000.0f / FPS, timer, 0);
}

void Game::reset()
{
	playerTurn = 1;
	board->reset();
	board->resetMovesUsed();
	board->allowPlay();

	clock = Clock::now();
	lastTurnTime = clock;

	if (!gameRunning)
	{
		glutTimerFunc(1000.0f / FPS, timer, 0);
		gameRunning = true;
	}

	glutPostRedisplay();
}

void Game::saveGame()
{
	FILE *fp = fopen("save.dat", "w");

	for (int xPos = 0; xPos < board->getWidth(); ++xPos)
	{
		for (int yPos = 0; yPos < board->getHeight(); ++yPos)
			fprintf(fp, "%d", board->getValue(xPos, yPos));
		fprintf(fp, "\n");
	}

	fclose(fp);
}

void Game::loadGame()
{
	board->reset();

	FILE *fp = fopen("save.dat", "r");

	if (fp != NULL)
	{
		char buffer[15];

		int xPos = 0;
		while (fgets(buffer, 15, fp))
		{
			for (size_t i = 0; i < strlen(buffer) - 1; ++i)
				board->setValue(xPos, i, buffer[i] - '0');
			++xPos;
		}

		fclose(fp);
		glutPostRedisplay();
	}
}

int Game::getPlayerTurn()
{
	return playerTurn;
}

void Game::setPlayerTurn(int player)
{
	playerTurn = player;
}

void Game::changePlayerTurn()
{
	playerTurn = (playerTurn == 1) ? 2 : 1; // Change player turn
}

GLfloat Game::getWindowAspectRatio()
{
	return windowAspect;
}

void Game::setWindowAspectRatio(GLfloat aspect)
{
	windowAspect = aspect;
}

int Game::getMouseCounterXPos()
{
	return mouseCounterXPos;
}

void Game::setMouseCounterXPos(float xPos)
{
	mouseCounterXPos = xPos;
}

bool Game::getAISetting()
{
	return aiOn;
}

void Game::toggleAISetting()
{
	aiOn = !aiOn;
}

void Game::aiPlayMove()
{
	std::cout << ai->alphabeta(board, playerTurn, -10000, 10000, 5) << std::endl;
	AIMove move = ai->getBestMove();

	try {
		std::cout << "Move: " << move.column << std::endl;
	} catch (const std::exception& e) {
		std::cout << "No move decided?" << std::endl;
		glutPostRedisplay();
		return;
	} 
	
	if (!board->playColumn(move.column, playerTurn))
	{
		std::cout << "He's fucking dumb" << std::endl;
		glutPostRedisplay();
		getchar();
		reset();
		return;
	}

	if (board->checkWin(playerTurn, true))
	{
		board->disallowPlay(); // Check to see if player has won
		glutPostRedisplay(); // Rerender the scene
		return;
	}
	playerTurn = (playerTurn == 1) ? 2 : 1; // Change player turn

	std::cout << "Score: " << move.score << std::endl;
}