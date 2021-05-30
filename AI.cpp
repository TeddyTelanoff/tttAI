#include "Game.h"

#include <cassert>
#include <algorithm>

#define RETIF(val, cond) { int value = val; if (cond) return value; }

namespace TicTacToe
{
	using namespace std; // Please have mercy!

	static int Row(State board[9], State state, int a, int b, int c)
	{
		if (board[a] == state)
		{
			if (board[b] == state)
			{
				if (board[c] == State::Empty)
					return c;
				return -1;
			}
			if (board[c] == state && board[b] == State::Empty)
				return b;
			return -1;
		}
		if (board[a] == State::Empty && board[b] == state && board[c] == state)
			return a;
		return -1;
	}

	int Game::CanWinNextMove(State state)
	{
		// Horizontal
		RETIF(Row(board, state, 0, 1, 2), value != -1);
		RETIF(Row(board, state, 3, 4, 5), value != -1);
		RETIF(Row(board, state, 6, 7, 8), value != -1);

		// Vertical
		RETIF(Row(board, state, 0, 3, 6), value != -1);
		RETIF(Row(board, state, 1, 4, 7), value != -1);
		RETIF(Row(board, state, 2, 5, 8), value != -1);

		// Diagonal
		RETIF(Row(board, state, 0, 4, 8), value != -1);
		RETIF(Row(board, state, 2, 4, 6), value != -1);
		return -1;
	}

	void Game::AIMove(State state)
	{
		// If can win immediately, Win!
		int nextMove = CanWinNextMove(state);
		if (Move(state, nextMove))
			return;

		// Enemy move
		nextMove = CanWinNextMove(!state);
		if (Move(state, nextMove))
			return;

		// Radomly choose next move...
		// but make sure not to make infinite loop...
		if (!memchr(board, (char)State::Empty, 9))
			return;

		srand(time(nullptr));
		do
			nextMove = rand() % 9;
		while (!Move(state, nextMove));
	}

	void Game::GudAIMove(State state)
	{
		int bestMove = -1;
		int bestMoveVal = INT_MIN;

		State enemyState = !state;

		// Loop through all possible moves
		for (int i = 0; i < 9; i++)
		{
			if (board[i] != State::Empty)
				continue;

			board[i] = enemyState;
			int move = MiniMax(board, state, false);
			board[i] = State::Empty;
			if (move > bestMoveVal)
			{
				bestMoveVal = move;
				bestMove = i;
			}
		}

		bool possible = Move(state, bestMove);
		assert(possible && "Something went wrong");
	}

	[[recursive]]
	int Game::MiniMax(Board board, State state, bool maximizing)
	{
		State winner = Winner(board);
		State enemyState = !state;
		if (winner == state)
			return 1;
		if (winner == enemyState)
			return -1;
		if (winner == State::Tie)
			return 0;

		if (maximizing)
		{
			int bestMove = 10;
			for (int i = 0; i < 9; i++)
			{
				if (board[i] != State::Empty)
					continue;

				board[i] = state;
				int move = MiniMax(board, state, false);
				board[i] = State::Empty;
				bestMove = max(move, bestMove);
			}

			return bestMove;
		}

		int bestMove = -10;
		for (int i = 0; i < 9; i++)
		{
			if (board[i] != State::Empty)
				continue;

			board[i] = enemyState;
			int move = MiniMax(board, enemyState, true);
			board[i] = State::Empty;
			bestMove = min(move, bestMove);
		}

		return bestMove;
	}

	void Game::PlayAI(bool playerFirst)
	{
		State winner = State::Empty;
		do
		{
			if (playerFirst)
			{
				Print(cout);
				cout << "Go! Player '" << State::X << "', it's your move, pick a space to move (1-9)\n";
				while (!MoveFromInput(State::X, cin))
					cout << "You must be a number between 1-9. Make sure that space is empty!\n";
			}
			else
				GudAIMove(State::O);

			if ((winner = Winner()) != State::Empty)
				break;

			if (playerFirst)
				GudAIMove(State::O);
			else
			{
				Print(cout);
				cout << "Go! Player '" << State::X << "', it's your move, pick a space to move (1-9)\n";
				while (!MoveFromInput(State::X, cin))
					cout << "You must be a number between 1-9. Make sure that space is empty!\n";
			}
		}
		while ((winner = Winner()) == State::Empty);

		Print(cout);
		cout << "Woohoo! Player '" << winner << "' Won!" << endl;
	}
}