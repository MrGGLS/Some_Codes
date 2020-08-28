#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
#define ERROR -1
typedef struct{
    ElemType data;
    struct node *next;
}node;

node* InitNode();//initialize node
void AddNode(node* head, ElemType e);//add a new node in end
void InsertNode(node* head, int i, ElemType e);//insert a new node in appointed place
void DeleteNode(node* head, int i);//delete node by index
void ShowList(node* head);//print all elements in this list
ElemType GetElem(node* head, int i);//get data by index


int main(){
    node* head = InitNode();
    AddNode(head, 1);
    AddNode(head, 2);
    AddNode(head, 3);
    AddNode(head, 4);
    AddNode(head, 5);
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
    printf("test GetElem()\n");
    printf("%d\n",GetElem(head,1));
    printf("%d\n",GetElem(head,3));
    printf("%d\n",GetElem(head,5));
    return 0;
}

node* InitNode(){
   
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = 0;
    newNode->next = NULL;
    return newNode;
}

void AddNode(node* head, ElemType e){
    if(head == NULL)
        return ERROR;    
    node *p = head;
    node *q = InitNode();
    q->data = e;
    while(p->next!=NULL){
        p = p->next;
    }
    p->next = q;
}

void InsertNode(node* head, int i, ElemType e){
    if(head == NULL)
        return ERROR;
    node *p = head;
    int j = 1;
    while(p->next!=NULL&&j<i){
        p = p->next;
        j++;
    }
    if(p->next==NULL)
        return ERROR;
    node *q = InitNode();
    q->data = e;
    q->next = p->next;
    p->next = q;
}

void DeleteNode(node* head, int i){
    if(head==NULL)
        return ERROR;
    node *p = head;
    int j = 1;
    while(p->next!=NULL&&j<i){
        p = p->next;
        j++;
    }
    if(p->next==NULL)
        return ERROR;
    node *temp = p->next;
    if(temp->next==NULL){
        free(temp);
        p->next = NULL;
    }else{
        p->next = temp->next;
       // temp->next = NULL;
        free(temp);
    }
}

void ShowList(node* head){
    if(head==NULL)
        return ERROR;
    node *p = head->next;
    while(p->next!=NULL){
        printf("%d->",p->data);
        p = p->next;
    }
    printf("%d",p->data);
    printf("\n");
}

ElemType GetElem(node* head, int i){
    int j = 1;
    if(head->next==NULL)
        return ERROR;
    node* p = head->next;
    while(p->next!=NULL&&j<i){
        p = p->next;
        j++;
    }
    if(j==i){
        return p->data;
    }else{
        return ERROR;
    }
}



