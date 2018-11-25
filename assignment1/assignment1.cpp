/*
	Alp Eren Gençoğlu | 150170019
	Data Structures Assignment 1

	This program can place mathematical operators to a grid
	and can perform moving operations to the opreators.
	All data (grid size, operator specifications and instructions)
	are read from files.
*/

#include <iostream>
#include <cstdio>

using namespace std;


struct grid_struct
{
	char type;
	int row, column, size;
};

struct instruction
{
	char direction[3];
	int row, column, move_by;
};

//Checks if there is border error while trying to place operators
bool borderError(struct grid_struct** grid, int rows, int columns, struct grid_struct info)
{
	bool error = false;
	switch(info.type)
	{
		case '+':
			if(info.row + info.size >= rows || info.row - info.size < 0)
				error = true;
		case '-':
			if(info.column + info.size >= columns || info.column - info.size < 0)
				error = true;
			break;
		case 'x':
		case '/':
			if(info.row + info.size >= rows || info.row - info.size < 0 || info.column + info.size >= columns || info.column - info.size < 0)	
				error = true;			
			break;
	}
	
	return error;
}

//Checks if there is conflict error while trying to place operators
bool conflictError(struct grid_struct** grid, int rows, int columns, struct grid_struct info)
{
	bool error = false;
	for(int j=1; j<=info.size; j++)
	{
		if(info.row-j<0 || info.row+j>=rows || info.column-j<0 || info.column+j>=columns)
			break;
		switch(info.type)
		{
			case '+':
				if( grid[info.row+j][info.column].type != '.' || 
				grid[info.row-j][info.column].type != '.' )
					error = true;			
			case '-':
				if(grid[info.row][info.column+j].type != '.' || 
				grid[info.row][info.column-j].type != '.' )
					error = true;
				break;

			case 'x':
				if(grid[info.row+j][info.column+j].type != '.' ||
				grid[info.row-j][info.column-j].type != '.' )
					error = true;
			case '/':	
				if(grid[info.row+j][info.column-j].type != '.' ||
				grid[info.row-j][info.column+j].type != '.' )
					error = true;
				break;
		}
	}
	
	return error;
}


