typedef struct _storenode{

  long int *num;
  int *chr;
  int *total;
}storenode;

typedef struct _tnode{
  struct _tnode *left;
  struct _tnode *right;
  int tchr;
  long int tnum;
}tnode;


typedef struct _realnode{

  struct _realnode *next;
  tnode *callt;
}realnode;

storenode *firstcall(FILE *fptr, FILE *fptr2);
void secondcall(realnode **head, storenode *list,FILE *fptr3);
void lastcall(realnode **head, FILE *fptr4);


realnode *PQ_enq(realnode **head, tnode *new_tree);

void put_tree(realnode **head);
realnode *stack_pop(realnode **head);
tnode *tree_merge(realnode *tn1, realnode *tn2);
void encode_tree(tnode *tree,char path[], int index, FILE *fptr4);

void free_all_store(storenode *list);
void destroy_tree(tnode *head);
void link_destroy(realnode *list);
//void *destroy_fn(void *varf);
