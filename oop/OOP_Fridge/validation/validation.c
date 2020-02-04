#include "validation.h"

/**
 * This function validates a category
 * @param category: char* - the given category
 * @return: 1 - if the category is valid
 *          0 - otherwise
 */
int validateCategory(char* category) {
    char* validCategories[] = {"dairy", "sweets", "meat", "fruit"};
    int i;
    for (i = 0; i < 4; ++i) {
        if (strcmp(category, validCategories[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * This function tells if a year is leap or not
 * @param year: int - the given year
 * @return 1 - if the year is leap
 *         0 - otherwise
 */
int isYearLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
 * This function validates an expiration date
 * @param year: int - the year of the expiration date
 * @param month: int - the month of the expiration date
 * @param day: int - the day of the expiration date
 * @return: 1 - if the date is valid
 *          0 - otherwise
 */
int validateExpirationDate(int year, int month, int day) {
    if (month < 1 || month > 12) {
        return 0;
    }
    int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isYearLeap(year) == 1) {
        monthDays[2] = 29;
    }

    if (day < 1 || day > monthDays[month]) {
        return 0;
    }
    return 1;
}