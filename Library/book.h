#ifndef _BOOK_H_
#define _BOOK_H_
typedef int bool;
#define false 0
#define true 1
typedef struct
{
	char no[20];//图书编号 
	char name[20];//书名 
	char author[20];//著者 
	char press[20];//出版社 
	char category[20];//类别 
	float price;//图书单价 
	int borrowedNums;//当前借出数量 
	int totalBorrowedNums;//借出次数 
	int nums;//总数量 
}BookInfo;//图书信息 

int check_book_by_no(char no[]);//查看图书是否存在

int check_book_by_name(char name[]);

int check_book_by_author(char author[]);

void find_book();//查找图书 

void add_book();//添加图书 

void delete_book();//删除图书 

void update_book_info();//更新图书信息 

void print_one_book(int i);//打印单本图书信息 

void print_all_books();//打印所有图书信息 

void recommend_books();//图书推荐 

void print_all_borrowed_books();//打印所有被借阅的图书信息 

#endif
