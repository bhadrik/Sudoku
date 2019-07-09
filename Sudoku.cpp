#include<iostream>
using namespace std;
class What_to_fill;
void read();
void display();
int count_blank();
void fill(What_to_fill,short);
short int arr[9][9]={1,0,0,0,5,6,0,0,0, //1
					 0,0,9,0,0,0,4,0,0, //2
					 0,0,0,7,0,9,0,0,0, //3
					 3,0,2,0,0,0,9,0,0, //4
					 0,7,0,0,1,0,0,0,5, //5
					 6,0,0,0,0,0,0,1,0, //6
					 2,0,0,5,0,0,8,0,0, //7
					 0,9,7,0,3,0,0,0,0, //8
					 0,6,4,0,0,0,0,0,1 }; //9

class What_to_fill{
public:
	short add_i,add_j;
	short arr[9];
};

int main(){
	short	blank;
	//read();
	display();
	blank = count_blank();

	What_to_fill obj[blank];

	short k=0,l=0,a=0,b=0;

	for(short i=0;i<9;i++){
		for(short j=0;j<9;j++){
			if(arr[i][j]==0){
				obj[k].add_i=i;
				obj[k].add_j=j;
				fill(obj[k],k);
				k++;
			}
		}
	}

	cin.get();
	return 0;
}

void fill(What_to_fill obj,short k){
	short a=0,b=0,l=0;

	for(a=0;a<9;a++){
		if(arr[obj.add_i][a]!=0){ obj.arr[l] = arr[obj.add_i][a]; l++; }
	}

	for(a=0;a<9;a++){
		if(arr[a][obj.add_j]!=0){ obj.arr[l] = arr[a][obj.add_j]; l++; }
	}

	if(obj.add_i<3) a=0; if(obj.add_i<6) a=3; if(obj.add_i<9) a=6;
	if(obj.add_j<3) b=0; if(obj.add_j<6) b=3; if(obj.add_j<9) b=6;

	short x=a+3,y=b+3;

	for(a;a<x;a++){
		for(b;b<y;b++){
			if(arr[a][b]!=0){ obj.arr[l] = arr[a][b]; l++; }
		}
	}

	cout<<"\nOBJ "<<k<<" detail\n";
	cout<<"add_i:"<<obj.add_i<<endl;
	cout<<"add_j:"<<obj.add_j<<endl;
	cout<<"1 2 3 4 5 6 7 8 9"<<endl;
	for(int a=0;a<9;a++)	cout<<obj.arr[a]<<" ";
	cout<<"\n";

}

void read(){
	char ch='A';
	cout<<"  1 2 3 4 5 6 7 8 9\n"
			<<"--------------------\n";
	for(int i=0;i<9;i++){
		cout<<ch++<<'|';
		for(int j=0;j<9;j++){
			cin>>arr[i][j];
		}
		cout<<endl;
	}
}

int count_blank(){
	int count=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(arr[i][j]!=0) count++;
		}
	}
	cout<<"Filed: "<<count<<endl;
	cout<<"Blank: "<<81-count<<endl;
	return (81-count);
}

void display(){
	char ch='A';
	cout<<"    1 2 3 | 4 5 6 | 7 8 9\n"
			<<"-------------------------\n";
	for(int i=0;i<9;i++){
			cout<<ch++;
		for(int j=0;j<9;j++){
			if(j==0) cout<<' ';
			if(j%3==0) cout<<"| ";
			if(arr[i][j]==0) cout<<' '/*Print instade of 0*/<<' ';
			else cout<<arr[i][j]<<' ';
		}
		cout<<endl;
		if(ch=='D' || ch=='G') cout<<"--|-------|-------|------\n";
	}
	cout<<"-------------------------\n";
}