int main(int argc, char* argv[]){
	
	int rows, columns;
	struct grid_struct info;
	struct instruction inst;
	struct grid_struct empty;
	empty.type='.'; empty.row=0; empty.column=0; empty.size=0;
	struct grid_struct old;

	bool border,conflict;

	FILE *gridptr;
	FILE *instructionsptr;
	

	//
	//
	// grid file operations
	//
	//
	gridptr = fopen(argv[1],"r");
	
	if(gridptr==NULL)
	{
		return 1;
	}
	
	fscanf(gridptr,"%d %d",&rows,&columns);
		
	//	
	// Grid creation
	//
	struct grid_struct **grid = new struct grid_struct*[columns];
	for(int i=0; i<columns; i++)
	{
		grid[i] = new struct grid_struct[rows];
	}
	cout << "A grid is created: " << rows << " " << columns << endl;

	fseek(gridptr,1,SEEK_CUR);
	
	for(int i=0; i<rows; i++)
	{	
		for(int j=0; j<columns; j++)
		{
			grid[i][j].type = '.';
		}
	}



	//
	// Placing operators into the grid
	//
	while( !feof(gridptr) )
	{

		fscanf(gridptr, " %c %d %d %d ", &info.type, &info.row, &info.column, &info.size);
		info.row--;
		info.column--;

		if( (border=borderError(grid,rows,columns,info)) )
			printf("BORDER ERROR: Operator %c with size %d can not be placed on (%d,%d).\n"
				,info.type, info.size, info.row+1, info.column+1 );
		if( (conflict=conflictError(grid,rows,columns,info)) )
			printf("CONFLICT ERROR: Operator %c with size %d can not be placed on (%d,%d).\n"
				,info.type, info.size, info.row+1, info.column+1 );
		
		if(!border && !conflict)
		{
			for(int j=0; j<=info.size; j++)
			{
				switch(info.type)
				{
					case '+':
						grid[info.row+j][info.column] = info;
						grid[info.row-j][info.column] = info;
					case '-':
						grid[info.row][info.column+j] = info;
						grid[info.row][info.column-j] = info;
						break;
					case 'x':
						grid[info.row+j][info.column+j] = info;
						grid[info.row-j][info.column-j] = info;
					case '/':	
						grid[info.row+j][info.column-j] = info;
						grid[info.row-j][info.column+j] = info;
						break;
				}
			}
			printf("SUCCESS: Operator %c with size %d is placed on (%d,%d).\n"
				,info.type, info.size, info.row+1, info.column+1 );
		
		}	
	}
	
	
	fclose(gridptr);



	//
	//	
	// instructions file operations
	//
	//
	instructionsptr = fopen(argv[2],"r");

	if(instructionsptr==NULL)
	{
		return 1;
	}
	

	while( !feof(instructionsptr) )
	{
		fscanf(instructionsptr,"%s %d %d %d ",inst.direction,&inst.row,&inst.column,&inst.move_by);
		inst.row--;
		inst.column--;
			
		old.type = grid[inst.row][inst.column].type;
		old.size = grid[inst.row][inst.column].size;
		old.row = grid[inst.row][inst.column].row;
		old.column = grid[inst.row][inst.column].column;

		info.type = grid[inst.row][inst.column].type;
		info.size = grid[inst.row][inst.column].size;
		info.row = grid[inst.row][inst.column].row;
		info.column = grid[inst.row][inst.column].column;
		switch(inst.direction[2])
		{
			case 'R': info.column+=inst.move_by; break;
			case 'L': info.column-=inst.move_by; break;
			case 'U': info.row-=inst.move_by; break;
			case 'D': info.row+=inst.move_by; break;
		}

		for(int j=0; j<=old.size; j++)
		{	
			switch(old.type)
			{
				case '+':
					grid [old.row+j] [old.column].type = '.';
					grid [old.row-j] [old.column].type = '.';
				case '-':
					grid [old.row] [old.column+j].type = '.';
					grid [old.row] [old.column-j].type = '.';
					break;
				case 'x':
					grid [old.row+j] [old.column+j].type = '.';
					grid [old.row-j] [old.column-j].type = '.';
				case '/':
					grid [old.row+j] [old.column-j].type = '.';
					grid [old.row-j] [old.column+j].type = '.';
					break;
			}
		
		}

		if( (border=borderError(grid,rows,columns,info)) )
		{
			printf("BORDER ERROR: %c can not be moved from (%d,%d) to (%d,%d).\n"
				,info.type, old.row+1, old.column+1 ,info.row+1, info.column+1 );
		}	
		if( (conflict=conflictError(grid,rows,columns,info)) )
		{
			printf("CONFLICT ERROR: %c can not be moved from (%d,%d) to (%d,%d).\n"
				,info.type, old.row+1, old.column+1 ,info.row+1, info.column+1 );
		}
		if(border || conflict)
		{
			for(int j=0; j<=old.size; j++)
			{	
				switch(old.type)
				{
					case '+':
						grid [old.row+j] [old.column].type = '+';
						grid [old.row-j] [old.column].type = '+';
						grid [old.row] [old.column+j].type = '+';
						grid [old.row] [old.column-j].type = '+';
						break;
					case '-':
						grid [old.row] [old.column+j].type = '-';
						grid [old.row] [old.column-j].type = '-';
						break;
					case 'x':
						grid [old.row+j] [old.column+j].type = 'x';
						grid [old.row-j] [old.column-j].type = 'x';
						grid [old.row+j] [old.column-j].type = 'x';
						grid [old.row-j] [old.column+j].type = 'x';
						break;
					case '/':
						grid [old.row+j] [old.column-j].type = '/';
						grid [old.row-j] [old.column+j].type = '/';
						break;
				}
			
			}
		}
		else
		{	

			for(int j=0; j<=info.size; j++)
			{	
				switch(info.type)
				{
					case '+':
						grid [old.row+j] [old.column] = empty;
						grid [old.row-j] [old.column] = empty;
					case '-':
						grid [old.row] [old.column+j] = empty;
						grid [old.row] [old.column-j] = empty;
						break;
					case 'x':
						grid [old.row+j] [old.column+j] = empty;
						grid [old.row-j] [old.column-j] = empty;
					case '/':
						grid [old.row-j] [old.column+j] = empty;
						grid [old.row+j] [old.column-j] = empty;
						break;
				}
			
			}


			for(int j=0; j<=info.size; j++)
			{	
				switch(info.type)
				{
					case '+':
						grid [info.row+j] [info.column] = info;
						grid [info.row-j] [info.column] = info;
					case '-':
						grid [info.row] [info.column+j] = info;
						grid [info.row] [info.column-j] = info;
						break;
					case 'x':
						grid [info.row+j] [info.column+j] = info;
						grid [info.row-j] [info.column-j] = info;
					case '/':
						grid [info.row-j] [info.column+j] = info;
						grid [info.row+j] [info.column-j] = info;
						break;
				}
			
			}
			printf("SUCCESS: %c moved from (%d,%d) to (%d,%d).\n"
				,info.type, old.row+1, old.column+1 ,info.row+1, info.column+1 );
		}

		 
	}
	
	

	fclose(instructionsptr);

	return 0;
}

