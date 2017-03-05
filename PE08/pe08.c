#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "answer08.h"
int main(int argc, char ** argv)
{
  FILE *fptr;
  int totalchar;
  Maze *maze;
  Maze *maze1;
  Maze *maze2;
  fptr = fopen("rsample.2.13x9", "r");
 

   maze = Read_maze_from_2Dfile(fptr);


  
   
 
   totalchar =  Write_maze_to_2Dfile("file1",maze);
   printf("totalsize = %d",totalchar);


   maze1 = Expand_maze_row(maze);
  
   totalchar =  Write_maze_to_2Dfile("file2",maze1);
   printf("totalsize = %d",totalchar);


   maze2 = Expand_maze_column(maze);

   totalchar =  Write_maze_to_2Dfile("file3",maze2);
   printf("totalsize = %d",totalchar);



   Deallocate_maze_space(maze);
   Deallocate_maze_space(maze1);
   Deallocate_maze_space(maze2);
   return EXIT_SUCCESS;
}
