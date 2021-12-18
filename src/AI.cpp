#include "AI.h"

int AI::alphabeta(Board *board, int player, int alpha, int beta, int depth)
{
	if (board->getSpaces() == 0)
		return 0;

	for (int x = 0; x < board->getWidth(); ++x)
	{
		if (board->playColumn(x, player))
		{
			if (board->checkWin(player, false))
			{
				board->unplayColumn(x);
				return (board->getWidth() + board->getHeight() + 1 - board->getMovesUsed()) / 2;
			}
			board->unplayColumn(x);
		}
	}

	int max = (board->getWidth() + board->getHeight() - 1 - board->getMovesUsed()) / 2;
	if (beta > max)
	{
		beta = max;
		if (alpha >= beta) return beta;
	}

	if (depth == 0)
		return 0;

	if (player == 2)
	{
		for (int x = 0; x < board->getWidth(); ++x)
		{
			if (board->playColumn(x, player))
			{
				int score = -alphabeta(board, 1, alpha, beta, depth - 1);
				board->unplayColumn(x);

				if (score >= beta) return score;
				if (score > alpha) alpha = score;
			}
		}
	}
	else
	{
		for (int x = 0; x < board->getWidth(); ++x)
		{
			if (board->playColumn(x, player))
			{
				int score = -alphabeta(board, 2, alpha, beta, depth - 1);
				board->unplayColumn(x);

				if (score >= beta) return score;
				if (score > alpha) alpha = score;
			}
		}
	}

	return alpha;
}

AIMove AI::getBestMove()
{
	int score = -10000;
	int best = 0;

	std::cout << "MOVES: " << moves.size() << std::endl;

	for (int i = 0; i < (int)moves.size(); ++i)
	{
		if (moves[i].score > score)
		{
			score = moves[i].score;
			best = i;
		}
	}

	return moves[best];
}