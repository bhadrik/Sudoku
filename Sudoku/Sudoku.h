#include <iostream>
#include <algorithm>
#include "BlankSpace.h"
#define MAXLOOP 20

using namespace std;

class Sudoku {
	
private:
	short sudoku[9][9];
	short suBackup[9][9];

	BlankSpace obj[9][9];
	BlankSpace objBackup[9][9];

	short loop = 0;
	short loopBackup = 0;

	short blank = 0;
	short totalEmpty;
	short m = -1, n = -1, value = 0;

public:
	Sudoku(short su[9][9]);

	//Initalize it's object
	void solve();

	void input();

	void display();

	//display object by providing its index
	void displayObj(short);

	//display object by providing its location in sudoku
	void displayObj(short, short);

	//fill function fills the mask field of sudoku
	void processObj(BlankSpace& objOne);

	void deepSearch(BlankSpace& objOne, short, short);

	//this function fill one of two blank space first found 3x3 box
	void athiyo(short&, short&, short&);

	//If the function "athiyo" fills wrong number then this will alter those numbers
	void fix(short, short, short);

	short countBlankObjects();

	short countEmptyFields();
};
