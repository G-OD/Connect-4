#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

class Board
{
	private:
		int width;
		int height;
		std::vector<std::vector<int>> board;
		int rowToWin;
		bool canPlay;
		unsigned int moves = 0;

	public:
		Board() {}
		Board(int w, int h, int win);
		~Board();

		void init();
		void reinit(int width, int height, int rowToWin);

		void print();

		void setRowToWin(int value);

		int getWidth();
		int getHeight();

		int getValue(int x, int y);
		void setValue(int x, int y, int value);
		int getSpaces();

		void reset();
		unsigned int getMovesUsed();
		void resetMovesUsed();

		void allowPlay();
		void disallowPlay();

		bool playColumn(int x, int player);
		void unplayColumn(int x);
		
		int inARow(int player);
		bool checkWin(int player, bool highlight);
};

#endif