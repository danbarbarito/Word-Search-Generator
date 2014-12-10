#include <iostream>
#include <cstdio>
#include <stdlib.h>
using namespace std;

enum direction{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

typedef int point[2]; //Declare a point type that represents a point on the grid

class Generator{
	char grid[10][10]; //Create a 10x10 grid
	const char NULL_CHAR = 'x'; //The null character will be a lowercase x
	public:
		Generator();
		char GenerateRandomChar();
		bool CanInsert(const char word[], point start, direction x);
		void ClearGrid();
		void FillGrid();
		void PrintGrid();
};

Generator::Generator(){
}

char Generator::GenerateRandomChar(){
	return 'A' + rand()%26;
}

//Sets all values in grid to 0
void Generator::ClearGrid(){
	for(int i=0;i<10;i++){
		for(int k=0;k<10;k++){
			grid[i][k] = NULL_CHAR; //Every empty value will be a lowercase x
		}
	}
}

//Checks if word can be inserted in the grid at the given start point
bool Generator::CanInsert(const char word[], point start, direction x){
	return true;
}

//Replaces empty tiles with a random character
void Generator::FillGrid(){
	for(int i=0;i<10;i++){
		for(int k=0;k<10;k++){
			if(grid[i][k] == 0){
				grid[i][k] = GenerateRandomChar(); //Set every null value to a random character
			}
		}
	}
}

//Replaces empty tiles with a random character
void Generator::PrintGrid(){
	for(int i=0;i<10;i++){
		for(int k=0;k<10;k++){
			if(k == 9){
				printf("%c\n",grid[i][k]); //Append a newline if it is on the last column
			}
			else{
				printf("%c",grid[i][k]);
			}
		}
	}
}



int main(){
	/* initialize random seed: */
	srand (time(NULL));
	Generator gen;
	gen.ClearGrid();
	gen.PrintGrid();
	//int startPos[2] = {1,2};
	return 0;
}
