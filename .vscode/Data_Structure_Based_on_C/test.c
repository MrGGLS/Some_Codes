#include<stdio.h>
#include<stdlib.h>
int isValid(char s[]);
int main(){ 
    char s[] = "){";
    printf("%d",isValid(s));
    }

 int isValid(char s[]) {
        int len = strlen(s);
        printf("len:%d\n",len);
        if((len%2!=0)||(len==0)){
            return 0;
        }
        int p = -1;
        int intS[2];
        for(int i = 0;i<len;i++){
            intS[i]=0;
        }
        int j = 0;
        for(int i = 0;i<len;i++){
            if(s[i]=='('){
                intS[j]=1;
                j++;
                p++;
            }
            if(s[i]=='['){
                intS[j]=2;
                j++;
                p++;
            }
            if(s[i]=='{'){
                intS[j]=3;
                j++;
                p++;
            }
            if(s[i]==')'){
                if(intS[p]==1){
                    s[p]=0;
                    p--;
                    j--;
                   
                }else{
                    return 0;
                }
            }
            if(s[i]==']'){
                if(intS[p]==2){
                    s[p]=0;
                    
                    p--;
                    j--;
                   
                }else{
                    return 0;
                }
            }
            if(s[i]=='}'){
                if(intS[p]==3){
                    s[p]=0;
                    
                    p--;
                    j--;
                }else{
                    return 0;
                }
            }
        }
        if(p==-1)
            return 1;
        return 0;
    }