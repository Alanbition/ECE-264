#include <stdio.h>
#include <stdlib.h>
#include "answer07.h"

/* Determine the dimensions of the maze contain in file. */
/* The maze will always be of the correct format */
/* the number of rows is to be stored at location pointed to by nrow */ 
/* the number of ncol is to be stored at location pointed to by ncol */

void Find_maze_dimensions(FILE *fptr, int *nrow, int *ncol)
{
   int ch=0;
   *nrow = *ncol = 0;
   fseek(fptr, 0,SEEK_SET);

   while((ch = fgetc(fptr)) != EOF)
   {
    if(ch == '\n')
	{
	 (*nrow)++;
	}
	 (*ncol)++;

   } 
  
  (*ncol) = (*ncol)/(*nrow) - 1;
}

/* Determine the ooooocolumn location of the top opening */
/* you may assume that the maze is of the correct format */

int Find_opening_location(FILE *fptr)
{
   int ch=0;
   int countrow=0;
   fseek(fptr, 0, SEEK_SET);
   while((ch = fgetc(fptr)) !=EOF)
   {
	 if(ch == ' ')
	 {
	 return countrow;}
     countrow++;
   }
   return 0;
}
/* Count the number of locations that are PATH */
/* A location is PATH if it is a space, ' ', or PATH */
/* you may assume that the maze is of the correct format */

int Count_path_locations(FILE *fptr)
{
   int ch=0;
   int countpath = 0;
   fseek(fptr, 0, SEEK_SET);
   while((ch = fgetc(fptr)) !=EOF)
   {
    if(ch == ' ')
	{
	  countpath++;
    }
    }
   return countpath;
}

/* Return the type of location: WALL or PATH */
/* The location is specified by its row-column coordinates. */
/* The coordinates are specified by row and col */
/* you may assume that these coordinates are always valid */
/* you may assume that the maze is of the correct format */

char Get_location_type(FILE *fptr, int row, int col) {
    
   int nrow;
   int ncol;
   Find_maze_dimensions(fptr, &nrow,  &ncol);
   fseek(fptr, (ncol+1)*row + col , SEEK_SET);
 //  char ch = fgetc(fptr);


   return fgetc(fptr);
}
 
/* Given a filename, re-represent the maze in the file pointer fptr */
/* in a single line */
/* The return value should be the number of characters written into the */
/* the new file */
/* if the writing to a file fails, you should return -1 */ 
/* you may assume that the maze is of the correct format */

int Represent_maze_in_one_line(char *filename, FILE *fptr)
{

   int ch=0;
   int nrow;
   int ncol;
   FILE *fptr2; 
   Find_maze_dimensions(fptr, &nrow, &ncol);
   int ele = nrow*ncol;
   fseek(fptr, 0,SEEK_SET);
   fptr2 = fopen(filename, "w");
   if( fptr2 == NULL)
   {
     return -1;
   }
   else
   {

   while((ch = fgetc(fptr)) != EOF)
   {
     if(ch == '\n')
	 {
	 }
	 else
	 {
       fputc(ch,fptr2);
	   if (ch == EOF)
	   {
	     return -1;
	   }
	   
     }

   }  
   }
   fclose(fptr2);
   return ele;
  }
