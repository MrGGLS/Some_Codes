#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
#define MAXSIZE 10
#define STACKINCREMENT 5
typedef int ElemType;
struct Stack{
    ElemType *base;
    int top;
    int StackSize;
};

struct Stack* InitStack();//initialize a stack
void push(struct Stack *stack,ElemType e);//add a new element in the top
ElemType pop(struct Stack *stack);//remove the top element and return it
ElemType peek(struct Stack *stack);//peek the top element but dont remove it
void ShowStack(struct Stack *stack);

int main(){
    struct Stack *stack = NULL;
    stack = InitStack();
    peek(stack);
    printf("test peek()\n");
    ShowStack(stack);
    pop(stack);
    printf("test pop()\n");
    ShowStack(stack);
    push(stack,1);
    push(stack,2);
    push(stack,3);
    push(stack,4);
    push(stack,5);
    printf("test push()\n");
    ShowStack(stack);
    pop(stack);
    pop(stack);
    printf("peek():%d\n",peek(stack));
    push(stack,6);
    push(stack,7);
    pop(stack);
    ShowStack(stack);
    free(stack);
    return 0;
}

struct Stack* InitStack(){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if(!stack)
        return ERROR;
    stack->StackSize = MAXSIZE;
    stack->base = (ElemType*)malloc(MAXSIZE*sizeof(ElemType));
    if(!stack->base)
        return ERROR;
    stack->top = -1;
    return stack;
}

void push(struct Stack *stack,ElemType e){
    if(stack->top == stack->StackSize-1){
        stack->base = (ElemType*)realloc(stack->base,(STACKINCREMENT+stack->StackSize)*sizeof(ElemType));
    }
    if(!stack->base)
        return ERROR;
    stack->top++;
    stack->base[stack->top] = e;
}

ElemType pop(struct Stack *stack){
    if(stack->top == -1)
        return ERROR;
    int temp = stack->top;
    stack->top--;
    return stack->base[temp];
}

ElemType peek(struct Stack *stack){
    if(stack->top == -1)
        return ERROR;
    return stack->base[stack->top];
}

void ShowStack(struct Stack *stack){
    int temp = 0;
    while(temp<=stack->top){
        printf("%d->",stack->base[temp]);
        temp++;
    }
    printf("\n");
}