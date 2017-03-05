#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmp.h"




int main(int argc, char ** argv)
{

  if(argc != 3)
  {
	fprintf(stderr, "Wrong number of arguments\n");
    return EXIT_FAILURE;
  }
  BMP_Image *oimage = NULL;
  BMP_Image *nimage = NULL;
  FILE *fptr;
  fptr = fopen(argv[1],"r");
  if(fptr == NULL){
  
  fprintf(stderr, "Can't open input file\n");

  return EXIT_FAILURE;}

  oimage = Read_BMP_Image(fptr); 
  
  if(oimage == NULL){
   fprintf(stderr, "File have problem\n");
   fclose(fptr);
   return EXIT_FAILURE;}

  FILE *fptr2;
  fptr2 = fopen(argv[2],"w");
  if(fptr2 == NULL){
  fprintf(stderr, "Can't open file for output\n");
  return EXIT_FAILURE;}


  if(oimage->header.bits == 24)
    {
        nimage =  Convert_24_to_16_BMP_Image_with_Dithering(oimage);
    }
  if(oimage->header.bits == 16)
    {
        nimage = Convert_16_to_24_BMP_Image(oimage);
    }
  Write_BMP_Image(fptr2, nimage);

  Free_BMP_Image(oimage);
  Free_BMP_Image(nimage);
  fclose(fptr);
  fclose(fptr2);
  return EXIT_SUCCESS;
}
