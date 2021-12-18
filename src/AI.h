#ifndef AI_H
#define AI_H

#include <iostream>
#include <vector>

#include "Board.h"

struct AIMove
{
	int column;
	int score;

	AIMove() {}
	AIMove(int score) {
		this->score = score;
	}
};

class AI
{
	private:
		std::vector<AIMove> moves;
		int maxDepth = 7;
		unsigned long long nodeCount = 0;

	public:
		AI() {}
		~AI() {}

		int alphabeta(Board *board, int player, int alpha, int beta, int depth);
		AIMove getBestMove();
		unsigned long long getNodeCount();
};

#endif