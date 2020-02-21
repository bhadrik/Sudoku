#include "BlankSpace.h"
#define MAXLOOP 10

class Sudoku{
public:
	Sudoku(short su[9][9]){
		copy(&su[0][0],&su[0][0]+81,&sudoku[0][0]);
		blank = countEmptyFields();
	}
	
	// calling initiialFill function for each blank spaces
	// to initalize it's object
	void solve(){
		short k=0;
		//Setup all objects
		for(short i=0;i<9;i++){
			for(short j=0;j<9;j++){
				BlankSpace::increaseCount(sudoku[i][j] - 1);
				if(sudoku[i][j]==0){
					obj[k].set(0,1,i);	//rowAddress
					obj[k].set(0,2,j);	//columnAddress
					obj[k].set(0,3,k);	//objectNumber
					k++;
				}
			}
		}
		
		short avail = blank;
		short count = 0;
		
		//Call the processObj untill all the 
		//blanks are filled and variable "avail become 0
		while(avail && count<MAXLOOP){
			for(short i=0;i<blank;i++){
				if(!obj[i].isFilled()){
					processObj(obj[i], sudoku);
				}
			}
			avail = countBlankObjects();
			count++;
		}
		if(count >= MAXLOOP)
			cout<<"+--------------------------------------------------------------------------+\n"
			    <<"|CAN'T SOLVE!                                                              |\n"
			    <<"|Increasing MAXLOOP little may halp, if not your sudoku is hard to solve :)|\n"
			    <<"+--------------------------------------------------------------------------+\n";
	}
	
	short blanks(){
		return blank;
	}
	
	void input(){
		char ch='A';
		cout<<"  1 2 3 4 5 6 7 8 9\n"
				<<"--------------------\n";
		for(short i=0;i<9;i++){
			cout<<ch++<<'|';
			for(short j=0;j<9;j++){
				cin>>sudoku[i][j];
			}
		}
		cout<<endl;
	}
	
	void display(){
		cout<<"    1 2 3 | 4 5 6 | 7 8 9\n"
				<<"  +-------+-------+-------+\n";
		for(short i=0;i<9;i++){
				cout<<i+1;
			for(short j=0;j<9;j++){
				if(j==0) cout<<' ';
				if(j%3==0) cout<<"| ";
				if(sudoku[i][j]==0) cout<<' '/*Print instead of 0*/<<' ';
				else cout<<sudoku[i][j]<<' ';
			}
			cout<<"|"<<endl;
			if(i==2 || i==5) cout<<"  +-------+-------+-------+\n";
		}
		cout<<"  +-------+-------+-------+\n";
	}
	
	void displayObj(short index){
		obj[index].display();
	}
	
	void printCount(){
		BlankSpace::printCount();
	}
	
private:
	short sudoku[9][9];
	short blank;
	short count[9] = {0,0,0,0,0,0,0,0,0};
	BlankSpace* obj = new BlankSpace[blank];
	
	//fill function fills the mask field of sudoku
	void processObj(BlankSpace &obj, short sudoku[9][9]){
		short a=0,b=0;
		bool possible=true;
		//row
		for(short i=0;i<9;i++) obj.set(1,sudoku[obj.get(0,1)][i],0);
		//column
		for(short i=0;i<9;i++) obj.set(1,sudoku[i][obj.get(0,2)],0);
		//3x3
		if(obj.get(0,1)<3) a=0; else if(obj.get(0,1)<6) a=3; else if(obj.get(0,1)<9) a=6;
		if(obj.get(0,2)<3) b=0; else if(obj.get(0,2)<6) b=3; else if(obj.get(0,2)<9) b=6;
		short x=a+3,y=b+3;
		
		for(short i=a;i<x;i++)
		for(short j=b;j<y;j++)
		obj.set(1,sudoku[i][j],0);
		
		deepSearch();
		
		obj.process(sudoku);
	}
	
	void deepSearch(){
		//Function for deep search
	}
	
	short countBlankObjects(){
		short count=0;
		for(short i=0;i<blank;i++){
			if(!obj[i].isFilled()) count++;
		}
		return count;
	}
	
	short countEmptyFields(){
		short count=0;
		for(short i=0;i<9;i++){
			for(short j=0;j<9;j++){
				if(sudoku[i][j]!=0) count++;
			}
		}
		return (81-count);
	}
};
