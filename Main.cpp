#include "Game.h"

#include <string>
using namespace std; // Please don't hurt me, I have a family!

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
	char first = 0;

	do
	{
		cout << "Do you wanna start first? (Y/N)";

		string str;
		getline(cin, str);
		if (str.length() == 1)
		{
			first = toupper(str[0]);
		}
	}
	while (first != 'Y' && first != 'N');
	
	TicTacToe::Game game;
	game.PlayAI(first == 'Y');
	
	system("pause");
}