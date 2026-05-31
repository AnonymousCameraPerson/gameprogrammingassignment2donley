// Lucia Donley
#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>	
#include <allegro5\allegro_native_dialog.h> 
#include "logic.h"
#include <string>
#include <algorithm>
#include <random>
//Reveal shapes
//Hide shapes again if they don't match
//You already ahve the pattern:
//Check if a move is valid (set_x, set_o)
//Then draw something
//That becomes:
//Check if a card is selected
//Then reveal or compare it

//game_objects pattern[5][5];
bool already_played[5][5];
std::string get_shape(int index); // given a box number(index) it gets what is in that box in either the patter or guess.
//void set_shape(int index); //given a box number and shape will fill in the pattern and guess.
//bool checkGuess() //compares the guess and pattern.
//void resetGame() //reset / clear the game.
void random_create(); //given the number of images needing to be generated.The objects will be randomly generated and randomly placed in the grid.
//get_mouse_input() //get mouse input
//following funtions I added
void draw_grid(); //draws 5x5 grid
void draw_status(); //draws the bottom right hand square and status info
int get_mouse_input();
//void draw_objects(int x, int y); //x and y are center of box



//Only global variables I can have are
int mx;
int my;

void set_graphics_x_o(int x, int y, game_logic& game_logic);

void game_message(bool& gameover, game_logic& game_logic);
void turn_xo(int x, int y, int& turn, int boardx, int boardy, game_logic& game_logic);

int main(void)
{


	game_logic  game_logic;
	int posX = 0, posY = 0;
	bool gameover = false;
	ALLEGRO_DISPLAY* Screen = NULL;
	int width = 900, height = 768;

	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}


	Screen = al_create_display(width, height);
	if (Screen == NULL)
	{
		al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}

	if (!al_install_mouse()) {
		al_show_native_message_box(Screen, "Error!", "Failed to initialize the mouse!\n.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return (-1);
	}
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	bool draw = false, done = false;;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	event_queue = al_create_event_queue();


	al_register_event_source(event_queue, al_get_display_event_source(Screen));
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_register_event_source(event_queue, al_get_mouse_event_source());

	game_logic.setup();
	draw_grid();
	draw_status();
	//game_message(gameover, game_logic);

	al_flip_display();
	while (!done && !gameover)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				posX = ev.mouse.x;
				posY = ev.mouse.y;

				draw = true;
			}
		}
		draw_grid();
		draw_status();
		game_message(gameover, game_logic);
		if (draw)
		{

			set_graphics_x_o(posX, posY, game_logic);

			draw = false;
		}
		al_flip_display();
	}
	al_rest(5.0);
	al_destroy_event_queue(event_queue);
	al_destroy_display(Screen);						//destroy our display object

	return 0;
}


void draw_grid()
{
	//vertical lines
	al_draw_line(180, 0, 180, 768, al_map_rgb(255, 255, 255), 2);
	al_draw_line(360, 0, 360, 768, al_map_rgb(255, 255, 255), 2);
	al_draw_line(540, 0, 540, 768, al_map_rgb(255, 255, 255), 2);
	al_draw_line(720, 0, 720, 768, al_map_rgb(255, 255, 255), 2);
	al_draw_line(900, 0, 900, 768, al_map_rgb(255, 255, 255), 2);
	
	//horizontal lines
	al_draw_line(0, 160, 900, 160, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 320, 900, 320, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 480, 900, 480, al_map_rgb(255, 255, 255), 2);
	al_draw_line(0, 640, 900, 640, al_map_rgb(255, 255, 255), 2);	

}




void draw_status() {
	//write status in bottom right hand square
	//ALLEGRO_FONT* font = al_load_font("college.ttf", 24, 0);
	//al_draw_text(font, al_map_rgb(255, 255, 255), 850, 520, ALLEGRO_ALIGN_LEFT, "Matched:\n");
	//al_draw_text(font, al_map_rgb(255, 255, 255), 850, 550, ALLEGRO_ALIGN_LEFT, "Remaining:\n");
}


//void draw_x(int x, int y)
//{
//	al_draw_pieslice(x, y, 30, 90, 30, al_map_rgb(50, 223, 0), 4);
//}
//void draw_o(int x, int y)
//{
//	al_draw_rounded_rectangle(x - 20, y - 20, x + 20, y + 20, 5, 5, al_map_rgb(255, 0, 0), 4);
//}



