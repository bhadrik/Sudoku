#include<iostream>
using namespace std;

short int shudoku[9][9]={
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
	short objectNumber,possibleNumbers;
	short rowAddress,columnAddress;
	bool willCome[10] = {0,1,1,1,1,1,1,1,1,1};
	Blank(){
		applicableNumber = 0;
		objectNumber = 0;
		rowAddress = 0;
		columnAddress = 0;
		possibleNumbers = 9;
	}
	void initialProcess(){
		countPossibleNumbers();
		if(possibleNumbers==1){
			willCome[0]=1;
			apply();
		}
		else applicableNumber = 0;
	}

	void display(){
		cout<<"\nOBJ "<<objectNumber<<" detail "<<possibleNumbers<<endl;
		cout<<"("<<rowAddress+1<<","<<columnAddress+1<<")"<<" pNum:"<<possibleNumbers<<" bit:"<<willCome[0]<<endl;
		cout<<"1 2 3 4 5 6 7 8 9"<<endl;
		for(int a=1;a<10;a++)	cout<<willCome[a]<<" ";
		cout<<"\n";
	}
private:
	short applicableNumber;
	void countPossibleNumbers(){
		possibleNumbers = 0;
		for(int i=1;i<10;i++){
			if(willCome[i]) possibleNumbers++;
			applicableNumber = i;
		}
	}
	void apply(){
		cout<<endl<<"I:"<<rowAddress<<"J"<<columnAddress<<endl;
		shudoku[rowAddress][columnAddress] = applicableNumber;
	}
};

void read(){
	char ch='A';
	cout<<"  1 2 3 4 5 6 7 8 9\n"
			<<"--------------------\n";
	for(int i=0;i<9;i++){
		cout<<ch++<<'|';
		for(int j=0;j<9;j++){
			cin>>shudoku[i][j];
		}
		cout<<endl;
	}
}

void printCount(short *count){
	cout<<count[0];
	for(int i=1;i<9;i++)
	cout<<","<<count[i];
	cout<<endl;
}

int countBlank(){
	int count=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(shudoku[i][j]!=0) count++;
		}
	}
	cout<<"Filed: "<<count<<endl;
	cout<<"Blank: "<<81-count<<endl;
	return (81-count);
}

void displaySudoku(){
	char ch='A';
	cout<<"    1 2 3 | 4 5 6 | 7 8 9\n"
			<<"-------------------------\n";
	for(int i=0;i<9;i++){
			cout<<ch++;
		for(int j=0;j<9;j++){
			if(j==0) cout<<' ';
			if(j%3==0) cout<<"| ";
			if(shudoku[i][j]==0) cout<<' '/*Print instade of 0*/<<' ';
			else cout<<shudoku[i][j]<<' ';
		}
		cout<<endl;
		if(ch=='D' || ch=='G') cout<<"--|-------|-------|------\n";
	}
	cout<<"-------------------------\n";
}
//initialFill function fills the willCome field of Sudoku
void initialFill(Blank *obj){
	short a=0,b=0,l=0;
	bool possible=true;

	//row
	for(a=0;a<9;a++) obj->willCome[shudoku[obj->rowAddress][a]] = 0;
	//column
	for(a;a<9;a++) obj->willCome[shudoku[a][obj->columnAddress]] = 0;
	//3x3
	if(obj->rowAddress<3) a=0; else if(obj->rowAddress<6) a=3; else if(obj->rowAddress<9) a=6;
	if(obj->columnAddress<3) b=0; else if(obj->columnAddress<6) b=3; else if(obj->columnAddress<9) b=6;
	short x=a+3,y=b+3;
	for(a;a<x;a++)
		for(b;b<y;b++)
			obj->willCome[shudoku[a][b]] = 0;
	obj->initialProcess();
}

void fillViseNumber(Blank *obj){

}
int main(){
	short blank = countBlank();
	short k = 0;
	short count[9] = {0,0,0,0,0,0,0,0,0};
	Blank obj[blank];

	displaySudoku();
	//calling fill function for each objcet
	for(short i=0;i<9;i++){
		for(short j=0;j<9;j++){
			count[shudoku[i][j] - 1]++;
			if(shudoku[i][j]==0){
				obj[k].rowAddress=i;
				obj[k].columnAddress=j;
				obj[k].objectNumber = k;
				initialFill(&obj[k]);
				k++;
			}
		}
	}

	printCount(count);
	for(int i=0;i<5;i++){
		// obj[i].initialProcess();
		obj[i].display();
	}
	displaySudoku();
	return 0;
}
