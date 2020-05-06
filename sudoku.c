#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


void print_board(int bo[9][9]){
	int i = 0, j;
	for(i = 0; i < 9; i++){
		if (i % 3 == 0 && i != 0)
			printf("- - - - - - - - - - - - - \n");
		for(j = 0; j < 9; j++){
			if (j % 3 == 0 && j != 0)
				printf(" | ");
			if (j == 8)
				printf("%d\n", bo[i][j]);
			else
				printf("%d ", bo[i][j]);
		}
	}
	printf("\n");
}
//returns the empty row and column
int * find_empty(int bo[9][9]){  
	int i, j;
	int* pair = (int *)malloc(2*sizeof(int));
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(bo[i][j] == 0){
				//first index is row, second index is column
				pair[0] = i;
				pair[1] = j;
				return pair;
			}
		}
	}
	return NULL;
}

//returns the corner of the box that a row, column pair belongs to
int * get_box_corner(int row,int column){
	int * corner = (int *)malloc(2* sizeof(int));
	int ret_column, ret_row;
	if(column >= 0 && column < 3)
		ret_column = 0;
	else if(column >=3 && column < 6)
		ret_column = 3;
	else
		ret_column = 6;
	if(row >= 0 && row < 3)
		ret_row = 0;
	else if(row >= 3 && row < 6)
		ret_row = 3;
	else
		ret_row = 6;
	corner[0] = ret_row;
	corner[1] = ret_column;
	return corner;
}
//returns the index of the value
bool present(int *l, int size, int val){
	int i;
	for(i = 0; i < size; i++){
		if(l[i] == val)
			return true;
	}
	return false;
}
void arr_remove(int *l, int size, int val){
	int i;
	for(i = 0; i < size; i++){
		if(l[i] == val)
			break;
	}
	for(;i < size-1;i++){
		l[i] = l[i+1];
	}
	for(; i < 9; i++)
		l[i] = -1;
}


//this function uses the row and column given by the find_empty function
//this function then returns the list of valid numbers for empty places in the sudoku
int * find_valid_numbers(int row,int column,int bo[9][9]){
	int * l = (int *)malloc(9*sizeof(int));
	int i = 0, j, size = 9;
	int *box_corner;
	while(i < 9){
		l[i] = i+1;
		i++;
	}
	//get the list of valid numbers in the row by removing numbers that are present in row 
	for(i = 0; i < 9; i++){
		if(bo[row][i] != 0){
			arr_remove(l, size, bo[row][i]);
			size--;
		}
	}
	//remove the numbers from the list l that are present in the column
	for(i = 0; i < 9; i++){
		if(bo[i][column] != 0){
			if(present(l, size, bo[i][column]) == true){
				arr_remove(l, size, bo[i][column]);
				size--;
			}
		}
	}
	//remove numbers that are in the box from list l
	box_corner = get_box_corner(row, column);
	for(i = box_corner[0]; i< box_corner[0]+3; i++){
		for(j = box_corner[1]; j< box_corner[1]+3; j++){
			if(bo[i][j] != 0){
				if( present(l, size, bo[i][j]) == true){
					arr_remove(l, size, bo[i][j]);
					size--;
				}
			}
		}
	}
//	for(i=0; i< 9; i++)
//		printf("%d  ", l[i]);
//	printf("\n");
//	l[size] = -1;
	return l;
}
int get_size(int *list){
	int i=0;
	while(i < 9){
		if(list[i] == -1)
			break;
		else
			i++;
	}
	return i;
}
//solveee
bool solve(int bo[9][9]){
	int * find;
	int *valid;
	int row, col, i, j, size;
	find = find_empty(bo);
	if(find ==  NULL)
		return true;
	else{
		row = find[0];
		col = find[1];
	}
	valid = find_valid_numbers(row, col, bo);
	size = get_size(valid);
	for(i = 1; i <= 9; i++){
		if(present(valid, size, i) == true){
			bo[row][col] = i;
			if(solve(bo) == true)
				return true;
			else
				bo[row][col] = 0;
		}
	}
	//print_board(bo);
	return false;
}

int main(){
	int bo[9][9] = {
		{7,8,0,4,0,0,1,2,0},
		{6,0,0,0,7,5,0,0,9},
		{0,0,0,6,0,1,0,7,8},
		{0,0,7,0,4,0,2,6,0},
		{0,0,1,0,5,0,9,3,0},
		{9,0,4,0,6,0,0,0,5},
		{0,7,0,3,0,0,0,1,2},
		{1,2,0,0,0,7,4,0,0},
		{0,4,9,2,0,6,0,0,7}
		};

	print_board(bo);
	bool answer = solve(bo);
	print_board(bo);
	return 0;
}
