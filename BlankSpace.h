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
		status = false;
	}
	
	void display(){
		cout<<"\nOBJ "<<objectNumber<<" status: "<<status<<endl;
		cout<<"("<<rowAddress+1<<","<<columnAddress+1<<")"<<" pNum:"<<possibleNumbers<<" bit:"<<mask[0]<<endl;
		cout<<"1 2 3 4 5 6 7 8 9"<<endl;
		for(short a=1;a<10;a++)	cout<<mask[a]<<" ";
		cout<<"\n";
	}

	void initialProcess(short sudoku[9][9]){
		countPossibleNumbers();
		if(possibleNumbers==1){
			mask[0]=1;
			apply(sudoku);
		}
		else applicableNumber = 0;
	}
	
	short get(bool key, short index){
		if(!key)
		switch(index){
			case 1: return rowAddress;  				//(0,1)
			case 2: return columnAddress; 			//(0,2)
			case 3: return objectNumber;				//(0,3)
			case 4: return possibleNumbers;			//(0,4)
			case 5: return applicableNumber;		//(0,5)
		}
		else return ((short)mask[index]);			//get(1,1-9)
		return 0;
	}
	
	void set(bool key,short index, short data){
		if(!key)
		switch(index){
			case 1: rowAddress = data;
			case 2: columnAddress = data;
			case 3: objectNumber = data;
			case 4: possibleNumbers = data;
			case 5: applicableNumber = data;
		}
		else mask[index] = data;
	}
	
	bool isFilled(){
		return status;
	}
	
	void forceApply(short sudoku[9][9], short forceApplicableNumber){
		cout<<"ForceApply:";
		applicableNumber = forceApplicableNumber;
        	apply(sudoku);
	}

private:
	bool status;
	short objectNumber,possibleNumbers,applicableNumber,
	rowAddress,columnAddress;
	bool mask[10] = {0,1,1,1,1,1,1,1,1,1};
	
	void countPossibleNumbers(){
		possibleNumbers = 0;
		for(short i=1;i<10;i++){
			if(mask[i]){
				possibleNumbers++;
				applicableNumber = i;
			}
			if(possibleNumbers!=1)
				applicableNumber = 0;
		}
	}
	
	void apply(short sudoku[9][9]){
		sudoku[rowAddress][columnAddress] = applicableNumber;
		status = true;
	}
};
