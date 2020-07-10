#include "BlankSpace.h"
#define MAXLOOP 10

class Sudoku{
public:
	Sudoku(short su[9][9]){
		copy(&su[0][0],&su[0][0]+81,&sudoku[0][0]);
	}

	// calling initiialFill function for each blank spaces
	// to initalize it's object
	void solve(){
		short k=0;
		//Setup all objects
		for(short i=0;i<9;i++){
			for(short j=0;j<9;j++){
				if(sudoku[i][j]==0){
					obj[k].set(0,1,i);	//rowAddress
					obj[k].set(0,2,j);	//columnAddress
					obj[k].set(0,3,k);	//objectNumber
					k++;
				}
			}
		}

		short avail = blank;
		short loop = 0;

		//Call the processObj untill all the
		//blanks are filled and variable "avail become 0
		while(avail && loop<MAXLOOP){
			for(short i=0;i<blank;i++){
				if(!obj[i].isFilled()){
					processObj(obj[i], sudoku);
				}
			}
			avail = countBlankObjects();
			loop++;
		}
		if(loop >= MAXLOOP || avail){\
            cout<<"+-----------------------------------------+\n"
			    <<"| CAN'T SOLVE!                            |\n"
			    <<"| Increaing MAXLOOP little may halp.      |\n"
			    <<"| If not, your sudoku is hard to solve :) |\n"
			    <<"+-----------------------------------------+\n";
            cout<<"Avail: "<<avail<<endl;
		}
	}

	void input(){
		bool input = false;

		cout<<"+-----------------+ +--------------------+\n"
				<<"| 1->INPUT SUDOKU | | 0->GO WITH DEFAULT |\n"
				<<"+-----------------+ +--------------------+\n";
		cin>>input;
		if(!input){
		    blank = countEmptyFields();
            obj = new BlankSpace[blank];
		    return;
		}
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
		blank = countEmptyFields();
		obj = new BlankSpace[blank];
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

	//display object by providing its index
	void displayObj(short index){
		obj[index].display();
	}

	//display object by providing its location in sudoku
	void displayObj(short x, short y){
		x--; y--;
		for(short i=0;i<blank;i++)
			if(x==obj[i].get(0,1) && y==obj[i].get(0,2)){
				obj[i].display();
				break;
			}
	}

private:
	short sudoku[9][9];
	short blank = countEmptyFields();
	short list[9] = {0,0,0,0,0,0,0,0,0};
	BlankSpace* obj;

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

		obj.initialProcess(sudoku);
	}

	void deepSearch(){
		//Function for deep search
	}

	short countBlankObjects(){
		short tmp=0;
		for(short i=0;i<blank;i++){
			if(!obj[i].isFilled()) tmp++;
		}
		return tmp;
	}

	short countEmptyFields(){
		short tmp=0;
		for(short i=0;i<9;i++){
			for(short j=0;j<9;j++){
				if(sudoku[i][j]==0) tmp++;
			}
		}
		return tmp;
	}

	short maxOfList(){
		short max=0,index=-1;
		for(short i=0;i<9;i++)
			if(list[i]>max){
				max = list[i];
				index = i;
			}
			list[index] = 0;
		return max;
	}

	void reList(){
		for(short i=0;i<9;i++)	list[i] = 0;
		for(short i=0;i<9;i++)
		for(short j=0;j<9;j++)
			if(sudoku[i][j]==0)
			list[sudoku[i][j]-1] += 1;
	}
};
