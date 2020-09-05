#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
typedef char ElemType;
typedef enum{Link,Thread} PointerTag;
typedef struct TBNode{
    char data;
    struct TBNode *lchild,*rchild;
    int ltag;
    int rtag;
} TBNode,*TBTree;

int main(){
    
    return 0;
}