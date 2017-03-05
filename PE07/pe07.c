#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "answer07.h"
int main(int argc, char ** argv)
{
  FILE *fptr;
  int nrow;
  int ncol;
  int location;
  char type;
  int totalchar;
  fptr = fopen("sample.2.7x9", "r");
   
  
  Find_maze_dimensions(fptr, &nrow, &ncol);
  printf ("nrow= %d, ncol= %d \n", nrow, ncol);
/* Determine the column location of the top opening */
/* You may assume that the maze is of the correct format */

  location =  Find_opening_location(fptr);

  printf("location = %d \n", location); 

/* Count the number of locations that are PATH  */
/* A location is a PATH if it is a space, ' ', or PATH */
/* You may assume that the maze is of the correct format */
  int countpath;
  countpath =  Count_path_locations(fptr);
  printf("countpath = %d \n", countpath);
/* Return the type of location: WALL or PATH, i.e. 'X' or ' ' */
/* In other words, return the character in the file for that location */ 
/* The location is specified by its row-column coordinates. */
/* The coordinates are specified by row and col */
/* These coordinates will always be valid for the given maze */
/* You do not have to worry about the coordinates being out of range */
/* You may assume that the maze is of the correct format */

  type =   Get_location_type(fptr, 6, 6);

   printf("type = %c \n", type); 
 
/* Given a filename, re-represent the maze in the file pointer fptr */
/* in a single line */
/* The return value should be the number of characters written into the */
/* the new file */
/* if the writing to a file fails, you should return -1 */ 
/* You may assume that the maze is of the correct format */

  totalchar = Represent_maze_in_one_line("file2", fptr);

   printf("totalchar = %d \n", totalchar); 

  return EXIT_SUCCESS;
}

