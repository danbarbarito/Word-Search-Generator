#include <iostream>
#include <cstdio>
using namespace std;

class Generator{
	public:
		Generator();
		void createGrid();
};

Generator::Generator(){
}

void Generator::createGrid(){
	int grid[10][10]; //Create a 10x10 grid
	for(int i=0;i<10;i++){
		for(int k=0;k<10;k++){
			if(k == 9){//if its the at the last column append a newline
				printf("x \n");
			}
			else{
				printf("x ");
			}
		}
	}
}

int main(){
	Generator gen;
	gen.createGrid();
	return 0;
}
