#include<stdio.h>
#define MAXSIZE 1000
typedef char ElemType;
typedef struct{
    char parent;
    ElemType data;
}Tnode;

typedef struct{
    Tnode nodes[MAXSIZE];
    int numsOfNodes;
    int root;
}PTree;