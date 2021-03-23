#include"menu.h"
#include"myclock.h"
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
void main_menu()//主菜单 
{
	system("cls");
	printf("\t\t\t********************************************************\n");
	printf("\t\t\t***              欢迎来到GGLS图书馆                  ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t***                  读者注册(1)                     ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                  读者登录(2)                     ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                  管理员登录(3)                   ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                  关于图书馆(4)                   ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                  退出系统(5)                     ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t********************************************************\n");
}

void admin_menu()//管理员菜单 
{
	system("cls");
	printf("\t\t\t********************************************************\n");
	printf("\t\t\t***                 管理员界面                       ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t***                 查找图书(1)                      ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 添加图书(2)                      ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 删除图书(3)                      ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 修改图书信息(4)                  ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 查看所有图书信息(5)              ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 查看所有读者信息(6)              ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 查看所有借阅书籍(7)              ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 返回主菜单(8)                    ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t********************************************************\n");
	
}

void reader_menu()//读者菜单 
{
	system("cls");
	printf("\t\t\t********************************************************\n");
	printf("\t\t\t***                   读者界面                       ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t***                 查找图书(1)                      ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 借阅图书(2)                      ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 归还图书(3)                      ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 图书推荐(4)                      ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 查看在借图书(5)                  ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 查看所有图书信息(6)              ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 查看个人信息(7)                  ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***                 返回主菜单(8)                    ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t********************************************************\n");
}

void about_menu()//关于 
{
	system("cls");
	printf("\t\t\t********************************************************\n");
	printf("\t\t\t***              欢迎来到GGLS图书馆                  ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t***         本图书馆致力于为所有热爱书籍的人         ***\n");
	printf("\t\t\t***         提供阅读场所，GGLS先生是我们敬爱，       ***\n");
	printf("\t\t\t***         的馆长兼系统开发总负责人，如果您         ***\n");
	printf("\t\t\t***         有任何问题，请通过2574832927@qq.com      ***\n");
	printf("\t\t\t***         联系馆长，非常感谢您的到来。             ***\n");
	printf("\t\t\t***                                                  ***\n");
	printf("\t\t\t***            按任意键返回主菜单                    ***\n");
	printf("\t\t\t***            -.-.-.-.-.-.-.-.-.-.-.-               ***\n");
	printf("\t\t\t********************************************************\n");
	getch();
}

void exit_lib()
{
	system("cls");
	printf("系统将在3秒后关闭~~~\n");
	printf("感谢您的到来，期待下次再见!");
	time_delay(3); 
	system("cls");
}
 

