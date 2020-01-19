#include <iostream>
#include <algorithm>
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
		for(int a=1;a<10;a++)	cout<<willCome[a]<<" ";
		cout<<"\n";
	}

private:
	short applicableNumber=0;
	void countPossibleNumbers(){
		possibleNumbers = 0;
		for(int i=1;i<10;i++){
			if(willCome[i]){
				possibleNumbers++;
				applicableNumber = i;
			}
			if(possibleNumbers!=1)
				applicableNumber = 0;
		}
	}
	void apply(){
		cout<<"Apply:"<<"("<<rowAddress+1<<","<<columnAddress+1<<")"<<endl;
		shudoku[rowAddress][columnAddress] = applicableNumber;
		isFilled = true;
	}
};

short Blank::count[9] = {0,0,0,0,0,0,0,0,0};

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

short countBlank(){
	short count=0;
	for(short i=0;i<9;i++){
		for(short j=0;j<9;j++){
			if(shudoku[i][j]!=0) count++;
		}
	}
	// cout<<"Filed: "<<count<<endl;
	// cout<<"Blank: "<<81-count<<endl;
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

//fill unction fills the willCome field of shudoku
void initialFill(Blank &obj){
	short a=0,b=0;
	bool possible=true;
	//row
	for(int i=0;i<9;i++) obj.willCome[shudoku[obj.rowAddress][i]] = 0;
	//column
	for(int i=0;i<9;i++) obj.willCome[shudoku[i][obj.columnAddress]] = 0;
	//3x3
	if(obj.rowAddress<3) a=0; else if(obj.rowAddress<6) a=3; else if(obj.rowAddress<9) a=6;
	if(obj.columnAddress<3) b=0; else if(obj.columnAddress<6) b=3; else if(obj.columnAddress<9) b=6;
	short x=a+3,y=b+3;
	for(;a<x;a++)
		for(;b<y;b++)
			obj.willCome[shudoku[a][b]] = 0;
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

short countBlankObjects(Blank* obj){
	short count=0;
	short blank = countBlank();
	for(int i=0;i<blank;i++){
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

	// displaySudoku();

	//calling initiialFill function for each objcet
	for(short i=0;i<9;i++){
		for(short j=0;j<9;j++){
			Blank::count[shudoku[i][j] - 1]++;
			if(shudoku[i][j]==0){
				obj[k].rowAddress=i;
				obj[k].columnAddress=j;
				obj[k].objectNumber = k;
				initialFill(obj[k]);
				k++;
			}
		}
	}

	// short loop = 3;
	// while(loop-- && blank){
	// 	blank = countBlankObjects(obj,blank);
	// 	int
	// }
	{
		// Blank::printCount();
		// for(int i=0;i<blank;i++){
		// 	obj[i].display();
		// }
		displaySudoku();
		short loop = 1;
		while(blank && loop--){
			for(int i=0;i<blank;i++){
				if(!obj[i].isFilled){
					initialFill(obj[i]);
					obj[i].display();
				}
			}
			displaySudoku();
			cout<<"Blanks:"<<blank<<endl;
		}

		return 0;
	}
}
