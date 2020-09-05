#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
#define MAXSIZE 66
typedef char ElemType;
typedef struct{
    int indexOfChild;
    struct Knode *next;
}*KNode;

typedef struct{
    ElemType data;
    int indexOfParent;
    KNode firstKid;
}NBox;

typedef struct{
    NBox nodes[MAXSIZE];
    int r,n;
}PKTree;

int main(){
    PKTree pKTree;
    pKTree.nodes[MAXSIZE];
    pKTree.r=0;
    pKTree.n=11;
    return 0;
}
