#include<stdio.h>
#define MAXSIZE 10

void Merging(int *left_a,int left_a_size,int *right_a,int right_a_size){
	int i,j,k,l;
	i = j = k = l = 0;
	int temp[MAXSIZE];
	while(i<left_a_size&&j<right_a_size){
		if(left_a[i]<right_a[j]){
			temp[k++]=left_a[i++];
		}else{
			temp[k++]=right_a[j++];
		}
	}
	while(i<left_a_size)
		temp[k++]=left_a[i++];
	while(j<right_a_size)
		temp[k++]=right_a[j++];
	for(l;l<(left_a_size+right_a_size);l++)
		left_a[l]=temp[l];
	
}

void MergeSort(int a[],int n){
	if(n>1){
    int *left_a = a;
	int left_a_size = n/2;
	int *right_a = left_a_size+a;
	
	MergeSort(left_a,left_a_size);
	MergeSort(right_a,n-left_a_size);
	Merging(left_a,left_a_size,right_a,n-left_a_size);	
	}	
}