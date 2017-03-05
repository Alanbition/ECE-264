#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer09.h"

//Declare functions
static int int_cmp(const void *p1, const void *p2);
static int string_cmp(const void *p1, const void *p2);
static void int_print(const void *ptr);
static void char_print(const void *ptr);
static void string_print(const void *ptr);
void destroy_fn(void *);

int main(int argc, char*argv[])
{	
	lnode *list = NULL;
	int ptr[] = {5, 10, 4, 3, 1};
	int ptr2[] = {7};

	int i;
	for (i = 0; i < 5; i++){
		PQ_enqueue(&list, &ptr[i], int_cmp);
	}
	lnode_print(list, int_print);

	stack_push(&list, &ptr2[0]);
	lnode_print(list, int_print);

	lnode *node1 = stack_pop(&list);
	lnode_print(list, int_print);

	lnode *node2 = lnode_remove_last(&list);
	lnode_print(list, int_print);
	
	lnode *node3 = PQ_dequeue(&list);
	lnode_print(list, int_print);

	lnode_destroy(list, destroy_fn);
	lnode_destroy(node1, destroy_fn);
	lnode_destroy(node2, destroy_fn);
	lnode_destroy(node3, destroy_fn);

	lnode * list2 = NULL;
	char ptr3[] = {'a', 'c', 'b', 'd', 'A', 'C', 'D', '1'};
	char ptr4 [] = {'T'};

	int j;
	for (j = 0; j < 8; j++){
		PQ_enqueue(&list2, &ptr3[j], string_cmp);
	}
	lnode_print(list2, char_print);

	stack_push(&list2, &ptr4[0]);
	lnode_print(list2, char_print);

	lnode *node4 = stack_pop(&list2);
	lnode_print(list2, char_print);

	lnode *node5 = lnode_remove_last(&list2);
	lnode_print(list2, char_print);

	lnode *node6 = PQ_dequeue(&list2);
	lnode_print(list2, char_print);

	lnode_destroy(list2, destroy_fn);
	lnode_destroy(node4, destroy_fn);
	lnode_destroy(node5, destroy_fn);
	lnode_destroy(node6, destroy_fn);

	lnode *list3 = NULL;

	char *ptr5[] = {"Ohio", "Texas", "Indiana", "California"};
	char *ptr6[] = {"Florida"};

	int k;
	for (k = 0; k < 4; k++){
		PQ_enqueue(&list3, ptr5[k], string_cmp);
	}
	lnode_print(list3, string_print);

	stack_push(&list3, ptr6[0]);
	lnode_print(list3, string_print);

	lnode *node7 = stack_pop(&list3);
	lnode_print(list3, string_print);

	lnode *node8 = lnode_remove_last(&list3);
	lnode_print(list3, string_print);

	lnode *node9 = PQ_dequeue(&list3);
	lnode_print(list3, string_print);

	lnode_destroy(list3, destroy_fn);
	lnode_destroy(node7, destroy_fn);
	lnode_destroy(node8, destroy_fn);
	lnode_destroy(node9, destroy_fn);


	return EXIT_SUCCESS;
}

static int int_cmp(const void *p1, const void *p2)
{
   return *(const int *)p1 - *(const int *)p2;
}

static int string_cmp(const void *p1, const void *p2)
{
   return strcmp((const char *)p1, (const char *)p2);
}

static void int_print(const void *ptr)
{
   printf("%d", *(const int *)ptr);
}

static void char_print(const void *ptr)
{
   printf("%c", *(const char *)ptr);
}

static void string_print(const void *ptr)
{
   printf("%s", (const char *)ptr);
}

void destroy_fn(void * var)
{
	
	return;
}
