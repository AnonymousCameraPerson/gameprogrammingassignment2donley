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

//pick a card and return which shape it is
std::string game_logic::select_card(int row, int col) {

	std::string shape = get_shape(row, col);
	return shape;
	
}

//figure out which turn it is and determine if you should show the first card or compare the two cards
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

//compare the two cards
bool game_logic::compare(std::string shape, std::string pattern) {
	if (shape == pattern) {
		//leave cards turned over
		return true;
	}	
	//turn over after 5 seconds
	return false;
	
}

//randomly populate the grid
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

//get shape from pattern array
std::string game_logic::get_shape(int index1, int index2) {

	return pattern[index1][index2];
}




