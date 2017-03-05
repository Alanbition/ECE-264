#include <stdio.h>
#include <stdlib.h>
#include "answer09.h"

/* the following functions deal with priority queues implemented         */
/* as a linked list of lnode's, with the address of each object of       */
/* interest stored in the ptr field of an lnode in the list              */

/* adding an lnode to a priority queue (PQ) implemented as a linked list */
/* such that linked list is ordered (accordinging to the cmp_fn          */
/* function) from smallest to the largest                                */
/* *pq is the address of the first lnode in the linked list; it is NULL  */
/* if the linked list is empty                                           */
/* new_object is the address of the new object to be stored in the ptr   */
/* field of the new lnode in the linked list pq; if it is NULL, the      */
/* linked list should remain the same                                    */
/* cmp_fn is the address of the function that can compare two objects    */
/* whose addresses are passed to the cmp_fn function;  the two addresses */
/* are typically stored in the ptr fields of two lnodes in the           */
/* linked list; returns a negative number if the first object is smaller,*/
/* a positive number if the first object is bigger, 0 if the two objects */
/* are the same                                                          */
/*                                                                       */
/* *pq should be updated if the new lnode added becomes the first lnode  */
/* of the linked list                                                    */
/* returns the address of the newly added lnode in the linked list       */
/* if you cannot allocate space for the new lnode, keep the linked list  */
/* the same and you should return NULL                                   */
/* if new_object is NULL, you should keep the linked list the same and   */
/* return NULL                                                           */


 /*  lnode * list1 = malloc(sizeof(lnode));
   if(list1 == NULL)
   {
	
    free(list1);
    return NULL;
   }
   if(new_object == NULL)
   {
    return NULL;
   }
   list1 -> ptr = *pq;

   list1 -> next = NULL;


   while(*pq != NULL)
   {
	  int ans = cmp_fn(list1->ptr, new_object );

	if(ans >= 0)
	{

	 //insert
      if(list1 == NULL)
   	 {
	   list1->ptr = (void *)new_object;
	   list1->next = NULL;
	 }
	 else if(list1 == *pq)
	 {
	   list1->next = *pq;
	   list1->ptr  =  (void *)new_object;
	   *pq =  (void *)new_object;
	 }
	 else
	 {
	  list1->next = list1;
	  list1->ptr=  (void *)new_object;
	 }
	 return list1;
	}
	else
	{
	}

      list1 = list1 -> next;
   }
   
   return list1;
*/


lnode *PQ_enqueue(lnode **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *))


{
/* remove the first lnode in a priority queue (PQ) implemented as a      */
/* linked list                                                           */
   lnode * new_node = (lnode *)malloc(sizeof(lnode));
   if(new_node == NULL)
   {
	
    free(new_node);
    return NULL;
   }
   new_node -> ptr = (void*)new_object;
   new_node -> next = NULL;


   if(new_object == NULL)
   {
    return NULL;
   }

   // case 1: empty list to begin with

   if (*pq == NULL) {
      *pq = new_node;
      return new_node;
   }

   // case 2: non-empty list

   lnode *prev = NULL;
   lnode *curr = *pq;
   while (curr != NULL) {
   //   if (strcmp(curr->str, str) >= 0) {
	  if (cmp_fn(curr->ptr, (void *)new_object) >= 0){
         break;
      } else {
         prev = curr;
         curr = curr->next;
      }
   }
   new_node->next = curr;
   if (prev != NULL) {
      prev->next = new_node;
   } else {
      *pq = new_node;
   }
   return new_node;
}
/*
{
if (new_object == NULL) {
      return NULL;
   }
   lnode *new_node = (lnode*)malloc(sizeof(lnode));
   new_node -> ptr = (void*)new_object;
   new_node -> next = NULL;

   if (new_node == NULL) {
      return NULL;
   }
   lnode dummy;
   dummy.next = *pq;
   lnode *prev = &dummy;
   lnode *curr = *pq;
   while (curr != NULL) {
      if (cmp_fn(curr->ptr, new_object) >= 0) {
         break;
      } else {
         prev = curr;
         curr = curr->next;
      }
   }
   prev->next = new_node;
   new_node->next = curr;
   *pq = dummy.next;
   return new_node;
*/

/* *pq is the address of the first lnode in the linked list; *pq is NULL */
/* if the linked list is empty                                           */
/*                                                                       */
/* if the linked list is empty, returns NULL                             */
/* otherwise, remove the first lnode from the linked list and update *pq */
/* set the removed lnode to be a single-node linked list and return the  */
/* address of the removed lnode                                          */
                       
lnode *PQ_dequeue(lnode **pq)
   

