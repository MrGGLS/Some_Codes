#include<stdio.h>
#include<stdlib.h>
#define ERROR
#define OK
typedef int ElemType;
typedef struct{
    ElemType data;
    struct DualNode *prior;
    struct DualNode *next;
}DualNode;
// double linked list is quite similar with linked list, so I just
// implement some functions
DualNode* InitNode();
void InsertNode(DualNode *head, int i , ElemType e);
void DeleteNode(DualNode *head, int i);
void AddNode(DualNode *head, ElemType e);
int GetLength(DualNode *head);
void ShowList(DualNode *head);

int main(){
    DualNode *head = InitNode();
    AddNode(head, 1);
    AddNode(head, 3);
    AddNode(head, 5);
    AddNode(head, 7);
    AddNode(head, 9);
    printf("test AddNode()\n");
    ShowList(head);
    InsertNode(head,1,10);
    InsertNode(head,6,60);
    InsertNode(head,3,30);
    printf("test InsertNode()\n");
    ShowList(head);
    DeleteNode(head,1);
    DeleteNode(head,4);
    DeleteNode(head,6);
    printf("test DeleteNode()\n");
    ShowList(head);
    
    return 0;
}

DualNode* InitNode(){
    DualNode * node = (DualNode*)malloc(sizeof(DualNode));
    node->data = 0;
    node->next = NULL;
    node->prior = NULL;
}

void InsertNode(DualNode *head,int i,ElemType e){
        if(head==NULL||i<1||i>GetLength(head)){
            return ERROR;
        }
        int j = 1;
        DualNode* p = head;
        for(j;j<i;j++){
            p = p->next;
        }
        DualNode *q = p;
        DualNode *r = p->next;
        DualNode *temp = InitNode();
        temp->data = e;
        temp->next = r;
        temp->prior = p;
        p->next  =temp;
        r->prior = temp;
}

void DeleteNode(DualNode *head, int i){
    if(head==NULL||i<1||i>GetLength(head)){
        return ERROR;
    }
    int j = 1;
    DualNode *p = head;
    for(j;j<i;j++){
        p = p->next;
    }
    DualNode *q = p->next;
    if(q->next==NULL){
        p->next = NULL;
        free(q);
        return OK;
    }
    DualNode *r = q->next;
    p->next = r;
    r->prior = p;
    free(q);
}

void AddNode(DualNode *head, ElemType e){
    DualNode *p = head;
    while(p->next){
        p = p->next;
    }
    DualNode *q = InitNode();
    q->data = e;
    p->next = q;
    q->prior = p;
}

int GetLength(DualNode *head){
    if(head==NULL){
        return ERROR;
    }
    DualNode *p = head->next;
    int count = 0;
    while(p){
        count++;
        p = p->next;
    }
    return count;
}

void ShowList(DualNode *head){
    if(head==NULL){
        return ERROR;
    }
    DualNode *p = head->next;
    while(p){
        printf("%d->",p->data);
        p = p->next;
    }
    printf("\n");
}