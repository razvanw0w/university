#include "date.h"

/**
 * This function creates a date based on the year, month and day
 * @param year: int - the year of the date
 * @param month: int - the month of the date
 * @param day: int - the day of the date
 * @return date: Date - the created date
 */
Date createDate(int year, int month, int day) {
    Date date;
    date.year = year;
    date.month = month;
    date.day = day;
    return date;
}

/**
 * This function returns a date's year field
 * @param date: Date - the current date
 * @return year: int - the date's year
 */
int getDateYear(Date date) {
    return date.year;
}

/**
 * This function returns a date's month field
 * @param date: Date - the current date
 * @return month: int - the date's month
 */
int getDateMonth(Date date) {
    return date.month;
}

/**
 * This function returns a date's day field
 * @param date: Date - the current date
 * @return day: int - the date's day
 */
int getDateDay(Date date) {
    return date.day;
}

/**
 * This function sets a date's year field
 * @param date: Date* - the current date
 * @param year: int - the year which needs to be set
 */
void setDateYear(Date *date, int year) {
    date->year = year;
}

/**
 * This function sets a date's month field
 * @param date: Date* - the current date
 * @param month: int - the month which needs to be set
 */
void setDateMonth(Date *date, int month) {
    date->month = month;
}

/**
 * This function sets a date's day field
 * @param date: Date* - the current date
 * @param day: int - the day which needs to be set
 */
void setDateDay(Date *date, int day) {
    date->day = day;
}

/**
 * This function tells if one date is smaller than the another
 * @param date1: Date - the first date to be compared
 * @param date2: Date - the second date to be compared
 * @return: 1 if the first date is smaller than the another
 *          0 otherwise
 */
int isDateLess(Date date1, Date date2) {
    int year1 = getDateYear(date1);
    int year2 = getDateYear(date2);

    if (year1 != year2)
        return year1 < year2;

    int month1 = getDateMonth(date1);
    int month2 = getDateMonth(date2);

    if (month1 != month2)
        return month1 < month2;

    int day1 = getDateDay(date1);
    int day2 = getDateDay(date2);

    return day1 < day2;
}

/**
 * This function computes the number of days until a specified date
 * @param date: Date - a given valid date
 * @return: the number of days until the specified date
 */
int countDaysUntilDate(Date date) {
    int year = getDateYear(date);
    int month = getDateMonth(date);
    int day = getDateDay(date);

    if (month <= 2) {
        --year;
        month += 13;
    }
    else {
        ++month;
    }
    int numberOfDays = 1461 * year / 4 + 153 * month / 5 + day;
    return numberOfDays;
}

/**
 * This function computes the difference in days between two dates
 * @param date1: Date - the first date
 * @param date2: Date - the second date
 * @return: the number of days between the two specified dates
 */
int getDayDifference(Date date1, Date date2) {
    return countDaysUntilDate(date2) - countDaysUntilDate(date1);
}