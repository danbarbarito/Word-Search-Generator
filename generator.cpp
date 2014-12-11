#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cctype>
using namespace std;

//Enum containing all the different direction the words can face
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
	char GenerateRandomChar(); //returns a random character
	bool CanInsert(char* word, point start, direction d); //Checks if the given word can be inserted at the start position facing direction d
	void InsertWord(char* word); //Place word at a random, valid location facing a random direction
	void ClearGrid(); //Sets the grid to be all null values
	void FillGrid(); //Fills null values with random characters
	void PrintGrid(); //Prints the grid to stdout
	point ShiftPoint(point start, direction d); //Returns the shifted point
};

Generator::Generator(){
	NULL_CHAR = 'x'; //Sets the null char to a lowercase x
}

char Generator::GenerateRandomChar(){
	return 'A' + rand()%26; //leet way to generate a random character
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
	while(i < (int)strlen(word)) //Iterates through the word char array
	{
		//Attempt to shift the point
		try{
			if(grid[newPoint.i][newPoint.k] == NULL_CHAR){
				newPoint = ShiftPoint(newPoint,d);
				i++;
			}
			else{
				return false;
			}
		}
		catch(const char* msg) //Returns false if the out of bounds error occurs
		{
			/*cout << "Cannot insert one of the words.  Please try again or choose a new word." << endl;
			exit(1);*/
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
				printf("%c \n",grid[i][k]); //Append a newline if it is on the last column
			}
			else{
				printf("%c ",grid[i][k]);
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
			newPoint.i = i-1; //Move up a row
			newPoint.k = k;   //Column stays the same
			break;
		case DOWN:
			newPoint.i = i+1;  //Move down a row
			newPoint.k = k;    //Column stays the same
			break;
		case LEFT:
			newPoint.i = i; //Row stays the same
			newPoint.k = k-1; //Column moves left
			break;
		case RIGHT:
			newPoint.i = i; //Row stays the same
			newPoint.k = k+1; //Column moves right
			break;
		case UP_LEFT:
			newPoint.i = i-1; //Row moves up
			newPoint.k = k-1; //Column moves left
			break;
		case UP_RIGHT:
			newPoint.i = i-1; //Row moves up
			newPoint.k = k+1; //Column moves right
			break;
		case DOWN_LEFT:
			newPoint.i = i+1; //Row moves down
			newPoint.k = k-1; //Column moves to left
			break;
		case DOWN_RIGHT:
			newPoint.i = i+1; //Row moves down
			newPoint.k = k+1; //Column moves right
			break;
		default:
			newPoint.i = i; //Row stays the same
			newPoint.k = k; //Column stays the same
			break;
	}
	//Handle out of bounds errors
	if(newPoint.i < -1 || newPoint.i > 10 || newPoint.k < -1 || newPoint.k > 10)
	{
		throw "Out of Bounds";
	}
	return newPoint;
}


void Generator::InsertWord(char* word){
	point start;
	direction d;
	do{
		start.i = rand() % 10; //set to a random row
		start.k = rand() % 10; //set to a random column
		d = direction(rand() % 8); //get a random direction
	}
	while(!CanInsert(word,start,d));
	int i = 0;
	point newPoint = start;
	while(i < (int)strlen(word))
	{
		grid[newPoint.i][newPoint.k] = (char)toupper(word[i]);
		newPoint = ShiftPoint(newPoint,d);
		i++;
	}
} 


int main(){
	/* initialize random seed: */
	srand (time(NULL));
	Generator gen;
	gen.ClearGrid();
	char* word = "qqqqqqq";
	gen.InsertWord(word);
	word = "ppppppppp";
	gen.InsertWord(word);
	word = "wwwwwwww";
	gen.InsertWord(word);
	word = "zzzzz";
	gen.InsertWord(word);
	gen.FillGrid();
	gen.PrintGrid();
	return 0;
}
