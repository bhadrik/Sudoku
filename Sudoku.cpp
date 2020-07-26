#include "Sudoku.h"

int main(){
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

	Sudoku s(sudoku);

	s.input();

	cout<<"Input"<<endl;
	s.display();

	s.solve();

	cout<<"\nOutput"<<endl;
	s.display();

	char ch;
	cin>>ch;
	return 0;
}
