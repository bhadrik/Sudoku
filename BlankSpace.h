#include <iostream>
#include <algorithm>
using namespace std;

class BlankSpace{
public:
	BlankSpace(){
		applicableNumber = 0;
		objectNumber = 0;
		rowAddress = 0;
		columnAddress = 0;
		possibleNumbers = 0;
		isFilled = false;
	}
	
	void display(){
		cout<<"\nOBJ "<<objectNumber<<" isFilled: "<<isFilled<<endl;
		cout<<"("<<rowAddress+1<<","<<columnAddress+1<<")"<<" pNum:"<<possibleNumbers<<" bit:"<<willCome[0]<<endl;
		cout<<"1 2 3 4 5 6 7 8 9"<<endl;
		for(short a=1;a<10;a++)	cout<<willCome[a]<<" ";
		cout<<"\n";
	}
	
	bool isFilled;
	short objectNumber,possibleNumbers,applicableNumber,
				rowAddress,columnAddress;
	bool willCome[10] = {0,1,1,1,1,1,1,1,1,1};
	static short count[9];

	void initialProcess(short sudoku[9][9]){
		// cout<<"("<<rowAddress+1<<","<<columnAddress+1<<")";
		countPossibleNumbers();
		if(possibleNumbers==1){
			willCome[0]=1;
			apply(sudoku);
		}
		else applicableNumber = 0;
	}

private:
	void countPossibleNumbers(){
		possibleNumbers = 0;
		for(short i=1;i<10;i++){
			if(willCome[i]){
				possibleNumbers++;
				applicableNumber = i;
			}
			if(possibleNumbers!=1)
				applicableNumber = 0;
		}
	}
	
	void apply(short sudoku[9][9]){
		// cout<<"Apply:"<<"("<<rowAddress+1<<","<<columnAddress+1<<")"<<endl;
		// cout<<"ok:"<<objectNumber+1<<endl;
		sudoku[rowAddress][columnAddress] = applicableNumber;
		isFilled = true;
	}
};
//Initialize Blank class static member
short BlankSpace::count[9] = {0,0,0,0,0,0,0,0,0};