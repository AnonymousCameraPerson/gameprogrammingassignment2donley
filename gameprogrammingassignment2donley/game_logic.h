//Lucia Donley
#include <string>
#include <array>
class game_logic
{
public:
	void setup();
	bool set_x(int x, int y);
	bool set_o(int x, int y);
	void done(bool& tie, bool& xwon, bool& owon);
	std::string select_card(int row, int col);
	void checkShapes(std::string shape, int& turn, int x, int y, int& matched, int& remaining);
	void random_create();
	//void draw_status();
	bool compare(std::string shape, std::string pattern);
	std::string get_shape(int index1, int index2);
private:
	char board[5][5];
	std::string pattern[5][5];
	std::string shape1;
	std::string shape2;
	int matched=0;
	int row1;
	int col1;
	int remaining=12;
};

