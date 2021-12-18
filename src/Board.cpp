#include "Board.h"

// Create board with width, height and amount in a row needed to win
Board::Board(int width, int height, int rowToWin)
{
	this->width = width;
	this->height = height;
	this->rowToWin = rowToWin;

	init();

	canPlay = true;
}

// Deconstructor. Delete pointers used by board
Board::~Board()
{
}

void Board::init()
{
	board.clear();
	for (int x = 0; x < width; ++x)
	{
		board.push_back(std::vector<int>());
		for (int y = 0; y < height; ++y)
		{
			board[x].push_back(0);
			board[x][y] = 0;
		}
	}
}

void Board::reinit(int width, int height, int rowToWin)
{
	this->width = width;
	this->height = height;
	this->rowToWin = rowToWin;
	init();
}

// Print game board to the console
void Board::print()
{
	for (int y = height - 1; y >= 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			std::cout << board[x][y];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::setRowToWin(int value)
{
	rowToWin = value;
}

// Return width
int Board::getWidth()
{
	return width;
}

// Return height
int Board::getHeight()
{
	return height;
}

// Get value at a specific location
int Board::getValue(int x, int y)
{
	return board[x][y];
}

// Set value at a specific location
void Board::setValue(int x, int y, int value)
{
	board[x][y] = value;
}

// Get number of available spaces on the game board
int Board::getSpaces()
{
	int spaces = 0;
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			if (board[x][y] == 0)
				++spaces;
		}
	}
	return spaces;
}

void Board::reset()
{
	for (int yPos = 0; yPos < height; ++yPos)
		for (int xPos = 0; xPos < width; ++xPos)
			board[xPos][yPos] = 0;
}

unsigned int Board::getMovesUsed()
{
	return moves;
}

void Board::resetMovesUsed()
{
	moves = 0;
}

// Enable users ability to play
void Board::allowPlay()
{
	canPlay = true;
}

// Disable the players ability to play (used for end of round to prevent people continuing)
void Board::disallowPlay()
{
	canPlay = false;
}

// Play in a column
bool Board::playColumn(int x, int player)
{
	if (canPlay && x >= 0 && x < width)
	{
		for (int y = 0; y < height; ++y)
		{
			if (board[x][y] == 0)
			{
				board[x][y] = player; // Add counter to column
				++moves;
				return true;
			}
		}
	}
	return false;
}

// Undo play in column
void Board::unplayColumn(int x)
{
	for (int y = height - 1; y >= 0; --y)
	{
		if (board[x][y] != 0)
		{
			board[x][y] = 0; // Remove counter from column
			--moves;
			break;
		}
	}
}

// Find the amount in a row for a specific player
int Board::inARow(int player)
{
	int bestRow = 0;

	// Horizontal check
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x <= width - rowToWin; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x + i][y] == player)
					++inARow;
				else
					break;
			}
			
			if (inARow == rowToWin)
				return inARow;
			else if (inARow > bestRow)
				bestRow = inARow;
		}
	}
	
	// Vertical check
	for (int y = 0; y <= height - rowToWin; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x][y + i] == player)
					++inARow;
				else
					break;
			}
			
			if (inARow == rowToWin)
				return inARow;
			else if (inARow > bestRow)
				bestRow = inARow;
		}
	}

	// Diagonal check (bottom left to top right)
	for (int y = 0; y <= height - rowToWin; ++y)
	{
		for (int x = 0; x <= width - rowToWin; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x + i][y + i] == player)
					++inARow;
				else
					break;
			}
			
			if (inARow == rowToWin)
				return inARow;
			else if (inARow > bestRow)
				bestRow = inARow;
		}
	}

	// Diagonal check (bottom right to top left)
	for (int y = 0; y <= height - rowToWin; ++y)
	{
		for (int x = rowToWin - 1; x < width; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x - i][y + i] == player)
					++inARow;
				else
					break;
			}
			
			if (inARow == rowToWin)
				return inARow;
			else if (inARow > bestRow)
				bestRow = inARow;
		}
	}
	
	return bestRow;
}

// Check if player has won with the ability to highlight
bool Board::checkWin(int player, bool highlight)
{
	// Horizontal check
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x <= width - rowToWin; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x + i][y] == player)
					++inARow;
				else
					break;
			}
			
			// Player has won. Colour winning move
			if (inARow == rowToWin)
			{
				if (highlight)
				{
					std::cout << player << " wins" << std::endl;
					for (int i = 0; i < rowToWin; ++i)
						board[x + i][y] = 3;
				}
				return true;
			}
		}
	}
	
	// Vertical check
	for (int y = 0; y <= height - rowToWin; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x][y + i] == player)
					++inARow;
				else
					break;
			}
			
			// Player has won. Colour winning move
			if (inARow == rowToWin)
			{
				if (highlight)
				{
					std::cout << player << " wins" << std::endl;
					for (int i = 0; i < rowToWin; ++i)
						board[x][y + i] = 3;
				}
				return true;
			}
		}
	}

	// Diagonal check (bottom left to top right)
	for (int y = 0; y <= height - rowToWin; ++y)
	{
		for (int x = 0; x <= width - rowToWin; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x + i][y + i] == player)
					++inARow;
				else
					break;
			}
			
			// Player has won. Colour winning move
			if (inARow == rowToWin)
			{
				if (highlight)
				{
					std::cout << player << " wins" << std::endl;
					for (int i = 0; i < rowToWin; ++i)
						board[x + i][y + i] = 3;
				}
				return true;
			}
		}
	}

	// Diagonal check (bottom right to top left)
	for (int y = 0; y <= height - rowToWin; ++y)
	{
		for (int x = rowToWin - 1; x < width; ++x)
		{
			// Count amount in row
			int inARow = 0;
			for (int i = 0; i < rowToWin; ++i)
			{
				if (board[x - i][y + i] == player)
					++inARow;
				else
					break;
			}
			
			// Player has won. Colour winning move
			if (inARow == rowToWin)
			{
				if (highlight)
				{
					std::cout << player << " wins" << std::endl;
					for (int i = 0; i < rowToWin; ++i)
						board[x - i][y + i] = 3;
				}
				return true;
			}
		}
	}
	
	return false;
}
