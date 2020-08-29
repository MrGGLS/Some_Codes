#include<stdio.h>
#include<stdlib.h>

int reverse(int x){
    int flag = 0;
    if(x<0){
        flag = 1;
        x = -x;
    }
    long res = 0;
    while(x/10!=0){
        res+=x%10;
        x/=10;
        res*=10;
        printf("res:%d\n",res);
    }
    res+=x;
    if(res>2147483647||res<-2147483647)
        return 0;
    if(flag == 1){
        return -res;
    }else
        return res;
}
int main(){ 
    printf("%ld",reverse(1534236459));

}