{
   if(*pq == NULL)
   {
     return NULL;
   }
   lnode *list3 = *pq;
   *pq = list3->next;
   list3->next = NULL;



   return list3;
}


/* the following functions deal with stacks implemented                  */
/* as a linked list of lnode's, with the address of each object of       */
/* interest stored in the ptr field of an lnode in the list              */

/* adding an lnode to a stack implemented as a linked list               */
/* *stack is the address of the first lnode in the linked list; it is    */
/* NULL if the linked list is empty                                      */
/* new_object is the address of the new object to be stored in the ptr   */
/* field of the new lnode in the linked list pq; if it is NULL, the      */
/* linked list should remain the same                                    */
/*                                                                       */
/* *stack should be updated after adding the new lnode as the first lnode*/
/* of the linked list                                                    */
/* returns the address of the newly added lnode in the linked list       */
/* if you cannot allocate space for the new lnode, keep the linked list  */
/* the same and you should return NULL                                   */
/* if new_object is NULL, you should keep the linked list the same and   */
/* return NULL                                                           */

lnode *stack_push(lnode **stack, const void *new_object)
{
   lnode * list2 = (lnode *)malloc(sizeof(lnode));
   
   
   if(list2 == NULL)
   {
    return NULL;
   }

   if(new_object == NULL)
   {
    return NULL;
   }
   
   list2 -> ptr = (void*)new_object;
   list2 -> next = NULL;
   list2 -> next = *stack;
   *stack = list2;
   return list2;

}

/* remove the first lnode on a stack implemented as a linked list        */
/* *stack is the address of the first lnode in the linked list; *stack   */
/* is NULL if the linked list is empty                                   */
/*                                                                       */
/* if the linked list is empty, returns NULL                             */
/* otherwise, remove the first lnode from the linked list and update     */
/* *stack                                                                */
/* set the removed lnode to be a single-node linked list and return the  */
/* address of the removed lnode                                          */
                       
lnode *stack_pop(lnode **stack)
{
   if(*stack == NULL)
   {
     return NULL;
   }
   lnode *list3 = *stack;
   *stack = list3->next;
   list3->next = NULL;

   return list3;
}

/* remove the last lnode in a linked list of lnode's                     */
/* *list is the address of the first lnode in the linked list; *list     */
/* is NULL if the linked list is empty                                   */
/*                                                                       */
/* if the linked list is empty, returns NULL                             */
/* otherwise, remove the last lnode from the linked list and update      */
/* *list if necessay                                                     */
/* set the removed lnode to be a single-node linked list and return the  */
/* address of the removed lnode                                          */

lnode *lnode_remove_last(lnode **list)
{
if (*list == NULL){
    return NULL;
  }

  lnode *new;
  //lnode *rem;
  lnode *now = *list;
  if(now->next!= NULL)
  {
  while(now->next != NULL){
    new = now;
    now = now->next;
    if(now->next == NULL){
      new->next = NULL;
      return new;
    }
  }
  }
  else{
	new = now;
    new->next = NULL;
    return new;
  }
  return NULL;
 } 
/*

if (*list == NULL){
    return NULL;
  }
  lnode *new;
  lnode *removed;
  lnode *current = *list;
  lnode *realnode; 

  while(realnode != NULL){
    new = current;
    realnode = current->next;
    if(realnode == NULL){
      removed = current;
      new->next = NULL;
      return removed;
    }
  }
  if(realnode == NULL){
    removed = current;
    new->next = NULL;
    return removed;
  }
  return NULL;


*/

/* destroy an entire linked list, freeing all memory used                */
/* pq is the address of the first lnode in the linked list               */
/* destroy_fn is the address of the function to free the memory          */
/* associated with the address of the generic object stored in the ptr   */
/* field of lnode in the linked list                                     */
/* if ptr is storing an address of a simple data type, the function free */
/* is an appropriate destroy_fn                                          */
/* if ptr is storing an address of a structure or an array that stores   */
/* other addresses, a user-defined destroy_fn would be required.  For    */
/* example, if ptr stores an address of structure Maze in PE08, you would*/
/* have to use Deallocate_maze_space as the destroy_fn function.         */

void lnode_destroy(lnode *list, void (*destroy_fn)(void *))
{
   while(list != NULL)
   {

     lnode *list4 = list -> next;
     destroy_fn(list);
     destory_fn(list->ptr);
   //  free(list);
	 list = list4; 
   }
  return;
}

/* print an entire linked list                                           */
/* pq is the address of the first lnode in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an lnode in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void lnode_print(const lnode *list, void (*print_fn)(const void *))
{
   while (list != NULL) {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   } 
   // print NULL and a newline after that 
   fprintf(stdout, "NULL\n");
}
