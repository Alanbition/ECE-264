#include <stdio.h>
#include <stdlib.h>
#include "answer04.h"

int main(int argc, char ** argv)
{

  if(argc != 5)
  {
   return EXIT_FAILURE;
  }
  storenode *list = NULL;
  realnode *head = NULL;
  FILE *fptr;
  fptr = fopen(argv[1],"r");
  if(fptr == NULL){return EXIT_FAILURE;}
  FILE *fptr2;
  fptr2 = fopen(argv[2],"w");
  if(fptr2 == NULL){return EXIT_FAILURE;}
  FILE *fptr3;
  fptr3 = fopen(argv[3],"w+");
  if(fptr3 == NULL){return EXIT_FAILURE;}
  FILE *fptr4;
  fptr4 = fopen(argv[4],"w");
  if(fptr4 == NULL){return EXIT_FAILURE;}
  list = firstcall(fptr);
  
  secondcall(&head,list); 
 // printf("%c",(head->callt)->tchr);
  lastcall(&head, fptr2, fptr3, fptr4);

  free_all_store(list);
  fclose(fptr);
  fclose(fptr2);
  fprintf(fptr3,"0");
  fclose(fptr3);
  fclose(fptr4);
  return EXIT_SUCCESS;
}
