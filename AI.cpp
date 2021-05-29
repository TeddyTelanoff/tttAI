#include "Game.h"

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
		if (memchr(board, (char)State::Empty, 9))
			return;
		do
			nextMove = rand() % 9;
		while (!Move(state, nextMove));
	}

	void Game::PlayAI()
	{
		State winner = State::Empty;
		do
		{
			Print(cout);
			cout << "Go! Player '" << State::X << "', it's your move, pick a space to move (1-9)\n";
			while (!MoveFromInput(State::X, cin))
				cout << "You must be a number between 1-9. Make sure that space is empty!\n";

			if ((winner = Winner()) != State::Empty)
				break;

			AIMove(State::O);
			if (!memchr(board, (char)State::Empty, 9))
			{
				Print(cout);
				cout << "It's a tie!" << endl;
				return;
			}
		}
		while ((winner = Winner()) == State::Empty);

		Print(cout);
		cout << "Woohoo! Player '" << winner << "' Won!" << endl;
	}
}