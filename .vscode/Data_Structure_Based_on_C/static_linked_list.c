#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000
#define ERROR -1
typedef int ElemType;
typedef struct{
    ElemType data;
    int cur;
}Component,StaticLinkedList[MAXSIZE];

StaticLinkedList* InitList();//initialize list
int Malloc_SLL(StaticLinkedList *list);//get free cursor
void InsertNode(StaticLinkedList *list, int i, ElemType e);//insert new node
int ListLength(StaticLinkedList list);//get length of this list
void ShowList(StaticLinkedList list);//printf all elements of this list
void DeleteNode(StaticLinkedList *list,int i);//delete a node by index and release the space 
void AddNode(StaticLinkedList *list, ElemType e);//add a new node at the end

int main(){
    StaticLinkedList *list = NULL;
    list = InitList();
    printf("=================\n");
    ShowList(list);
    AddNode(list,1);
    AddNode(list,5);
    AddNode(list,7);
    AddNode(list,9);
    printf("test AddNode()\n");
    ShowList(list);
    free(list);
    return 0;
}

StaticLinkedList* InitList(){
    StaticLinkedList *list = (StaticLinkedList*)malloc(sizeof(StaticLinkedList));
    for(int i = 0;i<MAXSIZE-1;i++){
        list[i]->cur = i+1;
    }
    list[MAXSIZE-1]->cur = 0;
    return list;
}

int Malloc_SLL(StaticLinkedList *list){
    int i = list[0]->cur;
    if(list[0]->cur){
        list[0]->cur = list[i]->cur;
    }
    return i;
}

void InsertNode(StaticLinkedList *list, int i, ElemType e){
    if(i<1||i>ListLength(list))
        return ERROR;
    int j = Malloc_SLL(list);
    if(j){
        list[j]->data = e;
        int k = MAXSIZE - 1;
        for(int l = 1;l<i;l++){
            k = list[k]->cur;
        }
        list[j]->cur = list[k]->cur;
        list[k]->cur = j;
    }
    return ERROR;
}

int ListLength(StaticLinkedList list){
    Component temp = list[MAXSIZE-1];
    int len = 0;
    while(temp.cur){
        len++;
        temp = list[temp.cur];
    }
    return len;
}

void ShowList(StaticLinkedList list){
    Component temp = list[MAXSIZE-1];
    while(temp.cur){
        temp = list[temp.cur];
        printf("%d->",temp.data);
    }
    printf("\n");
}

void DeleteNode(StaticLinkedList *list,int i){
    if(i<1||i>ListLength(list))
        return ERROR;
    int j = MAXSIZE-1;
    for(int l = 1;l<i;l++){
        j = list[j]->cur;
    }
    int k = list[j]->cur;
    list[j]->cur = list[k]->cur;
    list[k]->cur = list[0]->cur;
    list[0]->cur = k;
}

void AddNode(StaticLinkedList *list, ElemType e){
    if(ListLength(list)>=MAXSIZE-1)
        return ERROR;
    int i = list[0]->cur;
    list[i]->data = e;
    list[0]->cur = list[i]->cur;
    list[i]->cur = 0;
    if(!ListLength(list)){
        list[MAXSIZE-1]->cur = i;
    }
}