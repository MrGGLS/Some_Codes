#include"book.h"
#include"lib.h"
#include"myclock.h"
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern Library lib;
extern BookInfo books[];

int cmp(const void*a,const void*b)
{
	return ((*(BookInfo*)a).totalBorrowedNums>(*(BookInfo*)b).totalBorrowedNums)?-1:1;
}

int check_book_by_no(char no[])//查看图书是否存在
{
	for(int i=0;i<lib.booksType;i++)
		if(strcmp(no,books[i].no)==0)
			return i;
	return -1;
}

int check_book_by_name(char name[])
{
	for(int i=0;i<lib.booksType;i++)
	{
		if(strcmp(name,books[i].name)==0)
			return i;
	} 
	return -1;
}

int check_book_by_author(char author[])
{
	for(int i=0;i<lib.booksType;i++)
	{
		if(strcmp(author,books[i].author)==0)
			return i;
	} 
	return -1;
}

void find_book()//查找图书 
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t==================查找图书信息==================\n");
	printf("\t\t\t===               通过图书编号(1)            ===\n");
	printf("\t\t\t===               通过书名(2)                ===\n");
	printf("\t\t\t===               通过作者(3)                ===\n");
	printf("\t\t\t================================================\n");
	char choice=getch();
	while(choice!='1'&&choice!='2'&&choice!='3')
		choice=getch();
	system("cls"); 
	fflush(stdin);
	if(choice=='1')
	{
		char no[20];
		printf("请输入图书编号：");
		gets(no);
		int index=check_book_by_no(no);
		if(index==-1)
		{
			printf("无搜索结果，即将返回到读者界面~~~");
			time_delay(1);
			return;
		}
		else
		{
			printf("查找结果如下：\n");
			printf("图书编号            书名                作者                出版社              类别                在馆数量  总数量    图书单价\n");
			print_one_book(index);
		}
	}
	else if(choice=='2')
	{
		char name[20];
		printf("请输入书名：");
		gets(name);
		printf("查找结果如下：\n");
		printf("图书编号            书名                作者                出版社              类别                在馆数量  总数量    图书单价\n");
		int index=check_book_by_name(name);
		if(index==-1)
		{
			printf("无搜索结果，即将返回到读者界面~~~~");
			time_delay(1);
			return;
		}
	}
	else
	{
		char author[20];
		printf("请输入作者名：");
		gets(author);
		printf("查找结果如下：\n");
		printf("图书编号            书名                作者                出版社              类别                在馆数量  总数量    图书单价\n");
		int index=check_book_by_author(author);
		if(index==-1)
		{
			printf("无搜索结果，即将返回到读者界面~~~~");
			time_delay(1);
			return;
		}
	}
	printf("按任意键返回到读者界面");
	getch();
}

void add_book()//添加图书
{
	fflush(stdin);
	system("cls");
	if(lib.capacity==lib.quantity)
	{
		printf("抱歉，图书馆的藏书量已达到上限，如果您还想添加图书，请联系馆长GGLS先生。\n");
		printf("为您带来的不便，我们深感抱歉。\n\n\n");
		printf("按任意键返回到上一级菜单");
		getch();
	}
	else
	{
		char no[20];
		printf("请输入图书编号:");
		gets(no);
		char name[20];
		printf("\n请输入图书名字：");
		gets(name);
		char author[20];
		printf("\n请输入作者姓名：");
		gets(author);
		char press[20];
		printf("\n请输入出版社名：");
		gets(press);
		char category[20];
		printf("\n请输入图书类别：");
		gets(category);
		float price=0;
		printf("\n请输入图书单价：");
		scanf("%f",&price);
		int nums=0;
		printf("\n请输入添加数量：");
		while(true)
		{
			scanf("%d",&nums);
			if(nums>0)
				break;
			printf("非法输入，请再次输入图书数量：");
		} 
		while(price<1)
		{
			printf("\n单价输入有误，请重新输入图书单价：");
			fflush(stdin);
			scanf("%f",&price);	 
		}
		int index=check_book_by_no(no);
		if(index==-1)
		{
			strcpy(books[lib.booksType].no,no);
			strcpy(books[lib.booksType].name,name);
			strcpy(books[lib.booksType].author,author);
			strcpy(books[lib.booksType].press,press);
			strcpy(books[lib.booksType].category,category);
			books[lib.booksType].price=price;
			books[lib.booksType].nums+=nums;
			lib.booksType++;
			lib.quantity+=nums;
		}
		else
		{
			books[index].nums+=nums;
			lib.quantity+=nums;
		}
		printf("图书添加成功，按任意键返回到上一级菜单");
		getch();
	}
} 

