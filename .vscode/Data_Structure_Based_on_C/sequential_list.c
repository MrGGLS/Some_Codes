#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10000
#define TRUE 1
#define FALSE 0
#define ERROR -1
typedef int ElemType;
typedef struct
{
    ElemType *data;
    ElemType length;
    int Capacity;
}sequential_list;

void Initlist(sequential_list *list);//initialize list

int DestroyList(sequential_list *list);//if succeed return 1 else return -1

void ClearList(sequential_list *list);//remove all elements of this list

int ListEmpty(sequential_list *list);//to see if this list is empty

int ListLength(sequential_list *list);//get length

ElemType GetELem(sequential_list *list,int i);//get element through index

int LocateELem(sequential_list *list,ElemType elem);//get index through element

int PriorELem(sequential_list *list,ElemType cur_e);//get index of current element's prior element

int NextELem(sequential_list *list,ElemType cur_e);//get index of current elemtnt's next element

void ListInsert(sequential_list *list,int i, ElemType e);//insert a new element

void ListDelete(sequential_list *list,int i);//delete a element through index

void UnionL(sequential_list *l1,sequential_list l2);//add l2's elements to l1, however, cannot add same element!

void MergeList(sequential_list l1,sequential_list l2,sequential_list *l3);//merge l1 and l2 to l3,l1 and l2 should be sorted

int BinarySearch(sequential_list *list,ElemType e,int left,int right);//if your list is sorted, this method will works

void ShowList(sequential_list list);//print all elements in this list

void AddElement(sequential_list *list,ElemType e);//add a new element

void Resize(sequential_list *list,double times);//expansion and reduction of list


int main(){
    sequential_list list1,list2;
    Initlist(&list1);
    Initlist(&list2);
    ShowList(list1);
    AddElement(&list1,1);
    AddElement(&list1,3);
    AddElement(&list1,5);
    AddElement(&list1,7);
    AddElement(&list1,9);
    ShowList(list1);
    AddElement(&list2,2);
    AddElement(&list2,4);
    AddElement(&list2,6);
    AddElement(&list2,8);
    ShowList(list2);
    sequential_list list3;
    printf("test MergeList()\n");
    Initlist(&list3);
    MergeList(list1,list2,&list3);
    ShowList(list3);
    printf("test UnionL()\n");
    sequential_list list4;
    Initlist(&list4);
    AddElement(&list4,1);
    AddElement(&list4,3);
    AddElement(&list4,5);
    AddElement(&list4,6);
    AddElement(&list4,8);
    UnionL(&list1,list4);
    ShowList(list1);
    printf("test insert\n");
    ListInsert(&list2,2,3);
    ListInsert(&list2,1,-3);
    ListInsert(&list2,ListLength(&list2),100);
    ShowList(list2);
    printf("test delete\n");
    ListDelete(&list2,1);
    ListDelete(&list2,ListLength(&list2));
    ShowList(list2);
    return 0;
}

void Initlist(sequential_list *list){
    list->length = 0;
    list->Capacity=3;
    list->data = (ElemType*)malloc((list->Capacity)*sizeof(ElemType));
}

int DestroyList(sequential_list *list){
    list = NULL;
    if (list==NULL)
    {
        return TRUE;
    }else{
        return FALSE;
    }
}

void ClearList(sequential_list *list){
    if(list!=NULL){
    for (int i = 0; i < list->length; i++)
        {
            list->data[i]=0;
        }
        list->length=0;
    }
   
    
}

int ListEmpty(sequential_list *list){
    if (list==NULL)
    {
        return ERROR;
    }
    
    if (list->length==0)
    {
       return TRUE;
    }else 
    {
       return FALSE;
    }
}

int ListLength(sequential_list *list){
    if(list!=NULL)
        return list->length;
    return ERROR;
}

ElemType GetELem(sequential_list *list,int i){
    if(i<1||i>list->length||list==NULL){
        return ERROR;
    }else{
        return list->data[i-1];
    }
}

