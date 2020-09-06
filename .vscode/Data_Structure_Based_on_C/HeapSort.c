#include<stdio.h>

void swap(int a[],int i,int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void HeapAjust(int a[],int i,int j){

    int temp = a[i];
    for(int k = i*2;k<j;k*=2){
        if(k<j&&a[k]<a[k+1])
            k++;
        if(temp>=a[k])
            break;
        a[i]=a[k];
        i=k;
    }
    a[i]=temp;
}

void HeapSort(int a[],int n){

    for(int i = n/2;i>0;i--){
        HeapAjust(a,i,n);
    }

    for(int j = n;j>1;j--){
        swap(a,1,j);
        HeapAjust(a,1,j-1);
    }

}
