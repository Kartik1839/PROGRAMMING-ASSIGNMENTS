#include <stdio.h>
#include <time.h>

int is_leap_year(int year) {
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        return 1;
    }
    return 0;
}

int get_days_in_month(int month, int year) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 1 && is_leap_year(year)) { // February (0-indexed month 1)
        return 29;
    }
    return days_in_month[month];
}

int get_first_day_of_year(int year) {
    struct tm time_info = {0};
    time_info.tm_year = year - 1900; // Years since 1900
    time_info.tm_mon = 0;            // January (0)
    time_info.tm_mday = 1;           // 1st of the month
    time_info.tm_isdst = -1;

    mktime(&time_info);
    return time_info.tm_wday;        // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
}

int main() {
    int year;

    printf("Enter year: ");
    if (scanf("%d", &year) != 1) {
        return 1;
    }

    const char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    int start_day = get_first_day_of_year(year);

    printf("\n================ CALENDAR - %d ================\n", year);

    for (int month = 0; month < 12; month++) {
        int days = get_days_in_month(month, year);

        printf("\n------------ %s %d ------------\n", months[month], year);
        printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        // Leading spaces for the first day of the month
        for (int space = 0; space < start_day; space++) {
            printf("     ");
        }

        // Print all days of the month
        for (int day = 1; day <= days; day++) {
            printf("%3d  ", day);
            start_day = (start_day + 1) % 7;
            if (start_day == 0) {
                printf("\n");
            }
        }

        // Move to a new line if the month didn't end on Saturday
        if (start_day != 0) {
            printf("\n");
        }
    }

    return 0;
}
