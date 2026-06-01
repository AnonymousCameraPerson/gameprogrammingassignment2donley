//Lucia Donley
#include"game_logic.h"
#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <thread>
#include <chrono>
#include <cstdio>



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
std::string game_logic::select_card(int row, int col) {

	std::string shape = get_shape(row, col);
	return shape;
	
	//if (shape != "black_rec" && turn ==0) {
	//	shape1 = shape;
	//	row1 = x;
	//	col1 = y;
	//	turn=1;
	//	//reveal
	//}
	//else if (shape != "black_rec" && turn == 1) {
	//	shape2 = shape;
	//	turn = 0;
	//	if (compare(shape1, shape2)) {
	//		//leave cards facing up
	//		matched += 1;
	//	}
	//	else {
	//		shape1 = get_shape(4, 4);
	//		shape2 = get_shape(4, 4);

	//		//turn around
	//		al_draw_filled_rectangle(x-100, y-100, x + 100, y + 100, al_map_rgb(0, 0, 0)); //black color
	//		al_draw_filled_rectangle(row1-100, col1-100, row1 + 100, col1 + 100, al_map_rgb(0, 0, 0));
	//		return shape2;
	//	}
	//	
	//
	//return shape;

}

void game_logic::checkShapes(std::string shape, int& turn, int x, int y, int& matched, int& remaining) {


	if (shape != "black_rec" && turn == 0) {
		shape1 = shape;
		row1 = x;
		col1 = y;
		turn = 1;
		//reveal
	}
	else if (shape != "black_rec" && turn == 1) {
		shape2 = shape;
		turn = 0;
		if (compare(shape1, shape2)) {
			//leave cards facing up
			matched += 1;
			remaining -= 1;
		}
		else {
			
			//std::this_thread::sleep_for(std::chrono::seconds(5));
			//system("timeout /t 5 /nobreak");
			std::this_thread::sleep_for(std::chrono::seconds(5));
			//turn around
			al_draw_filled_rectangle(x - 80, y - 80, x + 80, y + 80, al_map_rgb(0, 0, 0)); //black color
			al_draw_filled_rectangle(row1 - 80, col1 - 80, row1 + 80, col1 + 80, al_map_rgb(0, 0, 0));
			
		}

	}
}

bool game_logic::compare(std::string shape, std::string pattern) {
	if (shape == pattern) {
		//leave cards turned over
		return true;
	}	
	//turn over after 5 seconds
	return false;
	
}
//
//void game_logic::draw_status() {
//	//write status in bottom right hand square
//	//ALLEGRO_FONT* font = al_load_font("college.ttf", 24, 0);
//
//	ALLEGRO_FONT* font = al_load_font("college.ttf", 24, 0);
//
//	al_draw_textf(font, al_map_rgb(255, 255, 255), 730, 650, ALLEGRO_ALIGN_LEFT, "Matched: %i", matched);
//	al_draw_textf(font, al_map_rgb(255, 255, 255), 730, 680, ALLEGRO_ALIGN_LEFT, "Remaining: %i", remaining);
//	
//	al_flip_display();
//	al_destroy_font(font);
//}


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


void game_logic::done(bool& tie, bool& xwon, bool& owon)
{
	//
}




