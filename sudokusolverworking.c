#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define N 9

/*Loop through each cell in the grid using a for loop inside a for loop
for each cell that is empty make a call to solveSudoku() which loops through numbers
1-9 and checks if each one fits using isValid() if not it will move on to the next cell
if none of the cells can be solved it ends

*/



//Find Empty spaces
void findEmpty(int *coordinates, int grid[][9]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (grid[i][j] == 0)
			{
				coordinates[0] = i;
				coordinates[1] = j;
				return;
			}
		}
	}
	coordinates[0] = -1;
	coordinates[1] = -1;
	return; //grid is full
}

//Check row doesn't have duplicate		
bool inRow(int row, int num, int grid[][9]) {
	for (int i = 0; i < N; i++) {
		if (grid[row][i] == num) {
			return true;
		}
	}
	return false;
}
//Check column doesn't have duplicate
bool inCol(int col, int num, int grid[][9]) {
	for (int i = 0; i < N; i++) {
		if (grid[i][col] == num) {
			return true;
		}
	}
	return false;
}
//Check box doesn't have duplicate
bool inBox(int beginRow, int beginCol, int num, int grid[][9]) {
	for (int i = 0; i < N / 3; i++) {
		for (int j = 0; j < N / 3; j++) {
			if (grid[i + beginRow][j + beginCol] == num) {
				return true;
			}
		}
	}
	return false;
}

bool isValid(int row, int col, int num, int grid[][9]) {
	//check that row contains num OR column contains num OR 
	//block in which cell is contained contains num
	if (!inRow(row, num, grid) && !inCol(col, num, grid) && !inBox(row - row % 3, col - col % 3, num, grid)) {
		return true;
	}
	return false;

}

//int * has list of memory locations, one for each number, the [9] means that every 9 items is a "row" in the array
bool solveSudoku(int *coordinates, int grid[][9]) {


	for (int i = 1; i <= N; i++) {//for numbers 1-9
		findEmpty(coordinates, grid);//allocate mem

		int row = coordinates[0];//allocate row. this is the first instance it's being allocated incorrectly
		int col = coordinates[1];//allocate col


		if (col == -1) {
			//indicating we've filled the whole grid
			return true;
		}

		if (isValid(row, col, i, grid)) {//check the number isValid. First call to this funtion
			grid[row][col] = i;//allocate that number to the cell if it isValid



			if (solveSudoku(coordinates, grid)) {//if grid is solved return true
				return true;
			}
			
			//selection of number didn't work, reverse changes
			grid[row][col] = 0;


		}
	}

	return false; //this will cause the backtracking
}



///MAIN METHOD
void main() {

	int coordinates[2] = { -1, -1 };

	int grid[N][N] = {
		{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
		{ 6, 0, 0, 1, 9, 5, 0, 0, 0 }, 
		{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
		{ 8, 0, 0, 0, 6, 0, 0, 0, 3 }, 
		{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
		{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
		{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
		{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
		{ 0, 0, 0, 0, 8, 0, 0, 7, 9 } };

	if (solveSudoku(coordinates, grid)) {
		printf("Solved");
		printf("\n");
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d", grid[i][j]);
			}
			printf("\n");
		}
	}
	else {
		printf("Not Solved");
	}

}
///MAIN METHOD