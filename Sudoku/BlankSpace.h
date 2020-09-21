#include <iostream>
using namespace std;

class BlankSpace {

private:
	short objectNumber;
	short possibleNumbers;
	short applicableNumber;
	short rowAddress;
	short columnAddress;

	bool status = false;
	bool mask[10] = { 0,1,1,1,1,1,1,1,1,1 };

	void countPossibleNumbers();

	void apply(short sudoku[9][9]);

public:
	BlankSpace();

	void display();

	void finalProcess(short sudoku[9][9]);

	short get(bool, short);

	void set(bool, short, short);

	bool isFilled();

	void changStatus(bool);

	void printMask();

	void forceApply(short suoku[9][9], short);

	//To referesh object. used in deepSearchs.
	void manualProcess(short sudoku[9][9]);
};


