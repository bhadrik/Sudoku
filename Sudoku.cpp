#include "Sudoku.h"
#include <windows.h>

/*
Example for manually input
0 6 0 9 0 1 4 2 0
0 0 3 0 7 0 0 0 5
0 0 0 0 0 5 6 0 0
0 0 9 3 0 0 8 7 0
0 5 0 0 6 0 0 0 0
0 7 0 0 1 0 2 0 0
0 0 0 0 9 0 0 3 2
4 0 7 0 0 0 0 0 0
0 0 0 0 0 0 0 6 0
*/

int main() {
	short sudoku[9][9]={
        0,0,0,8,0,0,0,2,0,
        6,5,8,0,0,0,0,0,7,
        0,9,0,0,0,0,0,8,3,
        0,0,0,9,0,0,0,0,0,
        0,6,2,0,0,0,0,0,4,
        0,0,7,0,2,0,8,1,0,
        5,0,0,7,0,2,0,0,0,
        0,0,4,0,0,0,6,0,8,
        0,0,0,0,6,0,0,4,0
	};

	Sudoku su_solver(sudoku);
	
	//Ask for input
	su_solver.input();
	
	//Print inputted sudoku
	cout<<"Input"<<endl;
	su_solver.display();
	
	//Start solving
	su_solver.solve();
	
	//Prnit sudoku afer trying to solve
	cout<<"\nOutput"<<endl;
	su_solver.display();
	
	system("PAUSE");
	return 0;
}