void draw_objects(int x, int y) {

	std::string shape = game_logic.get_shape();
	
	if (shape=="filled_triangle")
		al_draw_filled_triangle(x-20, y-20, x+20, y+20, x, y, al_map_rgb(200, 0, 0));
	else if (shape=="filled_rectangle")
		al_draw_filled_rectangle(x - 20, y - 20, x + 20, y + 20, al_map_rgb(255, 0, 0));
	else if (shape=="circle")
		al_draw_circle(x, y, 20, al_map_rgb(255, 255, 0), 4);
	else if (shape == "rec_with_line")
		al_draw_filled_rectangle(x - 20, y - 20, x + 20, y + 20, al_map_rgb(0, 255, 0));
		al_draw_line(x - 20, y - 20, x + 20, y + 20, al_map_rgb(255, 255, 0), 2);
	else if (shape=="rec_with_circle")
		al_draw_filled_rectangle(x - 20, y - 20, x + 20, y + 20, al_map_rgb(255, 0, 255));
		al_draw_circle(x, y, 20, al_map_rgb(255, 155, 0), 4);
	else if (shape=="circle_with_line")
		al_draw_line(x - 20, y + 20, x + 20, y - 20, al_map_rgb(255, 255, 0), 2);
		al_draw_circle(x, y, 20, al_map_rgb(255, 255, 0), 4);
	else if (shape=="pieslice_with_line")
		al_draw_pieslice(x - 20, y - 20, 10 ,90, 10, al_map_rgb(200, 0, 0), 4);
		al_draw_line(x - 20, y - 20, x + 20, y + 20, al_map_rgb(255, 255, 0), 2);
	else if (shape=="rectangles")
		al_draw_rectangle(x - 20, y - 20, x + 20, y + 20, al_map_rgb(255, 0, 0), 4);
		al_draw_filled_rectangle(x - 10, y - 10, x + 10, y + 10, al_map_rgb(50, 200, 80));
	else if (shape=="circles_with_line")
		al_draw_line(x, y - 20, x, y + 20, al_map_rgb(255, 0, 0), 2);
		al_draw_circle(x, y, 20, al_map_rgb(100, 100, 80), 4);
		al_draw_circle(x, y, 40, al_map_rgb(0, 200, 0), 4);
	else if (shape=="pieslice")
		al_draw_pieslice(x, y, 30, 90, 30, al_map_rgb(50, 223, 0), 4);
	else if (shape=="ellipse")
		al_draw_ellipse(x, y, 20, 10, al_map_rgb(255, 0, 0), 4);
		al_draw_circle(x, y, 20, al_map_rgb(255, 255, 0), 4);
	else if (shape=="rounded_rec")
		al_draw_rounded_rectangle(x - 20, y - 20, x + 20, y + 20, 5, 5, al_map_rgb(255, 0, 0), 4);

	}

}


