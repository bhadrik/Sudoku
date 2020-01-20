#include <iostream>
#include <algorithm>
using namespace std;

short sudoku[9][9]={
	2,7,5,6,4,0,8,3,0, //1
	9,4,8,5,3,0,6,0,2, //2
	6,3,1,8,2,7,5,4,0, //3
	//-----------------
	0,6,0,0,5,3,0,0,4, //4
	7,5,4,2,0,8,3,0,6, //5
	0,2,3,4,9,6,0,5,0, //6
	//-----------------
	3,8,0,0,6,2,4,0,5, //7
	4,0,2,1,0,5,7,6,3, //8
	5,0,6,3,0,4,0,0,0  //9
};

class Blank{
public:
	Blank(){
		applicableNumber = 0;
		objectNumber = 0;
		rowAddress = 0;
		columnAddress = 0;
		possibleNumbers = 0;
	}

	bool isFilled = false;
	short objectNumber,possibleNumbers;
	short rowAddress,columnAddress;
	bool willCome[10] = {0,1,1,1,1,1,1,1,1,1};
	static short count[9];

	static void printCount(){
		for(short i=0;i<9;i++)
			cout<<count[i]<<" ";
		cout<<endl;
	}

	void initialProcess(){
		// cout<<"("<<rowAddress+1<<","<<columnAddress+1<<")";
		countPossibleNumbers();
		if(possibleNumbers==1){
			willCome[0]=1;
			apply();

		}
		else applicableNumber = 0;
	}

	void display(){
		cout<<"\nOBJ "<<objectNumber<<" detail "<<possibleNumbers<<" "<<isFilled<<endl;
		cout<<"("<<rowAddress+1<<","<<columnAddress+1<<")"<<" pNum:"<<possibleNumbers<<" bit:"<<willCome[0]<<endl;
		cout<<"1 2 3 4 5 6 7 8 9"<<endl;
		for(short a=1;a<10;a++)	cout<<willCome[a]<<" ";
		cout<<"\n";
	}

private:
	short applicableNumber=0;
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
	void apply(){
		// cout<<"Apply:"<<"("<<rowAddress+1<<","<<columnAddress+1<<")"<<endl;
		// cout<<"ok:"<<objectNumber+1<<endl;
		sudoku[rowAddress][columnAddress] = applicableNumber;
		isFilled = true;
	}
};

short Blank::count[9] = {0,0,0,0,0,0,0,0,0};

void read(){
	char ch='A';
	cout<<"  1 2 3 4 5 6 7 8 9\n"
			<<"--------------------\n";
	for(short i=0;i<9;i++){
		cout<<ch++<<'|';
		for(short j=0;j<9;j++){
			cin>>sudoku[i][j];
		}
		cout<<endl;
	}
}

void printCount(short *count){
	cout<<count[0];
	for(short i=1;i<9;i++)
	cout<<","<<count[i];
	cout<<endl;
}

short countBlank(){
	short count=0;
	for(short i=0;i<9;i++){
		for(short j=0;j<9;j++){
			if(sudoku[i][j]!=0) count++;
		}
	}
	// cout<<"Filed: "<<count<<endl;
	// cout<<"Blank: "<<81-count<<endl;
	return (81-count);
}

void displaySudoku(){
	cout<<"    1 2 3 | 4 5 6 | 7 8 9\n"
			<<"-------------------------\n";
	for(short i=0;i<9;i++){
			cout<<i+1;
		for(short j=0;j<9;j++){
			if(j==0) cout<<' ';
			if(j%3==0) cout<<"| ";
			if(sudoku[i][j]==0) cout<<' '/*Print instead of 0*/<<' ';
			else cout<<sudoku[i][j]<<' ';
		}
		cout<<endl;
		if(i==2 || i==5) cout<<"--|-------|-------|------\n";
	}
	cout<<"-------------------------\n";
}

//fill function fills the willCome field of sudoku
void initialFill(Blank &obj){
	short a=0,b=0;
	bool possible=true;
	//row
	for(short i=0;i<9;i++) obj.willCome[sudoku[obj.rowAddress][i]] = 0;
	//column
	for(short i=0;i<9;i++) obj.willCome[sudoku[i][obj.columnAddress]] = 0;
	//3x3
	if(obj.rowAddress<3) a=0; else if(obj.rowAddress<6) a=3; else if(obj.rowAddress<9) a=6;
	if(obj.columnAddress<3) b=0; else if(obj.columnAddress<6) b=3; else if(obj.columnAddress<9) b=6;
	short x=a+3,y=b+3;
	for(short i=a;i<x;i++)
		for(short j=b;j<y;j++){
			obj.willCome[sudoku[i][j]] = 0;
		}
	obj.initialProcess();
}

// short indexOf(short num){
// 	for(short i=0;i<9;i++)
// 		if(num == Blank::count[i]) return i;
// }

// void solve(Blank* obj){
// 	for(short i=0;i<9;i++)
// 		if(Blank::count[i]==9) Blank::count[i]=-1;
// 	short *maximaum = max_element(Blank::count,Blank::count+9);
// 	short targetNumber = indexOf(*maximaum);
// }

short countBlankObjects(Blank* obj, short blank){
	short count=0;
	for(short i=0;i<blank;i++){
		if(!(obj[i].isFilled)) count++;
	}
	return count;
}

//Driver Function
int main(){
	short blank = countBlank();
	short k = 0;
	short count[9] = {0,0,0,0,0,0,0,0,0};
	Blank obj[blank];

	cout<<"Inpuut"<<endl;
	displaySudoku();

	//Initializing each object
	for(short i=0;i<9;i++){
		for(short j=0;j<9;j++){
			Blank::count[sudoku[i][j] - 1]++;
			if(sudoku[i][j]==0){
				obj[k].rowAddress=i;
				obj[k].columnAddress=j;
				obj[k].objectNumber = k;
				k++;
			}
		}
	}

	{
		short avail = blank;
		while(avail){
			// cout<<"----------------"<<endl;
			for(short i=0;i<blank;i++){
				if(!obj[i].isFilled){
					initialFill(obj[i]);
					// obj[i].display();
					// for(short j=1;j<10;j++)
					// 	if(obj[i].willCome[j])
					// 	cout<<j<<" ";
					// cout<<endl;
				}
			}
			avail = countBlankObjects(obj,blank);
		}
		cout<<"\nOutput"<<endl;
		displaySudoku();

		return 0;
	}
}
