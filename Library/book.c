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

int check_book_by_no(char no[])//�鿴ͼ���Ƿ����
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

void find_book()//����ͼ�� 
{
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t==================����ͼ����Ϣ==================\n");
	printf("\t\t\t===               ͨ��ͼ����(1)            ===\n");
	printf("\t\t\t===               ͨ������(2)                ===\n");
	printf("\t\t\t===               ͨ������(3)                ===\n");
	printf("\t\t\t================================================\n");
	char choice=getch();
	while(choice!='1'&&choice!='2'&&choice!='3')
		choice=getch();
	system("cls"); 
	fflush(stdin);
	if(choice=='1')
	{
		char no[20];
		printf("������ͼ���ţ�");
		gets(no);
		int index=check_book_by_no(no);
		if(index==-1)
		{
			printf("������������������ص����߽���~~~");
			time_delay(1);
			return;
		}
		else
		{
			printf("���ҽ�����£�\n");
			printf("ͼ����            ����                ����                ������              ���                �ڹ�����  ������    ͼ�鵥��\n");
			print_one_book(index);
		}
	}
	else if(choice=='2')
	{
		char name[20];
		printf("������������");
		gets(name);
		printf("���ҽ�����£�\n");
		printf("ͼ����            ����                ����                ������              ���                �ڹ�����  ������    ͼ�鵥��\n");
		int index=check_book_by_name(name);
		if(index==-1)
		{
			printf("������������������ص����߽���~~~~");
			time_delay(1);
			return;
		}
	}
	else
	{
		char author[20];
		printf("��������������");
		gets(author);
		printf("���ҽ�����£�\n");
		printf("ͼ����            ����                ����                ������              ���                �ڹ�����  ������    ͼ�鵥��\n");
		int index=check_book_by_author(author);
		if(index==-1)
		{
			printf("������������������ص����߽���~~~~");
			time_delay(1);
			return;
		}
	}
	printf("����������ص����߽���");
	getch();
}

void add_book()//���ͼ��
{
	fflush(stdin);
	system("cls");
	if(lib.capacity==lib.quantity)
	{
		printf("��Ǹ��ͼ��ݵĲ������Ѵﵽ���ޣ�������������ͼ�飬����ϵ�ݳ�GGLS������\n");
		printf("Ϊ�������Ĳ��㣬������б�Ǹ��\n\n\n");
		printf("����������ص���һ���˵�");
		getch();
	}
	else
	{
		char no[20];
		printf("������ͼ����:");
		gets(no);
		char name[20];
		printf("\n������ͼ�����֣�");
		gets(name);
		char author[20];
		printf("\n����������������");
		gets(author);
		char press[20];
		printf("\n���������������");
		gets(press);
		char category[20];
		printf("\n������ͼ�����");
		gets(category);
		float price=0;
		printf("\n������ͼ�鵥�ۣ�");
		scanf("%f",&price);
		int nums=0;
		printf("\n���������������");
		while(true)
		{
			scanf("%d",&nums);
			if(nums>0)
				break;
			printf("�Ƿ����룬���ٴ�����ͼ��������");
		} 
		while(price<1)
		{
			printf("\n����������������������ͼ�鵥�ۣ�");
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
		printf("ͼ����ӳɹ�������������ص���һ���˵�");
		getch();
	}
} 

void delete_book()//ɾ��ͼ��
{
	system("cls");
	fflush(stdin);
	char no[20];
	printf("�������ɾ��ͼ���ţ�");
	gets(no);
	int index=check_book_by_no(no);
	if(index==-1)
	{ 
		printf("�Ҳ���Ҫɾ����ͼ�飬�������ص���һ���˵�~~~");
		time_delay(2);
	}
	else
	{
		if(books[index].borrowedNums==books[index].nums)
		{
			printf("ɾ��ʧ�ܣ���ǰ��ɾ��ͼ����ȫ�����,�������ص���һ���˵�~~~");
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
			printf("ɾ���ɹ�������������ص���һ���˵�");
			getch();
		}
	}
} 

void update_book_info()//����ͼ����Ϣ
{
	system("cls");
	char no[20];
	printf("��������ͼ���ţ�");
	gets(no);
	int index=check_book_by_no(no);
	if(index==-1)
	{
		printf("��ͼ���Ų����ڣ��������ص���һ���˵�");
		time_delay(2);
		return;
	}
	printf("\n\n\n\n");
	printf("\t\t\t==================����ͼ����Ϣ==================\n");
	printf("\t\t\t===               ��������(1)                ===\n");
	printf("\t\t\t===               ��������(2)                ===\n");
	printf("\t\t\t===               ���³�����(3)              ===\n");
	printf("\t\t\t===               ���µ���(4)                ===\n");
	printf("\t\t\t===               �������(5)                ===\n"); 
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
		printf("�������µ�������");
		gets(name);
		strcpy(books[index].name,name);
	}
	else if(choice=='2')
	{
		char author[20];
		printf("�������µ���������");
		gets(author);
		strcpy(books[index].author,author);
	}
	else if(choice=='3')
	{
		char press[20];
		printf("�������µĳ����磺");
		gets(press);
		strcpy(books[index].press,press);
	}
	else if(choice=='4')
	{
		float price=0;
		printf("�������µĵ��ۣ�");
		fflush(stdin);
		scanf("%f",&price);
		while(price<=0)
		{
			printf("����ĵ����������������뵥�ۣ�");
			fflush(stdin);
			scanf("%f",&price);
		}
		books[index].price=price;
	}
	else
	{
		char category[20];
		printf("�������µ����");
		gets(category);
		strcpy(books[index].category,category);
	}
	system("cls");
	printf("�޸ĳɹ�������������ص���һ���˵�");
	getch();
} 

void print_one_book(int i)//��ӡ����ͼ����Ϣ 
{
	printf("%-20s%-20s%-20s%-20s%-20s%-10d%-10d%-10.2f\n",books[i].no,books[i].name,books[i].author,books[i].press,books[i].category,books[i].nums-books[i].borrowedNums,books[i].nums,books[i].price);
}

void print_all_books()//��ӡ����ͼ����Ϣ 
{
	system("cls");
	printf("==================================================================================================================================\n");
	printf("ͼ����            ����                ����                ������              ���                �ڹ�����  ������    ͼ�鵥��\n");
	for(int i=0;i<lib.booksType;i++)
		print_one_book(i);
	printf("����������ص���һ���˵�");
	getch();
}

void recommend_books()//ͼ���Ƽ�
{
	system("cls");
	if(lib.booksType==0)
	{
		printf("��Ǹ������ռ�޲���");
	}
	else
	{
		printf("===================================================�������ܻ�ӭͼ���=============================================================\n");
		printf("ͼ����            ����                ����                ������              ���                �ڹ�����  ������    ͼ�鵥��\n");
		qsort(books,lib.booksType,sizeof(BookInfo),cmp);
		for(int i=0;i<10&&i<lib.booksType;i++)
			print_one_book(i);
	}
	printf("����������ص���һ���˵�");
	fflush(stdin);
	getch();
} 

void print_all_borrowed_books()//��ӡ���б����ĵ�ͼ����Ϣ
{
	system("cls");
	printf("=====================================================Ŀǰ�����ĵ�ͼ��=============================================================\n");
	printf("ͼ����            ����                ����                ������              ���                �ڹ�����  ������    ͼ�鵥��\n");
	for(int i=0;i<lib.booksType;i++)
	{
		if(books[i].borrowedNums>0)
			print_one_book(i);
	}
	printf("����������ص���һ���˵�");
	getch();
}
