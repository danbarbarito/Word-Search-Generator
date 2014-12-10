#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cctype>
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

struct point{int i,k;}; //Declare a point structure that represents a point on the grid

class Generator{
	char grid[10][10]; //Create a 10x10 grid
	char NULL_CHAR; //The character that represents a null value
	public:
	Generator();
	char GenerateRandomChar();
	bool CanInsert(char* word, point start, direction d);
	void InsertWord(char* word, point start, direction d);
	void ClearGrid();
	void FillGrid();
	void PrintGrid();
	point ShiftPoint(point start, direction d);
};

Generator::Generator(){
	NULL_CHAR = 'x'; //Sets the null char to a lowercase x
}

char Generator::GenerateRandomChar(){
	return 'A' + rand()%26;
}

//Sets all values in grid to a null character
void Generator::ClearGrid(){
	for(int i=0;i<10;i++){
		for(int k=0;k<10;k++){
			grid[i][k] = NULL_CHAR; //Every empty value will be a lowercase x
		}
	}
}

//Checks if word can be inserted in the grid at the given start point
bool Generator::CanInsert(char* word, point start, direction d){
	int i = 0;
	point newPoint = start;
	printf("Length of the word %s: %d\n",word,(int)strlen(word));
	while(i < (int)strlen(word))
	{
		//Attempt to shift the point
		try{
			newPoint = ShiftPoint(newPoint,d);
			i++;
		}
		catch(const char* msg) //Returns false if the out of bounds error occurs
		{
			return false;
		}
	}
	return true;
}

//Replaces empty tiles with a random character
void Generator::FillGrid(){
	for(int i=0;i<10;i++){
		for(int k=0;k<10;k++){
			if(grid[i][k] == NULL_CHAR){
				grid[i][k] = GenerateRandomChar(); //Set every null value to a random character
			}
		}
	}
}

//Prints the grid to stdout
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

//Shifts the point depending on the direction
point Generator::ShiftPoint(point start, direction d){
	int i = start.i;
	int k = start.k;
	point newPoint;
	switch(d){
		case UP:
			newPoint.i = i-1;
			newPoint.k = k;
			break;
		case DOWN:
			newPoint.i = i+1;
			newPoint.k = k;
			break;
		case LEFT:
			newPoint.i = i;
			newPoint.k = k-1;
			break;
		case RIGHT:
			newPoint.i = i;
			newPoint.k = k+1;
			break;
		case UP_LEFT:
			newPoint.i = i-1;
			newPoint.k = k-1;
			break;
		case UP_RIGHT:
			newPoint.i = i-1;
			newPoint.k = k+1;
			break;
		case DOWN_LEFT:
			newPoint.i = i+1;
			newPoint.k = k-1;
			break;
		case DOWN_RIGHT:
			newPoint.i = i+1;
			newPoint.k = k+1;
			break;
		default:
			newPoint.i = i;
			newPoint.k = k;
			break;
	}
	//Handle out of bounds errors
	if(newPoint.i < 0 || newPoint.i > 9 || newPoint.k < 0 || newPoint.k > 9)
	{
		throw "Out of Bounds";
	}
	return newPoint;
}


void Generator::InsertWord(char* word, point start, direction d){
	if(CanInsert(word,start,d)){
		int i = 0;
		point newPoint = start;
		while(i < (int)strlen(word))
		{
			newPoint = ShiftPoint(newPoint,d);
			grid[newPoint.i][newPoint.k] = (char)toupper(word[i]);
			i++;
		}
	}
} 


int main(){
	/* initialize random seed: */
	srand (time(NULL));
	Generator gen;
	gen.ClearGrid();
	point startPoint;
	startPoint.i = 5;
	startPoint.k = 5;
	char* word = "Test";
	gen.InsertWord(word,startPoint,DOWN_RIGHT);
	gen.FillGrid();
	gen.PrintGrid();
	return 0;
}
