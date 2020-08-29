#include<stdio.h>
#include<stdlib.h>
int main(){ 
    int *x;
    int val = 100;
    x = &val;
    printf("%d\n",*x);
    free(x);
    printf("%d\n",*x);

}