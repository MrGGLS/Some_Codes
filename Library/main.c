#include<string.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h> 
#define false 0
#define true 1
#define CAPACITY 10000
#include"menu.h"
#include"lib.h"
#include"book.h"
#include"reader.h"
#include"secure.h"
#include"myclock.h"
typedef int bool;
Library lib;
Reader readers[1000];
BookInfo books[CAPACITY];

void getInfo()//从文件中读取书籍、读者的信息 
{
	memset(readers,0,sizeof(Reader)*1000);
	memset(books,0,sizeof(books));
	lib.booksType=lib.quantity=lib.readersNums=0;
	lib.capacity=CAPACITY;
	FILE *f_reader;
	FILE *f_books;
	FILE *f_borrowed;
	f_reader=fopen("readers_info.txt","r");
	if(!f_reader)
	{
		return;
	}
	f_books=fopen("books_info.txt","r");
	if(!f_books)
	{
		fclose(f_reader);
		return;	
	} 
	f_borrowed=fopen("borrowed_info.txt","r");
	if(!f_borrowed)
	{
		fclose(f_reader);
		fclose(f_books); 
		return;
	}
	char ch;
	ch=fgetc(f_reader);
	if(ch!=EOF)
	{
		rewind(f_reader);
		while(!feof(f_reader))
		{
			fscanf(f_reader,"%s %s %s %s\n",readers[lib.readersNums].account,readers[lib.readersNums].ID,readers[lib.readersNums].pwd,readers[lib.readersNums].sex);
			lib.readersNums++;
		}
	}
	ch=fgetc(f_books);
	if(ch!=EOF)
	{
		rewind(f_books);
		while(!feof(f_books))
		{
			fscanf(f_books,"%s %s %s %s %s %f %d %d %d\n",books[lib.booksType].no,books[lib.booksType].name,books[lib.booksType].author,books[lib.booksType].press,books[lib.booksType].category,&books[lib.booksType].price,&books[lib.booksType].borrowedNums,&books[lib.booksType].totalBorrowedNums,&books[lib.booksType].nums);
			lib.quantity+=(books[lib.booksType].nums-books[lib.booksType].borrowedNums);
			lib.booksType++;
		}		
	}
	ch=fgetc(f_borrowed);
	if(ch!=EOF)
	{
		rewind(f_borrowed);
		while(!feof(f_borrowed))
		{
			char ID[20];
			char no[20];
			fscanf(f_borrowed,"%s %s\n",ID,no);
			int index1=check_user_id(ID);
			int index2=check_book_by_no(no);
			readers[index1].borrowed[readers[index1].borrowedNum]=books[index2];
			readers[index1].borrowedNum++;
			printf("index1=%d id=%s borrowedNum=%d index2=%d no=%s\n",index1,readers[index1].ID,readers[index1].borrowedNum,index2,books[index2].no);
		}	
	}
	fclose(f_reader);
	fclose(f_books);
	fclose(f_borrowed);
}

void updateInfo()//将书籍、读者的信息保存到文件中 
{
	FILE *f_reader;
	FILE *f_books;
	FILE *f_borrowed;
	f_reader=fopen("readers_info.txt","w");
	if(!f_reader)
	{
		return;
	}
	f_books=fopen("books_info.txt","w");
	if(!f_books)
	{
		fclose(f_reader);
		return;	
	} 
	f_borrowed=fopen("borrowed_info.txt","w");
	if(!f_borrowed)
	{
		fclose(f_reader);
		fclose(f_books); 
		return;
	}

	for(int i=0;i<lib.readersNums;i++)
		fprintf(f_reader,"%s %s %s %s\n",readers[i].account,readers[i].ID,readers[i].pwd,readers[i].sex);

	for(int i=0;i<lib.booksType;i++)
		fprintf(f_books,"%s %s %s %s %s %.2f %d %d %d\n",books[i].no,books[i].name,books[i].author,books[i].press,books[i].category,books[i].price,books[i].borrowedNums,books[i].totalBorrowedNums,books[i].nums);		


	for(int i=0;i<lib.readersNums;i++)
	{
		if(readers[i].borrowedNum>0)
		{
			for(int j=0;j<readers[i].borrowedNum;j++)
				fprintf(f_borrowed,"%s %s\n",readers[i].ID,readers[i].borrowed[j].no);
		}
	}		

	fclose(f_reader);
	fclose(f_books);
	fclose(f_borrowed);
}

int main()
{
	fflush(stdin);
	while(true)
	{
		main_menu();
		bool flag1=false;
		char main_choice='a';
		while(main_choice>'5'||main_choice<'1')
			main_choice=getch();
		getInfo();
		switch(main_choice)
		{
			case '1':reader_register();break;
			case '2':
				{
					char ID[20]; 
					bool situation=reader_log_in(ID);
					if(situation==true)
					{
						while(true)
						{
							bool flag=0;
							reader_menu();
							char reader_choice='a';
							while(reader_choice<'1'||reader_choice>'8')
								reader_choice=getch();
							switch(reader_choice)
							{
								case '1':find_book();break;
								case '2':borrow_book(ID);break;
								case '3':return_book(ID);break;
								case '4':recommend_books();break;
								case '5':show_borrowed_logs(ID);break;
								case '6':print_all_books();break;
								case '7':show_reader_info(ID);break;
								case '8':flag=true;break;
							}
							updateInfo();
							getInfo();
							if(flag==true)
								break;					
						}
	
					}
				}
				break;
			case '3':
				{
					bool situation=admin_log_in();
					if(situation==true)
					{
						while(true)
						{
							bool flag=false;
							admin_menu();
							char admin_choice='a';
							while(admin_choice<'1'||admin_choice>'8')
								admin_choice=getch();
							switch(admin_choice)
							{
								case '1':find_book();break;
								case '2':add_book();break;
								case '3':delete_book();break;
								case '4':update_book_info();break;
								case '5':print_all_books();break;
								case '6':show_all_readers();break;
								case '7':print_all_borrowed_books();break;
								case '8':flag=true;break;
							}
							updateInfo();
							getInfo();
							if(flag==true)
								break;
						}
					}
				}
				break;
			case '4':about_menu();break;
			case '5':
				{
					exit_lib();
					flag1=true;
				}
				break;
		}
		updateInfo(); 
		if(flag1==true)
			break; 
	}
	return 0;
}
