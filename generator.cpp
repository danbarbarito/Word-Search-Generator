#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cctype>
#include <fstream>


using namespace std;


const int GRID_SIZE = 10;

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
	char grid[GRID_SIZE][GRID_SIZE]; //Create a nxn grid
	char NULL_CHAR; //The character that represents a null value
	string words[7];
	public:
	Generator();
	char GenerateRandomChar(); //returns a random character
	bool CanInsert(const char* word, point start, direction d); //Checks if the given word can be inserted at the start position facing direction d
	void InsertWord(const char* word); //Place word at a random, valid location facing a random direction
	void ClearGrid(); //Sets the grid to be all null values
	void FillGrid(); //Fills null values with random characters
	void PrintGrid(); //Prints the grid to stdout
	point ShiftPoint(point start, direction d); //Returns the shifted point
	void ReadFile(char* filename);
	void InsertWordsFromFile();
	void PuzzleToFile(char* filename);
};

Generator::Generator(){
	NULL_CHAR = 'x'; //Sets the null char to a lowercase x
}

char Generator::GenerateRandomChar(){
	return 'A' + rand()%26; //leet way to generate a random character
}

//Sets all values in grid to a null character
void Generator::ClearGrid(){
	for(int i=0;i<GRID_SIZE;i++){
		for(int k=0;k<GRID_SIZE;k++){
			grid[i][k] = NULL_CHAR; //Every empty value will be a lowercase x
		}
	}
}

//Checks if word can be inserted in the grid at the given start point
bool Generator::CanInsert(const char* word, point start, direction d){
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
	for(int i=0;i<GRID_SIZE;i++){
		for(int k=0;k<GRID_SIZE;k++){
			if(grid[i][k] == NULL_CHAR){
				grid[i][k] = GenerateRandomChar(); //Set every null value to a random character
			}
		}
	}
}

//Prints the grid to stdout
void Generator::PrintGrid(){
	printf("Generated Puzzle:\n");
	for(int i=0;i<GRID_SIZE;i++){
		for(int k=0;k<GRID_SIZE;k++){
			if(k == 0){
				printf("\t%c ",grid[i][k]); //Puts a tab at the first column to make it look pretty
			}
			else if(k == GRID_SIZE-1){
				printf("%c\n",grid[i][k]); //Append a newline if it is on the last column
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
	if(newPoint.i < -1 || newPoint.i > GRID_SIZE || newPoint.k < -1 || newPoint.k > GRID_SIZE)
	{
		throw "Out of Bounds";
	}
	return newPoint;
}


void Generator::InsertWord(const char* word){
	point start;
	direction d;
	do{
		start.i = rand() % GRID_SIZE; //set to a random row
		start.k = rand() % GRID_SIZE; //set to a random column
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

void Generator::ReadFile(char* filename){
	ifstream wordsFile(filename);
	string word;
	int line = 0;
	if(wordsFile.is_open()){
		printf("Reading file '%s'\n",filename);
		while(getline(wordsFile,word)){
			words[line] = word;
			line++;
			if(line == 8){
				throw "Words list can not have more than 7 words";
			}
			if(word.length() < 2 || word.length() > GRID_SIZE-1){
				throw "Words must be at least two characters and no more than the grid size";
			}
		}
	}
	else{
		throw "Cannot open words list file";
	}
}

void Generator::InsertWordsFromFile(){
	//Iterate through all of the indexes in the array and insert them into the grid
	for(int i=0;i<(int)(sizeof(words)/sizeof(words[0]));i++){
		string word = words[i];
		InsertWord(word.c_str()); //Convert the word (std::string) into a useable char* array
	}
}

void Generator::PuzzleToFile(char* filename){
	ofstream output(filename);
	char c;
	if(output.is_open()){
		printf("Writing to file '%s'\n",filename);
		for(int i=0;i<GRID_SIZE;i++){
			for(int k=0;k<GRID_SIZE;k++){
				if(k == GRID_SIZE-1){
					c = grid[i][k];
					output.put(c);
					output.put('\n');	//Append a newline if it is on the last column
				}
				else{
					c = grid[i][k];
					output.put(c);
				}
		}}
	}
	else{
		throw "Cannot create output file";
	}
}

int main(int argc, char* argv[]){
	/* initialize random seed: */
	srand (time(NULL));
	char* words_list;
	char* output_file;
	switch(argc){
		case 1:
			words_list = "words_list";
			output_file = "output";
			break;
		case 2:
			if(strcmp(argv[1],"--help") == 0){
				printf("Usage: ./generator <words list> <output file>\n");
				exit(1);
			}
			else{
			words_list = argv[1];
			output_file = "output";
			}
			break;
		case 3:
			words_list = argv[1];
			output_file = argv[2];
			break;
		default:
			printf("Usage: ./generator <words list> <output file>\n");
			exit(1);
	}
	Generator gen;
	try{
		gen.ReadFile(words_list);
	}
	catch(const char* msg){
		cout << msg << endl;
		exit(1);
	}
	gen.ClearGrid();
	gen.InsertWordsFromFile();
	gen.FillGrid();
	gen.PrintGrid();
	try{
		gen.PuzzleToFile(output_file);
	}
	catch(const char* msg){
		cout << msg << endl;
		exit(1);
	}
	return 0;
}
