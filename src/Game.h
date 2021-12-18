#ifndef GAME_H
#define GAME_H


#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <chrono>

#include "AI.h"
#include "Board.h"
#include "Graphics.h"
#include "Controls.h"
#include "MainMenu.h"
#include "Options.h"

#define FPS 30 // Framerate to check 

typedef std::chrono::high_resolution_clock Clock;

class Graphics;
class Controls;
class Board;
class MainMenu;
class Options;
class AI;

struct DefaultSettings
{
	const int opponent = 1;
	const int aiDifficulty = 0;
	const int matchTimeAllowed = 10;
	const int turnTimeAllowed = 10;
	const int rowToWin = 4;
	const int gameBoardWidth = 7;
	const int gameBoardHeight = 6;
};
struct Settings
{
	int opponent;
	int aiDifficulty;
	int matchTimeAllowed;
	int turnTimeAllowed;
	int rowToWin;
	int gameBoardWidth;
	int gameBoardHeight;
};

class Game
{
	private:
		static int currentWindowWidth;
		static int currentWindowHeight;
		GLfloat windowAspect;
		Graphics *graphics;
		Controls *controls;

		static Board *board;
		AI *ai;
		bool aiOn = false;
		static bool gameRunning;
		static std::chrono::time_point<std::chrono::high_resolution_clock> clock;
		static double matchTimeAllowed;
		static double turnTimeAllowed;
		static std::chrono::time_point<std::chrono::high_resolution_clock> lastTurnTime;

		float mouseCounterXPos = 0.0f;
		int playerTurn = 1;

	public:
		static DefaultSettings defaultSettings;
		Settings settings;
		// Constants
		static const int WINDOW_WIDTH = 500;
		static const int WINDOW_HEIGHT = 500;

		const float COUNTER_SPACE_RADIUS = 50.0f; // Counter and space radius
		const float GAME_BOARD_BORDER_SPACE = 50.0f; // Amount of space to leave as a border
		const float GAME_BOARD_X = -(float)(WINDOW_WIDTH - GAME_BOARD_BORDER_SPACE); // Starting point for the game board X position
		const float GAME_BOARD_Y = WINDOW_HEIGHT - GAME_BOARD_BORDER_SPACE; // Starting point for the game board Y position
		float GAME_BOARD_X_OFFSET; // Variable to hold the equal space offset for alignment
		float GAME_BOARD_Y_OFFSET;

		Game();

		~Game();

		void Init(int argc, char **argv);
		void Exit();

		static void setWindowWidth();
		static void setWindowHeight();
		static int getWindowWidth();
		static int getWindowHeight();

		void resetSettings();
		void loadSettings();
		void saveSettings();
		Settings getSettings();

		void gotoMainMenu();
		void gotoGame();
		void gotoOptions();

		void setTurnTime();

		static void timer(int state);
		void reset();

		void saveGame();
		void loadGame();

		int getPlayerTurn();
		void setPlayerTurn(int player);
		void changePlayerTurn();

		GLfloat getWindowAspectRatio();
		void setWindowAspectRatio(GLfloat aspect);

		int getMouseCounterXPos();
		void setMouseCounterXPos(float xPos);

		bool getAISetting();
		void toggleAISetting();

		void aiPlayMove();
};

#endif