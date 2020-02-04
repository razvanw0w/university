#ifndef OOP3_DATE_H
#define OOP3_DATE_H

typedef struct {
    int year;
    int month;
    int day;
}Date;

Date createDate(int year, int month, int day);
int getDateYear(Date date);
int getDateMonth(Date date);
int getDateDay(Date date);
void setDateYear(Date *date, int year);
void setDateMonth(Date *date, int month);
void setDateDay(Date *date, int day);
int isDateLess(Date date1, Date date2);
int countDaysUntilDate(Date date);
int getDayDifference(Date date1, Date date2);

#endif //OOP3_DATE_H
