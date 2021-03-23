#ifndef _BOOK_H_
#define _BOOK_H_
typedef int bool;
#define false 0
#define true 1
typedef struct
{
	char no[20];//ͼ���� 
	char name[20];//���� 
	char author[20];//���� 
	char press[20];//������ 
	char category[20];//��� 
	float price;//ͼ�鵥�� 
	int borrowedNums;//��ǰ������� 
	int totalBorrowedNums;//������� 
	int nums;//������ 
}BookInfo;//ͼ����Ϣ 

int check_book_by_no(char no[]);//�鿴ͼ���Ƿ����

int check_book_by_name(char name[]);

int check_book_by_author(char author[]);

void find_book();//����ͼ�� 

void add_book();//���ͼ�� 

void delete_book();//ɾ��ͼ�� 

void update_book_info();//����ͼ����Ϣ 

void print_one_book(int i);//��ӡ����ͼ����Ϣ 

void print_all_books();//��ӡ����ͼ����Ϣ 

void recommend_books();//ͼ���Ƽ� 

void print_all_borrowed_books();//��ӡ���б����ĵ�ͼ����Ϣ 

#endif