void delete_book()//删除图书
{
	system("cls");
	fflush(stdin);
	char no[20];
	printf("请输入待删除图书编号：");
	gets(no);
	int index=check_book_by_no(no);
	if(index==-1)
	{ 
		printf("找不到要删除的图书，即将返回到上一级菜单~~~");
		time_delay(2);
	}
	else
	{
		if(books[index].borrowedNums==books[index].nums)
		{
			printf("删除失败，当前待删除图书已全部借出,即将返回到上一级菜单~~~");
			time_delay(2);
		}
		else
		{
			if(books[index].nums>1)
			{
				books[index].nums--;
			}
			else
			{
				int j=index+1;
				for(j;j<lib.booksType;j++)
					books[j-1]=books[j];
				lib.booksType--;
			}
			lib.quantity--;
			printf("删除成功，按任意键返回到上一级菜单");
			getch();
		}
	}
} 

void update_book_info()//更新图书信息
{
	system("cls");
	char no[20];
	printf("请先输入图书编号：");
	gets(no);
	int index=check_book_by_no(no);
	if(index==-1)
	{
		printf("此图书编号不存在，即将返回到上一级菜单");
		time_delay(2);
		return;
	}
	printf("\n\n\n\n");
	printf("\t\t\t==================更新图书信息==================\n");
	printf("\t\t\t===               更新书名(1)                ===\n");
	printf("\t\t\t===               更新作者(2)                ===\n");
	printf("\t\t\t===               更新出版社(3)              ===\n");
	printf("\t\t\t===               更新单价(4)                ===\n");
	printf("\t\t\t===               更新类别(5)                ===\n"); 
	printf("\t\t\t================================================\n");
	fflush(stdin);
	char choice;
	choice=getch();
	while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='4'&&choice!='5')
		choice=getch();
	system("cls");
	fflush(stdin);
	if(choice=='1')
	{
		char name[20];
		printf("请输入新的书名：");
		gets(name);
		strcpy(books[index].name,name);
	}
	else if(choice=='2')
	{
		char author[20];
		printf("请输入新的作者名：");
		gets(author);
		strcpy(books[index].author,author);
	}
	else if(choice=='3')
	{
		char press[20];
		printf("请输入新的出版社：");
		gets(press);
		strcpy(books[index].press,press);
	}
	else if(choice=='4')
	{
		float price=0;
		printf("请输入新的单价：");
		fflush(stdin);
		scanf("%f",&price);
		while(price<=0)
		{
			printf("输入的单价有误，请重新输入单价：");
			fflush(stdin);
			scanf("%f",&price);
		}
		books[index].price=price;
	}
	else
	{
		char category[20];
		printf("请输入新的类别：");
		gets(category);
		strcpy(books[index].category,category);
	}
	system("cls");
	printf("修改成功，按任意键返回到上一级菜单");
	getch();
} 

void print_one_book(int i)//打印单本图书信息 
{
	printf("%-20s%-20s%-20s%-20s%-20s%-10d%-10d%-10.2f\n",books[i].no,books[i].name,books[i].author,books[i].press,books[i].category,books[i].nums-books[i].borrowedNums,books[i].nums,books[i].price);
}

void print_all_books()//打印所有图书信息 
{
	system("cls");
	printf("==================================================================================================================================\n");
	printf("图书编号            书名                作者                出版社              类别                在馆数量  总数量    图书单价\n");
	for(int i=0;i<lib.booksType;i++)
		print_one_book(i);
	printf("按任意键返回到上一级菜单");
	getch();
}

void recommend_books()//图书推荐
{
	system("cls");
	if(lib.booksType==0)
	{
		printf("抱歉，本馆占无藏书");
	}
	else
	{
		printf("===================================================本馆最受欢迎图书榜=============================================================\n");
		printf("图书编号            书名                作者                出版社              类别                在馆数量  总数量    图书单价\n");
		qsort(books,lib.booksType,sizeof(BookInfo),cmp);
		for(int i=0;i<10&&i<lib.booksType;i++)
			print_one_book(i);
	}
	printf("按任意键返回到上一级菜单");
	fflush(stdin);
	getch();
} 

void print_all_borrowed_books()//打印所有被借阅的图书信息
{
	system("cls");
	printf("=====================================================目前被借阅的图书=============================================================\n");
	printf("图书编号            书名                作者                出版社              类别                在馆数量  总数量    图书单价\n");
	for(int i=0;i<lib.booksType;i++)
	{
		if(books[i].borrowedNums>0)
			print_one_book(i);
	}
	printf("按任意键返回到上一级菜单");
	getch();
}
