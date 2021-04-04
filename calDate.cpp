//
// Created by Mr.GGLS on 2021/4/4.
//
#include "iostream"
using namespace ::std;
struct Date
{
    int year;
    int month;
    int day;
};
Date initDate{1900,1,1};//Monday
int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
const char* weekdays[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
void addOneDay(Date&);//add one day to the date
void addOneMonth(Date&);//add one month to the date
void addOneYear(Date&);//add one year to the date
bool isLeapYear(int);//is this year a leap year?
bool isLaterDate(Date d1,Date d2);//is d1>d2?
int calPassedDays(Date);//calculate all passed days in this year, including today
int calRestDays(Date);//calculate all rest days in this year, not including today
int calDaysIn2Years(int,int);//calculate all days between two assigned years
int calDaysIn2Dates(Date,Date);//calculate all days between two assigned dates
void printDate(Date& date);//print out date
void printWeekDay(Date& date);//print out the day of the week
void printNextMonday(Date& date);//print out the date of the next Monday
#define DAYS_OF_NORM_YEAR 365;//days of the normal year
#define DAYS_OF_LEAP_YEAR 366;//days of the leap year
int main()
{
    Date d1{2016,2,29};
    Date d2{2016,4,7};

    addOneDay(d1);
    printDate(d1);

    addOneYear(d1);
    printDate(d1);

    addOneMonth(d1);
    printDate(d1);

    printWeekDay(d1);
    printNextMonday(d1);

    printWeekDay(d2);
    printNextMonday(d2);
    return 0;
}

void addOneDay(Date& date)
{
    ++date.day;
    if (date.day>months[date.month-1])
    {
        if(date.month==2)
        {
            if (date.day==29)
            {
                if (!isLeapYear(date.year))
                {
                    ++date.month;
                    date.day=1;
                }
            }
            else if (date.day>29)
            {
                if (isLeapYear(date.year))
                    date.day-=29;
                else
                    date.day-=28;
                ++date.month;
            }
        }
        else
        {
            ++date.month;
            if (date.month>12)
                date.month=1;
            date.day=1;
        }
    }
}

void addOneMonth(Date& date)
{
    switch (date.month) {
        case 1:{   ++date.month;
                    if (date.day>28)
                    {
                        if(isLeapYear(date.year))
                            date.day=29;
                        else
                            date.day=28;
                    }
                    break;
                }
        case 3:;
        case 5:;
        case 7:;
        case 8:;
        case 10:{   ++date.month;
                    if (date.day==31)
                        --date.day;
                    break;
                }
        case 12:{   ++date.year;
                    date.month=1;
                    break;
                }
        default: ++date.month;break;
    }

}

void addOneYear(Date& date)
{
    if (isLeapYear(date.year)&&date.day==29)
        --date.day;
    ++date.year;
}

bool isLaterDate(Date d1,Date d2)
{
    if (d1.year>d2.year)
        return true;
    else if(d1.year==d2.year)
    {
        if(d1.month>d2.month)
            return true;
        else if(d1.month==d2.month)
        {
            if(d1.day>d2.day)
                return true;
            return false;
        }
        return false;
    }
    return false;
}

bool isLeapYear(int year)
{
    return (year%400==0)||(year%4==0&&year%100!=0);
}

int calPassedDays(Date date)
{
    int days=0;
    for (int i = 0; i < date.month-1; ++i)
        days+=months[i];
    days+=date.day;
    if ((date.month>2)&&isLeapYear(date.year))
        ++days;
    return days;
}

int calRestDays(Date date)
{
    int days=months[date.month-1]-date.day;
    for(int i=date.month;i<12;++i)
        days+=months[i];
    if ((date.month<=2)&&isLeapYear(date.year))
        ++days;
    return days;
}

int calDaysIn2Years(int year1,int year2)
{
    int days=0;
    for(int i=year1;i<year2;i++)
    {
        if (isLeapYear(i))
        {
            days+=DAYS_OF_LEAP_YEAR;
        }
        else
            days+=DAYS_OF_NORM_YEAR;
    }
    return days;
}

int calDaysIn2Dates(Date d1,Date d2)
{
    bool flag=false;
    if(isLaterDate(d1,d2))
    {
        Date tmp=d1;
        d1=d2;
        d2=tmp;
        flag=true;
    }
    int days=calRestDays(d1);
    if(d1.year!=d2.year)
    {
        if((d2.year-d1.year)>=2)
            days+=calDaysIn2Years(d1.year+1,d2.year);
        days+=calPassedDays(d2);
    }
    else
    {
        days=days-calRestDays(d2);
    }
    return flag==true?-days:days;
}

void printDate(Date& date)
{
    cout<<"date: "<<date.year<<"/"<<date.month<<"/"<<date.day<<endl;
}

void printWeekDay(Date& date)
{
    int days=calDaysIn2Dates(initDate,date);
    days%=7;
    if (days==0)
        cout<<weekdays[0]<<endl;
    else if (days<0)
    {
        cout<<weekdays[7+days]<<endl;
    }
    else
    {
        cout<<weekdays[days]<<endl;
    }
}

void printNextMonday(Date& date)
{
    int days=calDaysIn2Dates(initDate,date);
    Date tmp=date;
    days%=7;
    if (days<0)
    {
        days+=7;
        days=7-days;
    }
    else if (days==0)
    {
        days+=7;
    }
    else
    {
        days=7-days;
    }
    while (days--)
        addOneDay(tmp);
    printDate(tmp);
}