#include "Game.h"

#include <string>
using namespace std; // Please don't hurt me, I have a family!

static bool Confirm(const string &prompt)
{
	char yes = 0;

	do
	{
		cout << prompt << " (Y/N)";

		string str;
		getline(cin, str);
		if (str.length() == 1)
			yes = toupper(str[0]);
	}
	while (yes != 'Y' && yes != 'N');
	return yes == 'Y';
}

// Handy Function
static bool EqualsIgnoreCase(const string &a, const string &b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}

int main()
{
	TicTacToe::Game game;

	do
	{
		bool startFirst = Confirm("Do you want to start first?");
		game.PlayAI(startFirst);
	}
	while (Confirm("Do you wanna play again?"));
}