void select_card(int x, int y, int& turn, int boardx, int boardy, logic& game_logic)
{
	ALLEGRO_FONT* font = al_load_font("college.ttf", 24, 0);
	if (turn == 0)
	{
		//if (game_logic.set_x(boardx, boardy) == true)
		//{
		//	draw_x(x, y);
		//	turn = 1;
		//}

		if (game_logic.select_card(boardx, boardy) == true) {
			draw_shape(x, y);
			turn = 1; //choose another card
			//Reveal card
		}

	}
	else
	{
		if (game_logic.select_card(boardx, boardy) == true)
		{
			draw_shape(x, y);
			turn = 0;
			//Compare card
		}
	}
}
void set_graphics_x_o(int x, int y, logic& game_logic)
{
	static int turn = 0;


	//first row
	if ((x < 180) && (y < 160))
	{
		game_logic.select_card(0, 0);
		//turn_xo(80, 80, turn, 0, 0, game_logic);
	}
	else if ((x < 360) && (x>180) && (y < 160))
	{
		game_logic.select_card(0, 1);
		//turn_xo(270, 80, turn, 0, 1, game_logic);
	}
	else if ((x < 540) && (x > 360) && (y < 160))
	{
		game_logic.select_card(0, 2);
		//turn_xo(450, 80, turn, 0, 2, game_logic);
	}
	else if ((x < 720) && (x>540) && (y<160))
	{
		game_logic.select_card(0, 3);
		//turn_xo(630, 80, turn, 0, 3, game_logic);
	}
	else if ((x < 900) && (x > 720) && (y < 160)) 
	{
		game_logic.select_card(0, 4);
		//turn_xo(820, 80, turn, 0, 4, game_logic);
	}

	//second row
	else if ((x < 180) && (y<320))
	{
		game_logic.select_card(1,0);
		//turn_xo(80, 240, turn, 0, 5, game_logic);
	}
	else if ((x < 360) && (x > 180) && (y < 320))
	{
		game_logic.select_card(1, 1);
		//turn_xo(270, 240, turn, 0, 6, game_logic);
	}
	else if ((x < 540) && (x > 360) && (y < 320) )
	{
		game_logic.select_card(1, 2);
		//turn_xo(450, 240, turn, 0, 7, game_logic);
	}
	else if ((x < 720) && (x > 540) && (y < 320)) 
	{
		game_logic.select_card(1, 3);
		//turn_xo(630, 240, turn, 0, 8, game_logic);
	}
	else if ((x < 900) && (x > 720) && (y < 320) ) 
	{
		game_logic.select_card(1, 4);
		//turn_xo(820, 240, turn, 0, 9, game_logic);
	}

	//third row
	else if ((x < 180) && (y < 480))
	{
		game_logic.select_card(2, 0);
		//turn_xo(80, 400, turn, 0, 10, game_logic);
	}
	else if ((x < 360) && (x > 180) && (y < 480))
	{
		game_logic.select_card(2, 1);
		//turn_xo(270, 400, turn, 0, 11, game_logic);
	}
	else if ((x < 540) && (x > 360) && (y < 480))
	{
		game_logic.select_card(2, 2);
		//turn_xo(450, 400, turn, 0, 12, game_logic);
	}
	else if ((x < 720) && (x > 540) && (y < 480) ) 
	{
		game_logic.select_card(2, 3);
		//turn_xo(630, 400, turn, 0, 13, game_logic);
	}
	else if ((x < 900) && (x > 720) && (y < 480)) 
	{
		game_logic.select_card(2, 4);
		//turn_xo(820, 400, turn, 0, 14, game_logic);
	}

	//fourth row
	else if ((x < 180) && (y < 640))
	{
		game_logic.select_card(3, 0);
		//turn_xo(80, 560, turn, 0, 15, game_logic);
	}
	else if ((x < 360) && (x > 180) && (y < 640))
	{
		game_logic.select_card(3, 1);
		//turn_xo(270, 560, turn, 0, 16, game_logic);
	}
	else if ((x < 540) && (x > 360) && (y < 640))
	{
		game_logic.select_card(3, 2);
		//turn_xo(450, 560, turn, 0, 17, game_logic);
	}
	else if ((x < 720) && (x > 540) && (y < 640)) 
	{
		game_logic.select_card(3, 3);
		//turn_xo(630, 560, turn, 0, 18, game_logic);
	}
	else if ((x < 900) && (x > 720) && (y < 640)) 
	{
		game_logic.select_card(3, 4);
		//turn_xo(820, 560, turn, 0, 19, game_logic);
	}

	//fifth row
	else if ((x < 180) && (y > 640))
	{
		game_logic.select_card(4, 0);
		//turn_xo(80, 720, turn, 0, 20, game_logic);
	}
	else if ((x < 360) && (x > 180) && (y > 640))
	{
		game_logic.select_card(4, 1);
		//turn_xo(270, 720, turn, 0, 21, game_logic);
	}
	else if ((x < 540) && (x > 360) && (y > 640))
	{
		game_logic.select_card(4, 2);
		//turn_xo(450, 720, turn, 0, 22, game_logic);
	}
	else if ((x < 720) && (x > 540) && (y > 640)) 
	{
		game_logic.select_card(4, 3);
		//turn_xo(630, 720, turn, 0, 23, game_logic);
	}
	else if ((x < 900) && (x > 720) && (y > 640)) 
	{
		game_logic.select_card(4, 4);
		//turn_xo(820, 720, turn, 0, 24, game_logic);
	}
}

void game_message(bool& gameover, game_logic& game_logic)
{
	bool xwon = false, owon = false, tie = false;
	game_logic.done(tie, xwon, owon);
	ALLEGRO_FONT* font = al_load_font("college.ttf", 24, 0);

	if (tie == true)
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), 1, 400, ALLEGRO_ALIGN_LEFT, "The game is a tie -- screen will close shortly");
		gameover = true;
	}
	else if (xwon == true)
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), 1, 400, ALLEGRO_ALIGN_LEFT, "X won the game-- screen will close shortly");
		gameover = true;
	}
	else if (owon == true)
	{
		al_draw_text(font, al_map_rgb(255, 255, 255), 1, 400, ALLEGRO_ALIGN_LEFT, "O won the game-- screen will close shortly");
		gameover = true;
	}
	else {
		al_draw_text(font, al_map_rgb(255, 255, 255), 920, 520, ALLEGRO_ALIGN_LEFT, "Matched:\n");
		al_draw_text(font, al_map_rgb(255, 255, 255), 920, 550, ALLEGRO_ALIGN_LEFT, "Remaining:\n");
	}
	al_destroy_font(font);

}


