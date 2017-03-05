#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "answer03.h"

Maze *Allocate_maze_space(int, int);
void Deallocate_maze_space(Maze *maze);
int Write_maze_to_2Dfile(char *filename, const Maze *maze);
Maze *Read_maze_from_2Dfile(FILE *fptr);
//Maze *Allocate_maze_int_space(int nrow, int ncol);
//Maze *Read_maze_from_int2Dfile(FILE *fptr);

/* given a maze, given a location cur, is that PATH */
/* if out of bound, return 0                        */
/* if within bound, but not PATH, return 0          */
/* otherwise return 1                               */

static int Is_path(Maze *maze, int row, int col)
{
   if ((row >= 0) && (row < maze->nrow)) {
      if ((col >= 0) && (col < maze->ncol)) {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return 0;
}

/* given a maze, current row (curr),                                     */
/* current column (curc), destination row (drow), destination col (dcol) */
/* current distance from source, determine the where to explore from the */
/* current location                                                      */
/* a recursive function: from the current location, try 'N', 'S', 'E',   */
/* 'W' locations one at a time if the attempt is successful, write the   */
/* direction in the file                                                 */


/*
static int Pathfinder_helper2(Maze *maze,int *all, int curr, int curc, int endr, int endc,int count,FILE *dfptr)
{
    
	  
	  printf("(%d,%d),%d,all=%d\n", curr, curc, count,*all);
     // maze->maze_array[curr][curc] = VISITED;
      if(maze->maze_array[curr][curc] == ' ' )
      {
	    maze->maze_array[curr][curc] = count;
	  }
	  else if(count < maze->maze_array[curr][curc])
	  {
	    maze->maze_array[curr][curc] = count;
	  }
   if ((curr == endr) && (curc == endc)) { // reach the destination 
	  if(*all == count)
	  {

	    int i;
       for (i = 0; i < count; i++) { // create enough space in file
         fputc(VISITED, dfptr);
      }
        return count;
	  }
   }

   int found;
   if (Is_path(maze, curr-1, curc)) {
      found = Pathfinder_helper2(maze,all, curr-1, curc, endr, endc, count+1, dfptr);
	  //maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
		 fseek(dfptr,count,SEEK_SET);
         fputc('N', dfptr);
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (Is_path(maze, curr+1, curc)) {
      found = Pathfinder_helper2(maze,all,curr+1, curc, endr, endc, count+1, dfptr);
	  //maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
		 fseek(dfptr,count,SEEK_SET);
         fputc('S', dfptr);
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
    
   if (Is_path(maze, curr, curc+1)) {
      found = Pathfinder_helper2(maze,all, curr, curc+1, endr, endc, count+1, dfptr);
      //maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
		 fseek(dfptr,count,SEEK_SET);
         fputc('E', dfptr);
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (Is_path(maze, curr, curc-1)) {
      found = Pathfinder_helper2(maze,all, curr, curc-1, endr, endc, count+1, dfptr);
	  //maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
		 fseek(dfptr,count,SEEK_SET);
         fputc('W', dfptr);
         //fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   maze->maze_array[curr][curc] = ' ';
   return -1;
}
 





    static int Pathfinder_helper(Maze *maze,int *all, int curr, int curc, int endr, int endc, int count,FILE *dfptr)
{
    
      //maze->maze_array[curr][curc] = VISITED;
    if(maze->maze_array[curr][curc] == ' ' )
      {
	    maze->maze_array[curr][curc] = count;
	  }
	  else if(count < maze->maze_array[curr][curc])
	  {
	    maze->maze_array[curr][curc] = count;
	  }

   if ((curr == endr) && (curc == endc)) { // reach the destination 
	  if(*all > count)
	  {
	    *all = count;
	  }
	  int i;
      for (i = 0; i < count; i++) { // create enough space in file
         fputc(VISITED, dfptr);
      }
	  
   }

   int found;
   if (Is_path(maze, curr-1, curc)) {
      found = Pathfinder_helper(maze,all, curr-1, curc, endr, endc, count+1, dfptr);
	  //maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
        fseek(dfptr, -1, SEEK_CUR); // go back one position
        fputc('N', dfptr);
        fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (Is_path(maze, curr+1, curc)) {
      found = Pathfinder_helper(maze,all, curr+1, curc, endr, endc, count+1, dfptr);
	 // maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        fputc('S', dfptr);
        fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
    
   if (Is_path(maze, curr, curc+1)) {
      found = Pathfinder_helper(maze, all,curr, curc+1, endr, endc, count+1, dfptr);
      //maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('E', dfptr);
        fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (Is_path(maze, curr, curc-1)) {
      found = Pathfinder_helper(maze,all, curr, curc-1, endr, endc, count+1, dfptr);
	  //maze->maze_array[curr][curc] = ' ';
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('W', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   maze->maze_array[curr][curc] = ' ';
   return -1;
}
 
   
*/
static int Pathfinder_helper4(Maze *maze, int*all ,int curr, int curc, int endr, int endc,
                 int count, FILE *dfptr)
{
   
   if(maze->maze_array[curr][curc] == ' ')
    {
    maze->maze_array[curr][curc] = count;
    }
   else if(count < maze->maze_array[curr][curc])
    {
    maze->maze_array[curr][curc] = count;
    }

   if ((curr == endr) && (curc == endc)) { // reach the destination
     if (*all == count)
       {
		 int i;
         for (i = 0; i < count; i++) { // create enough space in file
         fputc(VISITED, dfptr);
         }
        return count;
       }
    }
   int found;
   if (Is_path(maze, curr-1, curc)) {
     found = Pathfinder_helper4(maze,all, curr-1, curc, endr, endc, count+1, dfptr);
      if (found != -1) {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('N', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (Is_path(maze, curr+1, curc)) {
     found = Pathfinder_helper4(maze,all, curr+1, curc, endr, endc, count+1, dfptr);
      
      if (found != -1) {
		 fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('S', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (Is_path(maze, curr, curc+1)) {
     found = Pathfinder_helper4(maze, all,curr, curc+1, endr, endc, count+1, dfptr);
      if (found != -1) {
		 fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('E', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   if (Is_path(maze, curr, curc-1)) {
     found = Pathfinder_helper4(maze, all, curr, curc-1, endr, endc, count+1, dfptr);
      if (found != -1) {
		 fseek(dfptr, -1, SEEK_CUR); // go back one position
         fputc('W', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
         return found;
      }
   }
   maze->maze_array[curr][curc] = ' ';  
   return -1;
}
static int Pathfinder_helper3(Maze *maze, int curr, int curc, int endr, int endc,
                 int count, int* all)
{
   
   if(maze->maze_array[curr][curc] == ' ')
    {
    maze->maze_array[curr][curc] = count;
    }
   else if(count < maze->maze_array[curr][curc])
    {
    maze->maze_array[curr][curc] = count;
    }
    if ((curr == endr) && (curc == endc)) { // reach the destination
     if (count < *all)
     {
     *all = count;
    }
   }
   int found;
   if (Is_path(maze, curr-1, curc)) {
     found = Pathfinder_helper3(maze, curr-1, curc, endr, endc, count+1,  all);
      if (found != -1) {
         return found;
      }
   }

   if (Is_path(maze, curr+1, curc)) {
     found = Pathfinder_helper3(maze, curr+1, curc, endr, endc, count+1,  all);
      if (found != -1) {
         return found;
      }
   }

   if (Is_path(maze, curr, curc+1)) {
     found = Pathfinder_helper3(maze, curr, curc+1, endr, endc, count+1, all);
      if (found != -1) {
         return found;
      }
   }
    
   if (Is_path(maze, curr, curc-1)) {
     found = Pathfinder_helper3(maze, curr, curc-1, endr, endc, count+1,  all);
      
      if (found != -1) {
         return found;
      }
   }
   maze->maze_array[curr][curc] = ' ';
   return -1;
}

int Find_path_from_top_entrance_to_bottom_exit(char *mazefile, char *directionfile)
{
   FILE *mfptr = fopen(mazefile, "r");
   if (mfptr == NULL) {
      return -1;}
   Maze *maze = Read_maze_from_2Dfile(mfptr);
   fclose(mfptr);
   if (maze == NULL) {
      return -1;
   }
    int nrow = maze-> nrow;
	int ncol = maze-> ncol;

   // find the starting location, the top-most, left-most opening /
   int startr, startc;
   startr = 0;
   for (startc = 0; startc < maze->ncol; startc++) {
      if (maze->maze_array[startr][startc] == PATH) {
         break;
      }
   }


   // find the ending location, the bottom-most, right most opening 
   int endr, endc;
   endr = maze->nrow-1;
   for (endc = maze->ncol-1; endc >= 0; endc--) {
      if (maze->maze_array[endr][endc] == PATH) {
         break;
      }
   } 

   // no starting location, deallocate and return 
   if (startc == maze->ncol) {
      Deallocate_maze_space(maze);
      return -1;
   }
   // no ending location, deallocate and return 
   if (endc == -1) {
      Deallocate_maze_space(maze);
      return -1;
   }


   FILE *dfptr = fopen(directionfile, "w");
   if (dfptr == NULL) {
      Deallocate_maze_space(maze);
      return -1;
   }
   int plus = nrow * ncol;
   int *all = &plus;
   Pathfinder_helper3(maze, startr, startc, endr, endc, 0, all);
   fseek(dfptr,0,SEEK_SET);
   Pathfinder_helper4(maze,all, startr, startc, endr, endc, 0, dfptr);
   fclose(dfptr);
   Deallocate_maze_space(maze);
   return *all;
}
/* this is a function implemented by the instructor to illustrate           */
/* how to use a recursive function to go from the left-most top entrance to */
/* the right-most bottom exit of a maze.  The function will print the       */
/* directions taken to reach the bottom exit, without visiting a location   */
/* twice.  Note that the recursion may visit a location a few times         */
/* Given three filenames, first one is a given maze, the second one is to   */
/* be written with the directions, the third is the explored maze           */
/* If the maze file does not exist, the function immediately return -1 and  */
/* do nothing else                                                          */
/* the directions are in the form of a series of characters                 */
/* 'N', 'S', 'E', 'W', without spacing (and without the quotes).            */
/* There should be just a single line, without a terminating newline        */
/* character. In other words, to the vi editor, it is an incomplete file    */
/* you are to assume that you start from the top-most, left-most entry      */
/* of the maze.  Therefore, the first direction is always 'S'               */
/* similarly, the last direction is always 'S'                              */
/* the returned value should be the number of steps taken to reach          */
/* the right-most bottom exit.  It is typically not the shortest distance   */
/* Note that the maze can be generated by amaze, or some combinations of    */
/* the maze expansion functions that you have written in PE08               */
/* you may assume that the maze file, if it exists, is in the correct format*/

/*

int Find_path_from_top_entrance_to_bottom_exit(char *mazefile, char *directionfile, char *visitedfile)
{
   //int steps=0;
   FILE *mfptr = fopen(mazefile, "r");
   if (mfptr == NULL) {
      return -1;
   }
   
   // read the maze from mfptr 
  
   Maze *maze = Read_maze_from_2Dfile(mfptr);
   if (maze == NULL) {
      return -1;
   }
   fclose(mfptr);
    int nrow = maze-> nrow;
	int ncol = maze-> ncol;

   // find the starting location, the top-most, left-most opening /
   int startr, startc;
   startr = 0;
   for (startc = 0; startc < maze->ncol; startc++) {
      if (maze->maze_array[startr][startc] == PATH) {
         break;
      }
   }

   // find the ending location, the bottom-most, right most opening 
   int endr, endc;
   endr = maze->nrow-1;
   for (endc = maze->ncol-1; endc >= 0; endc--) {
      if (maze->maze_array[endr][endc] == PATH) {
         break;
      }
   } 

   // no starting location, deallocate and return 
   if (startc == maze->ncol) {
      Deallocate_maze_space(maze);
      return -1;
   }
   // no ending location, deallocate and return 
   if (endc == -1) {
      Deallocate_maze_space(maze);
      return -1;
   }

   FILE *dfptr = fopen(directionfile, "w");
   if (dfptr == NULL) {
      Deallocate_maze_space(maze);
      return -1;
   }
   int giveall = nrow*ncol;

   int *all;
   all = &giveall;
   int count;
   int count2;
   printf("all = %d\n",*all);
   printf("(%d,%d) to (%d,%d)\n",startr, startc, endr, endc);
   count = Pathfinder_helper(maze, all, startr, startc, endr, endc, 0, dfptr);
   //printf("count = %d\n", *all);
   count2 = Pathfinder_helper2(maze, all, startr, startc, endr, endc, 0, dfptr);
   //printf("count2 = %d\n",*all); 

   fclose(dfptr);
   Deallocate_maze_space(maze);
   return *all;
}
*/
/* Details of the function can be found in README                        */
/* this function expects four parameters: two filenames, and coordinates */
/* of two locations                                                      */
/* two filenames: first one is a given maze, the second one is to        */
/* be written with the directions                                        */
/* coordinates of two locations: source and destination locations        */
/*                                                                       */
/* If the maze file does not exist, you should immediately return -1 and */
/* do nothing else, i.e., the direction file should not be created       */
/* If the maze file cannot be read into a Maze structure, you should     */
/* immediately return -1 and do nothing else                             */
/* If the coordinates are not valid, do nothing and return -1            */
/* If the directions file cannot be opened for writing, return -1        */
/* The function should write the directions of a shortest path from the  */
/* source location to the destination location into the directions file  */
/* the directions are in the form of a series of characters              */
/* 'N', 'S', 'E', 'W', without spacing (and without the quotes).         */
/* There should be just a single line, without a terminating newline     */
/* character. In other words, to the vi editor, it is an incomplete file */
/* The directions should allow an agent to travel in the maze from the   */
/* source coordinates to the destination coordinates using the fewest    */
/* number of moves                                                       */
/* the number of moves taken by the agent in a shortest path should be   */
/* returned                                                              */
/* Note that the maze can be generated by amaze, or some combinations of */
/* the maze expansion functions that you have written in PE08            */
/* you may assume that the maze file, if it exists, is in the correct    */
/* format                                                                */

int DFS_shortest_path_directions(char *mazefile, char *directionfile,
                        Coord source, Coord destination)
{  
   int srow = source.row;
   int scol = source.col;
   int drow = destination.row;
   int dcol = destination.col;

   if (mazefile == NULL)
   {
    return -1;
   }
   FILE *mfptr;
   mfptr = fopen(mazefile, "r");
   if(mfptr == NULL)
   {
//	fclose(mfptr);
    return -1;
   }
   
   Maze *maze = Read_maze_from_2Dfile(mfptr);
   if (maze == NULL) { 
	  fclose(mfptr);
      Deallocate_maze_space(maze);
      return -1;
   }
   fclose(mfptr);
    
   if(!Is_path(maze, srow, scol))
   {
	Deallocate_maze_space(maze);
    return -1;
   }

   if(!Is_path(maze,drow,dcol))
   {
	Deallocate_maze_space(maze);
    return -1;
   }
   
   FILE *dfptr = fopen(directionfile, "w");
   if (dfptr == NULL) {
      Deallocate_maze_space(maze);
      return -1;
   }
   int nrow = maze-> nrow;
   int ncol = maze-> ncol;
   int all = nrow*ncol;
   int *realall = &all;
   Pathfinder_helper3(maze, srow, scol, drow, dcol, 0, realall);
   fseek(dfptr,0,SEEK_SET);
   Pathfinder_helper4(maze,realall, srow, scol, drow, dcol, 0, dfptr);
   fclose(dfptr);
   Deallocate_maze_space(maze);
   return *realall;
}

    
/* Details of the function can be found in README                        */
/* this function expects 5 parameters: 3 filenames, and coordinates of   */
/* the source and destination locations                                  */
/* three filenames: first one is a given maze, the second one is a       */
/* directions file (a series of characters 'N', 'S', 'E', 'W'), you are  */
/* to simulate the movement of agent according to the directions         */
/* given in the direction files. The maze showing the locations that the */
/* agent has visited will be stored in the third file.                   */
/* the source and destination coordinates are the starting and end points*/
/* of the agent's path in the maze                                       */
/*                                                                       */
/* If the maze file does not exist, you should immediately return -1 and */
/* do nothing else                                                       */
/* If the maze file cannot be read into a Maze structure, you should     */
/* immediately return -1 and do nothing else                             */
/* If the direction file does not exist, you should immediately return   */
/* -1 and do nothing else                                                */
/* if the coordinates are not valid, you should immediately return -1    */
/* and do nothing else                                                   */
/* Otherwise, it means that the agent has been airdropped to the starting*/
/* and the starting location has been visited                            */
/* You should simulate until you reach the end of file of the direction  */
/* file or encounter an invalid direction                                */
/* you should print the visited maze into the third given filename, the  */
/* visitedfile, with visited locations represented by '.'                */
/* if you encounter an invalid direction (wrong character, try to visit  */
/* a location with WALL, try to visit a location again, try to move the  */
/* agent out of bound), you should return -1                             */
/* do not change a location with WALL to a VISITED location              */
/* If the agent successfully reach the final destination with valid      */
/* directions in the direction file, and the visited maze can be output  */
/* properly, you should return the number of visited locations,          */
/* otherwise, return -1                                                  */
/* you may assume that the maze file, if it exists, is in correct format */

 int Simulate_movement(char *mazefile, char *directionfile, char *visitedfile,
                      Coord source, Coord destination)
 { 
   if(mazefile == NULL)
   {
     return -1;
   }
   if(directionfile == NULL)
   {
    return -1;
   }

   int srow = source.row;
   int scol = source.col;
   int drow = destination.row;
   int dcol = destination.col;

   int curr = srow;
   int curc = scol;
 
   FILE *mfptr = fopen(mazefile, "r");
   if (mfptr == NULL) {
	  //fclose(mfptr);
      return -1;
   }
   
   /* read the maze from mfptr */
 
   Maze *maze = Read_maze_from_2Dfile(mfptr);
   fclose(mfptr);
   if (maze == NULL) {
	  Deallocate_maze_space(maze);
      return -1;
   }
   /*
   if(!Is_path(maze, srow, scol))
   {
	Deallocate_maze_space(maze);
    return -1;
   }

   if(!Is_path(maze,drow,dcol))
   {
	Deallocate_maze_space(maze);
    return -1;
   }
   */
 
   FILE *dfptr = fopen(directionfile, "r");
     if (dfptr == NULL) {
        Deallocate_maze_space(maze);
        return -1;
     }
 
   int ch = 0; 
   int steps = 1;
   fseek(dfptr, 0 ,SEEK_SET);
  
	  while((ch = fgetc(dfptr)) != EOF)
	  {   
	    // Write_maze_to_2Dfile(visitedfile, maze);
      if ((Is_path(maze, curr, curc))&&(ch == 'S')){
	       maze->maze_array[curr][curc] = VISITED;
	       // Write_maze_to_2Dfile(visitedfile, maze);
	       curr++;
	       steps++;
	  }
      else if ((Is_path(maze, curr, curc))&&(ch == 'N')){
	       maze->maze_array[curr][curc] = VISITED;
	       // Write_maze_to_2Dfile(visitedfile, maze);
               curr--;
	       steps++;

	  }
      else if ((Is_path(maze, curr, curc))&&(ch == 'W')){
	      maze->maze_array[curr][curc] = VISITED;
	      // Write_maze_to_2Dfile(visitedfile, maze);
              curc--;
	      steps++;
	      

      }
      else if ((Is_path(maze, curr, curc))&&(ch == 'E')){
	      maze->maze_array[curr][curc] = VISITED;
	      //  Write_maze_to_2Dfile(visitedfile, maze);
              curc++;
	      steps++;
       } 
	 else if(ch == '\n'){}
	 else
	   {
	     // maze->maze_array[curr][curc] = VISITED;
           Write_maze_to_2Dfile(visitedfile, maze);
           fclose(dfptr);
           Deallocate_maze_space(maze);
           return -1;}
     }
 
    maze->maze_array[drow][dcol] = VISITED;
    Write_maze_to_2Dfile(visitedfile, maze);
    fclose(dfptr);
    Deallocate_maze_space(maze);
    return steps;
}
 
	
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
