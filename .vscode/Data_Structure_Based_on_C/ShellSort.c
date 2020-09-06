#include<stdio.h>
#include<stdlib.h>
#define MAX 100005
int a[MAX];
void ShellSort()
 {
     int i,j;
     int temp;
     int increment;
 
     for( increment=MAX/2; increment>0; increment/=2){
         for( i=increment; i<MAX; i++){
             if(a[i-1]>a[i]){
                temp = a[i];   
                for( j=i-increment;  j>=0&&temp<a[j] ; j-=increment)//can't be written as tempa[j]&&j>=0(stackoverflow!!!)
                    a[ j+increment ] = a[j];
                    a[ j+increment ] = temp;
             }
         }
     }
 }