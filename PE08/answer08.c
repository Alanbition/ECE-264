#include <stdio.h>
#include <stdlib.h>
#include "answer08.h"

// if you want to declare and define new functions, do not name them
// with a prefix "__".  The instructors will be using functions with
// such names to test your individual functions.  You should not be 
// calling a function whose name has a prefix "__" because your program
// should compile without any functions from the instructors.
// you may put your additional functions here or at the end of this file



// allocate space from heap memory for the user-defined structure Maze, and
// allocate nrow x ncol maze and store the address in the structure (in 
// maze_array)
// also assign nrow and ncol fields in the structure accordingly
// if allocation fails, return NULL
// if allocation fails, you are also responsible for freeing the memory
// allocated in this function before the failure
// may assume that nrow and ncol are > 0

Maze *Allocate_maze_space(int nrow, int ncol)
{
   int row;
   int row1;
   int row2;
   Maze *maze = NULL;
   maze = malloc(sizeof(Maze));
   maze->nrow = nrow;
   maze->ncol = ncol;
   char  **array1;
   array1 = malloc(sizeof(char*) * nrow);
   maze->maze_array = array1;
   for (row = 0;row < nrow; row++)
   {
    array1[row] = malloc(sizeof(char) * (ncol + 1));
	if(array1[row] == NULL)
	{
	  for (row2 = 0; row2< nrow; row2++)
	  {
	    free(array1[row2]);
	  }
	  free(array1);
	  return NULL;
	}
   }
   if(maze == NULL)
   {
     for(row1 = 0;row1 < nrow; row1 ++)
   {
     free(array1[row1]);
   }
   free(array1);
   return NULL;
   }
  return maze; 
}

// free the memory used for the maze
// you may assume that maze is not NULL, and all memory addresses are valid

void Deallocate_maze_space(Maze *maze)
{
   int row = maze -> nrow;
   int row1;
   
   for (row1 = 0; row1 < row; row1 ++)
   {
     free(maze -> maze_array[row1]);
   }
   free(maze ->maze_array);
   free(maze);
}

/* Read maze in a multi-line file and store the necessary information */
/* into a 2D array of characters.  The address of the 2D array and the */
/* dimensions of the 2D array should be stored in a Maze structure allocated */
/* from the heap memory */
/* if the allocation fails, should return NULL */

Maze *Read_maze_from_2Dfile(FILE *fptr)
{
   int ch = 0;
   int row =0;
   int row1;
   int col = 0;
   int col1 ;
   char **maze_array;
   Maze *maze;
   fseek(fptr, 0 ,SEEK_SET);
   while((ch = fgetc(fptr)) !=EOF)
   {
     if(ch == '\n')
	 {
	  row++;
	 }
     col++;
   }

     col = col/row -1;
   maze = Allocate_maze_space(row, col);
   maze_array = maze->maze_array;
   fseek(fptr, 0, SEEK_SET);
   for(row1 =0; row1 < row; row1++)
   {
   for(col1 = 0; col1 < col+1; col1++)
   {
     ch = fgetc(fptr);
	if( ch != '\n')
	{

	 maze -> maze_array[row1][col1] = ch;
	}

	}
   }
   return maze;
}

/* Write the maze into a multi-line file */
/* the maze has to stay intact */

int Write_maze_to_2Dfile(char *filename, const Maze *maze)
{
   int ch = 0;
   int nrow = maze-> nrow;
   int row1;
   int ncol = maze-> ncol;
   int col1;
   FILE *fptr;
   fptr = fopen(filename, "w");
   if( fptr == NULL){return -1;}
   else
   {
   for(row1 = 0; row1< nrow; row1++)
   {
   for(col1 = 0; col1 < ncol+1; col1++)
   {
    if(col1 == (ncol))
	{
	 ch = '\n';
	}
	else
	{
     ch = maze -> maze_array[row1][col1];
	
	}
    fputc(ch, fptr);
	// if(ch == EOF)
	// {
	//  return -1;
	// }
   }
   }
   }
   fclose(fptr);
   return nrow * (ncol+1);
}

/* Expand the maze from nrow x ncol to (2nrow - 1) x ncol */
/* the top half of the maze is the same as the original maze */
/* the bottom half of the maze is a reflection of the original maze */
/* You have to allocate space for a new maze */
/* the nrow and ncol fields of the new maze have to be assigned accordingly */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned */
/* the original maze has to stay intact */

Maze *Expand_maze_row(const Maze *maze)
{ 
   int row;
   int col;
   int nrow = maze -> nrow;
   int ncol = maze -> ncol;
   int newrow = (maze->nrow)*2 -1;
   char **array2;
   Maze *maze2;
   maze2 = Allocate_maze_space(newrow, ncol);
   array2 =  maze2 -> maze_array;
  
   for(row = 0;row < newrow ;row++)
   {
     if(row < nrow)
	{
	   for(col = 0; col < ncol; col++)
	   {
	    array2[row][col] = maze -> maze_array[row][col];
       }
	}

 	else
	{
	 for(col =0; col < ncol; col++)
	  {
	   array2[row][col] = maze -> maze_array[(newrow - row-1)][col];
	  }
	}
   }
	 
   return maze2;
}

/* Expand the maze from nrow x ncol to nrow x 2ncol - 1 */
/* the left half of the maze is the same as the original maze */
/* the right half of the maze is a reflection of the original maze */
/* moreover, you have to create an opening between the left and right halves */
/* the opening should be at the middle row of the maze */
/* the opening must also be accessible from one of the paths in the */
/* new maze */
/* to do that, you have to convert some locations that are WALL to PATH */
/* starting from the new opening to the left and to the right until you reach */
/* a location that is adjacent to a location that is PATH */
/* You have to allocate space for a new maze */
/* the nrow and ncol fields of the new maze have to be assigned accordingly */
/* if you can't expand the maze because of memory issue, NULL should be */
/* returned */
/* the original maze has to stay intact */

Maze *Expand_maze_column(const Maze *maze)
{  

   int row;
   int col;
   int ncol = maze -> ncol;
   int ncolcopy = ncol;
   int newcol = (maze->ncol)*2 -1;
   int newrow = (maze ->nrow);
   Maze *maze3;
   char **array3;
   maze3 = Allocate_maze_space(newrow, newcol);
   array3 = maze3 -> maze_array;
   for(row =0; row < newrow; row++)
   {
     
   for(col = 0; col < newcol; col++)
   {
    if(col < ncol)
	{
	  array3[row][col] = maze -> maze_array[row][col];
	}
	else
	{
	 {
	   array3[row][col] = maze -> maze_array[row][newcol-col-1];
	 }
   }
   }
   }
    array3[newrow/2][ncol-1] = ' ';
   {
    while((array3[newrow/2-1][ncolcopy-1] == 'X') && (array3[newrow/2+1][ncolcopy-1] == 'X'))
	{
	 array3[newrow/2][ncolcopy-2] = ' ';
	 array3[newrow/2][newcol-ncolcopy+1] = ' ';
	 ncolcopy--;
    }
   } 
   return maze3;
}

// if you want to declare and define new functions, put them here
// or at the beginning of the file

