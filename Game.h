#pragma once

#include <iostream>

namespace TicTacToe
{
	using namespace std; // Please have mercy!
	enum class State: char
	{
		Empty = ' ',
		Tie = 'T',
		X = 'X',
		O = 'O',
	};

	using Board = State[9];

	inline State operator !(const State &state)
	{ return state != State::Empty ? (state == State::X ? State::O : State::X) : State::Empty; }

	inline ostream &operator <<(ostream &os, const State &state)
	{ return os << (char)state; }

	class Game
	{
	private:
		Board board = {
			State::Empty, State::Empty, State::Empty,
			State::Empty, State::Empty, State::Empty,
			State::Empty, State::Empty, State::Empty,
		};
	public:
		void Print(ostream &os);
		bool MoveFromInput(State state, istream &is);
		bool Move(State state, int pos);
		void Play();
		void PlayAI(bool playerFirst = true);
		void AIMove(State state);
		void GudAIMove(State state);

		int CanWinNextMove(State state);
		State Winner();
		static State Winner(Board board);
	private:
		[[recursive]]
		static int MiniMax(Board board, State state, bool maximizing);
	};
}