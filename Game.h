#pragma once

#include <iostream>

namespace TicTacToe
{
	using namespace std; // Please have mercy!
	enum class State: char
	{
		Empty = ' ',
		X = 'X',
		O = 'O',
	};

	inline State operator !(const State &state)
	{ return state != State::Empty ? (state == State::X ? State::O : State::X) : State::Empty; }

	inline ostream &operator <<(ostream &os, const State &state)
	{ return os << (char)state; }

	class Game
	{
	private:
		State board[9] = {
			State::Empty, State::Empty, State::Empty,
			State::Empty, State::Empty, State::Empty,
			State::Empty, State::Empty, State::Empty,
		};
	public:
		void Print(ostream &os);
		bool MoveFromInput(State state, istream &is);
		bool Move(State state, int pos);
		void Play();
		void PlayAI();
		void AIMove(State state);

		int CanWinNextMove(State state);
		State Winner();
	};
}