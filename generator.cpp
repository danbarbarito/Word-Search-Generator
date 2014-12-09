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

class Generator{
	char grid[10][10]; //Create a 10x10 grid
	public:
		Generator();
		char GenerateRandomChar();
		bool CanInsert(const char word[], direction x);
		void ClearGrid();
		void FillGrid();
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
			grid[i][k] = 0; //Set every empty value to a random character
		}
	}
}

//Checks if word can be inserted in the grid
bool Generator::CanInsert(const char word[], direction x){
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



int main(){
	/* initialize random seed: */
	srand (time(NULL));
	Generator gen;
	gen.ClearGrid();
	cout << gen.CanInsert("test",UP) << endl;
	return 0;
}
