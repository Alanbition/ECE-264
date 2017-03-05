#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmp.h"




int main(int argc, char ** argv)
{

  int i;
  int v = 0;
  int h = 0;
  if(argc < 3)
  {
	fprintf(stderr, "Wrong number of arguments\n");
    return EXIT_FAILURE;
  }
  BMP_Image *oimage = NULL;
  BMP_Image *nimage = NULL;
  FILE *fptr;
  fptr = fopen(argv[argc-2],"r");
  if(fptr == NULL){
  
  fprintf(stderr, "Can't open input file\n");

  return EXIT_FAILURE;}
  FILE *fptr2;
  fptr2 = fopen(argv[argc-1],"w");
  if(fptr2 == NULL){
  fprintf(stderr, "Can't open file for output\n");
  return EXIT_FAILURE;}

  oimage = Read_BMP_Image(fptr); 
  
  for(i =1;i < argc-2; i++)
  {
   if(strcmp(argv[i], "-v") == 0)
   {
      v = (v+1)%2;
   }
   else if(strcmp(argv[i], "-h") == 0)
   {
      h = (h+1)%2;
   }
   else{
     fprintf(stderr, "Invalid option, -h or -v expected\n");
     return EXIT_FAILURE;
   }
  }
    
  nimage = Reflect_BMP_Image(oimage , h, v);

  Write_BMP_Image(fptr2, nimage);

  Free_BMP_Image(oimage);
  Free_BMP_Image(nimage);
  fclose(fptr);
  fclose(fptr2);
  return EXIT_SUCCESS;
}
