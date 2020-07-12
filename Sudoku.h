#include "BlankSpace.h"
#define MAXLOOP 20

class Sudoku{
public:
	Sudoku(short su[9][9]){
		copy(&su[0][0],&su[0][0]+81,&sudoku[0][0]);
	}

	// calling initiialFill function for each blank spaces
	// to initalize it's object
	void solve(){
		short k=1;
		//Setup all objects
		for(short i=0;i<9;i++){
			for(short j=0;j<9;j++){
                obj[i][j].set(0,3,0);
				if(sudoku[i][j]==0){
					obj[i][j].set(0,1,i);	//rowAddress
					obj[i][j].set(0,2,j);	//columnAddress
					obj[i][j].set(0,3,k);	//objectNumber
					k++;
				}
				else{
                    obj[i][j].changStatus(1);
                    obj[i][j].set(0,3,0);     // objectNumber of already filled number is 0.
				}
			}
		}

		//Call the processObj untill all the
		//blanks are filled and variable "avail become 0
		while(avail && loop<MAXLOOP){
			for(short i=0;i<9;i++)
            for(short j=0;j<9;j++){
				if(!obj[i][j].isFilled()){
					processObj(obj[i][j], sudoku);
				}
			}
			avail = countBlankObjects();
			loop++;
		}
		if(loop >= MAXLOOP || avail){\
            cout<<"+--------------------------------------------+\n"
			    <<"| CAN'T SOLVE!                               |\n"
			    <<"| Increaing MAXLOOP little may halp.         |\n"
			    <<"| If not, your sudoku is harder than hard :) |\n"
			    <<"+--------------------------------------------+\n";
            cout<<"Avail: "<<avail<<endl;
		}
		cout<<"Total loop:"<<loop<<endl;
	}

	void input(){
		bool input = false;

		cout<<"+-----------------+ +--------------------+\n"
			<<"| 1->INPUT SUDOKU | | 0->GO WITH DEFAULT |\n"
			<<"+-----------------+ +--------------------+\n";
		
		cin>>input;
		if(!input){
		    blank = countEmptyFields();
		    avail = blank;
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
		avail = blank;
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
		for(short i=0;i<9;i++)
		for(short j=0;j<9;j++)
            if(obj[i][j].get(0,3) == index)
                obj[i][j].display();
	}

	//display object by providing its location in sudoku
	void displayObj(short x, short y){
	    obj[--x][--y].display();
	}

private:
	short sudoku[9][9];
	short blank = countEmptyFields();
	short list[9] = {0,0,0,0,0,0,0,0,0};
	BlankSpace obj[9][9];
	short avail;
    short loop = 0;

	//fill function fills the mask field of sudoku
	void processObj(BlankSpace &objOne, short sudoku[9][9]){
		short a=0,b=0;
		//row
		for(short i=0;i<9;i++) objOne.set(1,sudoku[objOne.get(0,1)][i],0);
		//column
		for(short i=0;i<9;i++) objOne.set(1,sudoku[i][objOne.get(0,2)],0);
		//3x3
		if(objOne.get(0,1)<3) a=0; else if(objOne.get(0,1)<6) a=3; else if(objOne.get(0,1)<9) a=6;
		if(objOne.get(0,2)<3) b=0; else if(objOne.get(0,2)<6) b=3; else if(objOne.get(0,2)<9) b=6;
		short x=a+3,y=b+3;

		for(short i=a;i<x;i++)
		for(short j=b;j<y;j++){
            objOne.set(1,sudoku[i][j],0);
		}

		//One step ahed search
		deepSearch(objOne, sudoku, a, b);

		objOne.initialProcess(sudoku);
	}

	void deepSearch(BlankSpace &objOne, short sudoku[9][9], short a, short b){
	    short x=a+3, y=b+3;
        if(loop>0){
            for(int l=1;l<10;l++){

                if(objOne.get(1,l)==1){

                    bool possible = true;
                    for(short i=a;i<x;i++){
                    for(short j=b;j<y;j++){
                            //objectNumber != 0      Not same object
                        if(obj[i][j].get(0,3) !=0 && obj[i][j].get(0,3) != objOne.get(0,3) && !obj[i][j].isFilled()){
                            if(obj[i][j].get(1,l) !=0){ possible = false; break; }
                        }
                    }
                        if(!possible) break;
                    }
                    if(possible) objOne.forceApplly(sudoku, l);
                }
            }
        }
	}

	short countBlankObjects(){
		short tmp=0;
		for(short i=0;i<9;i++)
        for(short j=0;j<9;j++){
			if(!obj[i][j].isFilled()) tmp++;
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