int LocateELem(sequential_list *list,ElemType elem){
    if(list!=NULL){
        for(int i = 0; i<list->length;i++){
            if (list->data[i]==elem)
            {
                return i+1;
            }           
        }
    }
    return ERROR;
}
int PriorELem(sequential_list *list,ElemType cur_e){
    if(list!=NULL){
        for (int i = 0; i < list->length; i++)
        {
            if (cur_e == list->data[i]&&i>0)
            {
                return i;
            }
            
        }
        return ERROR;
    }
    return ERROR;
}

int NextELem(sequential_list *list,ElemType cur_e){
    if(list!=NULL){
        for(int i = 0; i < list->length;i++){
            if(cur_e == list->data[i]&&i<list->length-1){
                return i+2;
            }
        }
        return ERROR;
    }
    return ERROR;
}

void ListInsert(sequential_list *list,int i, ElemType e){
    if (list==NULL||i<1||i>list->length+1)
    {
        return ERROR;
    }
    if(list->length+1>=MAXSIZE){
        printf("you can't insert more data");
        return ERROR;
    }
    if(list->length+1>list->Capacity){
    do{
        Resize(list,2);
    }while(list->length+1>list->Capacity);
    }
    list->length++;
    for(int k = list->length-1;k>=i;k--)
        list->data[k] = list->data[k-1];
    list->data[i-1] = e;    
}

void ListDelete(sequential_list *list,int i){
    if(list==NULL||i<1||i>list->length){
        return ERROR;
    }
    for(int k = i-1;k<list->length-1;k++){
        list->data[k] = list->data[k+1];
    }
    list->length--;
    if(list->Capacity>list->length*2){
        Resize(list,0.5);
    }
}

void UnionL(sequential_list *l1,sequential_list l2){
    int len1 = l1->length;
    int len2 = l2.length;
    for(int i = 0; i<l2.length;i++){
        int flag = LocateELem(l1,l2.data[i]);
        if(flag==ERROR){
            AddElement(l1,l2.data[i]);
        }
    }
}

void MergeList(sequential_list l1,sequential_list l2,sequential_list *l3){
    Initlist(l3);
    int i = 1;
    int j = 1;
    int k = 0;
    int len_l1 = l1.length;
    int len_l2 = l2.length;
    while(i<=len_l1&&j<=len_l2){
        ElemType ai = GetELem(&l1,i);
        ElemType bj = GetELem(&l2,j);
        if(ai<=bj){
            ListInsert(l3,++k,ai);
            i++;
        }else{
            ListInsert(l3,++k,bj);
            j++;
        }
    }
    while(i<=len_l1){
        ListInsert(l3,++k,GetELem(&l1,i));
        i++;
    }
    while(j<=len_l2){
        ListInsert(l3,++k,GetELem(&l2,j));
    }
    
}

int BinarySearch(sequential_list *list,ElemType e,int left,int right){
    if(left>right)
        return ERROR;
    int mid = (left+right)/2;
    ElemType ai = list->data[mid];
    if(ai==e){
        return mid+1;
    }
    if(ai<e){
       return BinarySearch(&list,e,mid+1,right);
    }
    if(ai>e){
       return BinarySearch(&list,e,left,mid-1);
    }
}

void ShowList(sequential_list list){ 
    int i = 0;
    int len = list.length;
    printf("all elements of this list: ");
    for(i; i<len;i++){
        printf("%d ",list.data[i]);
    }
    printf("\n");
}

void AddElement(sequential_list *list,ElemType e){
    if(list==NULL){
        return ERROR;
    }
    if(list->length+1>MAXSIZE){
        printf("you cannot add more data");
        return ERROR;
    }
    if(list->length+1>list->Capacity){
        do{
            Resize(list,2);
        }while(list->length+1>list->Capacity);
    }
    list->data[list->length] = e;
    list->length++;
}

void Resize(sequential_list *list,double times){
    ElemType *newData = (ElemType*)malloc(((int)list->Capacity*times)*sizeof(ElemType));
    for (int i = 0; i < list->length; i++)
    {
       newData[i]=list->data[i];
    }
    list->Capacity = (int)times*list->Capacity;
    free(list->data);
    list->data = newData;
}




