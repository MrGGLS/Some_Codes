#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
typedef char ElemType;
typedef struct BTNode{
    ElemType data;
    struct BTNode *lchild,*rchild;
}BTNode,*BTree;


void CreateTree(BTree *T);
void ShowNode(char data);
void PreOrderTraverse(BTree T);

int main(){
    BTree T=NULL;
    CreateTree(&T);
    PreOrderTraverse(T);
    return 0;
}

void CreateTree(BTree *T){
    char name;
    scanf("%c",&name);
    if(name==' ')
        *T=NULL;
    else{
        *T=(BTNode*)malloc(sizeof(BTNode));
        (*T)->data=name;
        CreateTree(&(*T)->lchild);
        CreateTree(&(*T)->rchild);
    }
}

void ShowNode(char data){
    printf("%c->",data);
}

void PreOrderTraverse(BTree T){
    if(T){
        ShowNode(T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}



