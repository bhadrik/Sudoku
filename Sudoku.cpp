#include "Sudoku.h"
/*
*	Camel Case: firstName
*	Pascal Case:FirstName
*	Hungarian Notation: strFirstName
*/
/*copy for Input
	2 7 5 6 4 0 8 3 0
	9 0 8 0 3 0 6 0 2
	6 3 0 0 0 7 5 4 0
	0 6 0 0 5 3 0 0 4
	7 5 4 2 0 8 3 0 6
	0 2 3 0 0 6 0 5 0
	0 8 0 0 6 2 4 0 5
	4 0 2 1 0 5 7 0 3
	5 0 6 3 0 0 0 0 0
*/

//Driver Function
int main(){
	short sudoku[9][9]={
		2,7,5,6,4,0,8,3,0, //1
		9,4,8,5,3,0,6,0,2, //2
		0,0,0,0,0,0,0,0,0, //3
		//-----------------
		0,6,0,0,5,3,0,0,4, //4
		0,0,0,0,0,0,0,0,0, //5
		0,2,3,4,9,6,0,5,0, //6
		//-----------------
		0,8,0,0,6,2,4,0,5, //7
		0,0,2,1,0,5,7,6,3, //8
		0,0,6,3,0,4,0,0,0  //9
	};
	// Example 2
	// short sudoku[9][9]={
	// 	5,0,0,0,4,9,0,0,0, //1
	// 	0,0,9,0,0,0,1,0,8, //2
	// 	0,0,7,0,0,0,0,0,5, //3
	// 	//-----------------
	// 	0,0,0,9,0,0,0,0,2, //4
	// 	2,1,0,4,0,7,0,9,0, //5
	// 	4,0,6,0,0,0,7,9,0, //6
	// 	//-----------------
	// 	0,6,2,0,0,3,0,1,0, //7
	// 	0,0,5,2,0,0,3,6,0, //8
	// 	3,0,0,6,1,0,8,0,0  //9
	// };
	
	Sudoku s(sudoku);

	// s.input();
	
	cout<<"Input"<<endl;
	s.display();
	
	s.solve();
	
	cout<<"\nOutput"<<endl;
	s.display();
	return 0;
}
