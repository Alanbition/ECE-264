#include <stdio.h>
#include <stdlib.h>
#include "answer10.h"

int main(int argc, char ** argv)
{

  storenode *list = NULL;
  realnode *head = NULL;
  FILE *fptr;
  fptr = fopen(argv[1],"r");
  FILE *fptr2;
  fptr2 = fopen(argv[2],"w");
  FILE *fptr3;
  fptr3 = fopen(argv[3],"w");
  FILE *fptr4;
  fptr4 = fopen(argv[4],"w");

  list = firstcall(fptr,fptr2);
  
  secondcall(&head,list,fptr3); 
 // printf("%c",(head->callt)->tchr);
  lastcall(&head, fptr4);
  free_all_store(list);
  fclose(fptr);
  fclose(fptr2);
  fclose(fptr3);
  fclose(fptr4);
  return EXIT_SUCCESS;
}
