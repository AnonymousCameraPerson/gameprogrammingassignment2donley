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
	void select_card(int row, int col);
	void random_create();
	std::string get_shape(int index1, int index2);
private:
	char board[5][5];
	std::string pattern[5][5];
};

