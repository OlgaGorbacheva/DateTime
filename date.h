#ifndef _DATE_H
#define _DATE_H

#include <time.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include "timespan.h"

using namespace std;

class Date{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    static int MDays[12];
public:
    friend class TimeSpan;
    Date();
    Date(int const _year, int const _month, int const _day, int const _hour, int const _minute, int const _second);
    Date(int const _year, int const _month, int const _day);
    Date(time_t _second);

    int DayOfWeek() const;

    static Date Current()
    {
        time_t sec;
        time(&sec);
        Date dt(sec);
        return dt;
    }

    friend istream & operator>> (istream &cin, Date &_date);
    friend ostream & operator<< (ostream &cout, Date const &_date);

    friend bool operator <(Date const &d1, Date const &d2);
    friend bool operator >(Date const &d1, Date const &d2);
    friend bool operator ==(Date const &d1, Date const &d2);
    friend bool operator !=(Date const &d1, Date const &d2);

    string ToString () const;
    bool isLeap() const;
    time_t DateToTime_t()const;

    friend TimeSpan Diff(Date const &d1, Date const &d2);

    friend Date operator +(Date const &d1, TimeSpan const &t);
    friend Date operator -(Date const &d1, TimeSpan const &t);
};

const Date FIRST_DAY(1970, 1, 1, 0, 0, 0);

const int SEC_IN_MINUTE = 60;
const int SEC_IN_HOUR = SEC_IN_MINUTE * 60;
const int SEC_IN_DAY = SEC_IN_HOUR * 24;
const int SEC_IN_YEAR = SEC_IN_DAY * 365;
const int SEC_IN_LEAP_YEAR = SEC_IN_DAY * 366;

#endif //_DATE_H
