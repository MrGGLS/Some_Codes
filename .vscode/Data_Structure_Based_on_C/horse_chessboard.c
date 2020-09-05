#include<stdio.h>
#include<time.h>
#define X 6
#define Y 6
#define OK 1
#define NO 0

int chessboard[X][Y];
int nextTry(int *x,int *y,int place);
int travelChessboard(int x,int y,int tag);
void print();

int main(){
    clock_t start, end;
    char n;
    printf("Do you wonder how to win the horse chessboard game?(y/n): ");
    scanf("%c",&n);
    if(n=='n'||n=='N')
        return 0;
    printf("Now, you should input the coodinates of the start point\n");
    int x,y;
    printf("x: ");
    scanf("%d",&x);
    printf("y: ");
    scanf("%d",&y);
    if(x<0||x>6||y<0||y>6){
        printf("Are you kidding me?\n");
        return 0;
    }
    for(int i = 0;i<X;i++)
        for(int j = 0;j<Y;j++)
            chessboard[i][j]=0;
    printf("The result is loading, please be patient~~~\n");
    start = clock();
    if(!travelChessboard(x,y,1)){
        printf("Sorry, I'm too stupid to find the answer\n");
    }else{
        printf("Hooray~~ We made it!\n");
    }
    end = clock();
    printf("It totally takes our %f seconds\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}


int nextTry(int *x,int *y,int place){
    switch(place){
        case 0:if(*x+2<X&&*y-1>=0&&chessboard[*x+2][*y-1]==0){
            *x = *x+2;
            *y = *y-1;
            return OK;
        } break;
        case 1:if(*x+2<X&&*y+1<Y&&chessboard[*x+2][*y+1]==0){
            *x = *x+2;
            *y = *y+1;
            return OK;
        } break;
        case 4:if(*x-2>=0&&*y-1>=0&&chessboard[*x-2][*y-1]==0){
            *x = *x-2;
            *y = *y-1;
            return OK;
        } break;
        case 5:if(*x-2>=0&&*y+1<Y&&chessboard[*x-2][*y+1]==0){
            *x = *x-2;
            *y = *y+1;
            return OK;
        } break;
        case 7:if(*y+2<Y&&*x-1>=0&&chessboard[*x-1][*y+2]==0){
            *y = *y+2;
            *x = *x-1;
            return OK;
        } break;
        case 3:if(*y+2<Y&&*x+1<X&&chessboard[*x+1][*y+2]==0){
            *y = *y+2;
            *x = *x+1;
            return OK;
        } break;
        case 6:if(*y-2>=0&&*x-1>=0&&chessboard[*x-1][*y-2]==0){
            *y = *y-2;
            *x = *x-1;
            return OK;
        } break;
        case 2:if(*y-2>=0&&*x+1<X&&chessboard[*x+1][*y-2]==0){
            *y = *y-2;
            *x = *x+1;
            return OK;
        } break;
        default: break;
    }
    return NO;
}

int travelChessboard(int x,int y,int tag){
    chessboard[x][y] = tag;
    //printf("%d %d %d\n",x,y,chessboard[x][y]);
    if(tag==X*Y){
        print();
        return OK;
    }

    int next_X = x;
    int next_Y = y;
    int flag = 0;
    int count = 0;

	flag = nextTry(&next_X,&next_Y,count);
	while(0==flag&&count<7){
		count++;
		flag = nextTry(&next_X,&next_Y,count);
	}
    
    while(flag){
        if(travelChessboard(next_X,next_Y,tag+1)){
            return OK;
        }
        next_X = x;
        next_Y = y;
		
		count++;
	flag = nextTry(&next_X,&next_Y,count);
	while(0==flag&&count<7){
		count++;
		flag = nextTry(&next_X,&next_Y,count);
	}
    }

    if(0==flag){
        chessboard[x][y]=0;//we should choose a new start point
    }

    return NO;//restart


}

void print(){
    for(int i = 0;i<X;i++){
        for(int j = 0;j<Y;j++){
            printf("%2d\t",chessboard[i][j]);
        }
        printf("\n");
    }
    printf("finished~\n");
}