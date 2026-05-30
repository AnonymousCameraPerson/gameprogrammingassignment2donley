//Lucia Donley
#include"logic.h"

void logic::setup()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			board[i][j] = 'n';
}
bool logic::set_x(int x, int y)
{
	if (board[x][y] == 'n')
	{
		board[x][y] = 'x';
		return true;
	}
	return false;

}
bool logic::set_o(int x, int y)
{
	if (board[x][y] == 'n')
	{
		board[x][y] = 'o';
		return true;
	}
	return false;
}
void logic::done(bool& tie, bool& xwon, bool& owon)
{
	//if //cards match
	//{
	//	xwon = true;
	//	tie = false;
	//	owon = false;
	//}
	//else if //(cards don't match)
	//{
	//	xwon = false;
	//	tie = false;
	//	owon = true;
	//}
	
}




