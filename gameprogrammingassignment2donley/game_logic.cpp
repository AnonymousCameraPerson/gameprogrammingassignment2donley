//Lucia Donley
#include"game_logic.h"
#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

//void game_logic::setup()
//{
//	for (int i = 0; i < 5; i++)
//		for (int j = 0; j < 5; j++)
//			board[i][j] = 'n';
//}
//bool game_logic::set_x(int x, int y)
//{
//	if (board[x][y] == 'n')
//	{
//		board[x][y] = 'x';
//		return true;
//	}
//	return false;
//
//}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//store what's in each box
//track selections (first and second pick)
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//instead of set_x:
std::string game_logic::select_card(int row, int col, int& turn) {
	std::string shape = get_shape(row, col);
	
	if (shape != "" && turn ==0) {
		shape1 = shape;
		turn=1;
		//reveal
	}
	else if (shape != "" && turn == 1) {
		shape2 = shape;
		turn == 0;
		if (compare(shape1, shape2)) {
			//leave cards facing up
			matched += 1;

		}
		else {
			shape = get_shape(4, 4);
			shape1 = shape;
			shape2 = shape;
			//turn around
		}
		//compare
	}
	return shape;

		//reveal or compare
		//if turn==0, they have to pick another card
		//else, compare
	//}
	//else, you have to pick a different 
	
}

bool game_logic::compare(std::string shape, std::string pattern) {
	if (shape == pattern) {
		//leave cards turned over
		return true;
	}	
	//turn over after 5 seconds
	return false;
	
}



void game_logic::random_create()
{
	std::array<std::string, 25> arr = {"filled_triangle", "filled_triangle","filled_rectangle","filled_rectangle", "circle",
		"circle", "rec_with_line", "rec_with_line", "rec_with_circle", "rec_with_circle", "circle_with_line",
		"circle_with_line", "pieslice_with_line", "pieslice_with_line", "rectangles", "rectangles", "circles_with_line",
		"circles_with_line", "pieslice", "pieslice", "ellipse", "ellipse", "rounded_rec", "rounded_rec", "black_rec"};

	//std::string pattern[5][5];

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(arr.begin(), arr.begin() + 24, g);

	for (int r = 0; r < 5; ++r) {
		for (int c = 0; c < 5; ++c) {
			pattern[r][c] = arr[(r * 5) + c];
		}
	}
	
}

std::string game_logic::get_shape(int index1, int index2) {

	return pattern[index1][index2];
}


//bool game_logic::set_o(int x, int y)
//{
//	if (board[x][y] == 'n')
//	{
//		board[x][y] = 'o';
//		return true;
//	}
//	return false;
//}
void game_logic::done(bool& tie, bool& xwon, bool& owon)
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




