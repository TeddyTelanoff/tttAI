#pragma once

#include <string>
#include "Game.h"

namespace TicTacToe
{
	using namespace std; // Please have mercy!

	void Game::Print(ostream &os)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 2; x++)
			{
				int i = x + y * 3;
				if (board[i] == State::Empty)
					os << i + 1;
				else
					os << board[i];
				os << '|';
			}
			int i = 2 + y * 3;
			if (board[i] == State::Empty)
				os << i + 1;
			else
				os << board[i];
			os << '\n';
		}
	}

	bool Game::MoveFromInput(State state, istream &is)
	{
		string tmp;
		getline(is, tmp);
		try
		{
			int pos = stoi(tmp);
			return Move(state, pos - 1);
		}
		catch (const invalid_argument &)
		{ return false; }
	}

	bool Game::Move(State state, int pos)
	{
		if (pos < 0 || pos >= 9)
			return false;

		if (board[pos] != State::Empty)
			return false;

		board[pos] = state;
		return true;
	}

	void Game::Play()
	{
		State player = State::O;
		do
		{
			Print(cout);
			player = !player;
			cout << "Go! Player '" << player << "', it's your move, pick a space to move (1-9)\n";
			while (!MoveFromInput(player, cin))
				cout << "You must be a number between 1-9. Make sure that space is empty!\n";
		}
		while (Winner() == State::Empty);

		Print(cout);
		cout << "Woohoo! Player '" << player << "' Won!" << endl;
	}

	State Game::Winner()
	{ return Winner(board); }

	State Game::Winner(Board board)
	{
		State tmp;
		if (board[0] != State::Empty)
		{
			tmp = board[0];
			if (board[1] == tmp && board[2] == tmp)
				return tmp;
			if (board[4] == tmp && board[8] == tmp)
				return tmp;
			if (board[3] == tmp && board[6] == tmp)
				return tmp;
		}
		if (board[4] != State::Empty)
		{
			tmp = board[4];
			if (board[1] == tmp && board[7] == tmp)
				return tmp;
			if (board[3] == tmp && board[5] == tmp)
				return tmp;
			if (board[2] == tmp && board[6] == tmp)
				return tmp;
		}
		if (board[8] != State::Empty)
		{
			tmp = board[8];
			if (board[2] == tmp && board[5] == tmp)
				return tmp;
			if (board[6] == tmp && board[7] == tmp)
				return tmp;
		}

		if (!memchr(board, (char)State::Empty, 9))
			return State::Tie;
		return State::Empty;
	}
}