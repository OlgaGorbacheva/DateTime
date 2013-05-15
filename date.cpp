#include "date.h"

int Date::MDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool Date::isLeap() const
{
    return (year + 1) % 400 == 0 || ((year + 1) % 100 != 0 && (year + 1) % 4 == 0);
}

Date::Date():year(1970), month(0), day(1), hour(0), minute(0), second(0)
{; }

Date::Date(int const _year, int const _month, int const _day, int const _hour, int const _minute, int const _second):
    year(_year), month(_month - 1), day(_day), hour(_hour), minute(_minute), second(_second)
{; }

Date::Date(int const _year, int const _month, int const _day):
    year(_year), month(_month - 1), day(_day), hour(0), minute(0), second(0)
{; }

Date::Date(time_t _Second)
{
    long long int _second = _Second;
    year = FIRST_DAY.year;
    month = FIRST_DAY.month;
    day = FIRST_DAY.day;
    hour = FIRST_DAY.hour;
    minute = FIRST_DAY.minute;
    while (_second >= SEC_IN_LEAP_YEAR ||
           (!isLeap() && _second >= SEC_IN_YEAR)){
        year++;
        if (isLeap())
            _second -= SEC_IN_LEAP_YEAR;
        else _second -= SEC_IN_YEAR;
    }
    while ((_second >= (MDays[month] + 1) * SEC_IN_DAY) ||
           (!isLeap() && month == 1 && _second >= MDays[month] * SEC_IN_DAY)){
        if (month == 1 && isLeap())
            _second -= SEC_IN_DAY * (MDays[month] + 1);
        else _second -= SEC_IN_DAY * MDays[month];
        month++;
    }
    while (_second >= SEC_IN_DAY){
        _second -= SEC_IN_DAY;
        day++;
    }
    while (_second >= SEC_IN_HOUR){
        _second -= SEC_IN_HOUR;
        hour++;
    }
    while (_second >= SEC_IN_MINUTE){
        _second -= SEC_IN_MINUTE;
        minute++;
    }
    second = _second;
}

int Date::DayOfWeek() const
{
    int TotalDays = 0;
    for (int count = FIRST_DAY.year; count < year; count++){
        if (count % 400 == 0 || (count % 100 != 0 && count % 4 == 0))
            TotalDays += 366;
        else TotalDays += 365;
    }
    for (int j = 0; j < month; j++){
        if (j == 2 && isLeap())
            TotalDays += MDays[j] + 1;
        else TotalDays += MDays[j];
    }
    TotalDays += day;
    return (TotalDays % 7 + 2) % 7;
}

istream & operator>> (istream &cin, Date &_date)
{
    int x;
    cin >> x; _date.year = x;
    cin >> x; _date.month = x - 1;
    if (x > 12 || x < 0)
        throw "unexpectable data";
    cin >> x; _date.day = x;
    if ((x > _date.MDays[_date.month] || (_date.isLeap() && _date.month == 1 && x > _date.MDays[_date.month]+1))|| x < 0)
        throw "unexpectable data";
    cin >> x; _date.hour = x;
    if (x > 23 || x < 0)
        throw "unexpectable data";
    cin >> x; _date.minute = x;
    if (x > 59 || x < 0)
        throw "unexpectable data";
    cin >> x; _date.second = x;
    if (x > 59 || x < 0)
        throw "unexpectable data";
    return cin;
}

ostream & operator<< (ostream &cout, Date const &_date)
{
    cout << _date.year << "/" << _date.month + 1 << "/" << _date.day << " " <<
            _date.hour << ":" << _date.minute << ":" << _date.second;
    return cout;
}

string to_string(int const x)
{
    char *num;
    num = new char [10];
    int n = x, i = 0;
    while (n > 0){
        num[i] = n % 10 + '0';
        n /= 10;
        i++;
    }
    string res(num, i);
    reverse(res.begin(), res.end());
    return res;
}

string Date::ToString() const
{
    return to_string(year) + "/" + to_string(month + 1)+ "/" + to_string(day) + " "
        + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
}

bool operator <(Date const &d1, Date const &d2)
{
    if (d1.year == d2.year){
        if (d1.month == d2.month){
            if (d1.day == d2.day){
                if (d1.hour == d2.hour){
                    if (d1.minute == d2.minute){
                        return d1.second < d2.second;
                    }else return d1.minute < d2.minute;
                }else return d1.hour < d2.hour;
            }else return d1.day < d2.day;
        }else return d1.month < d2.month;
    }else return d1.year < d2.year;
}

bool operator >(Date const &d1, Date const &d2)
{
    if (d1.year == d2.year){
        if (d1.month == d2.month){
            if (d1.day == d2.day){
                if (d1.hour == d2.hour){
                    if (d1.minute == d2.minute){
                        return d1.second > d2.second;
                    }else return d1.minute > d2.minute;
                }else return d1.hour > d2.hour;
            }else return d1.day > d2.day;
        }else return d1.month > d2.month;
    }else return d1.year > d2.year;
}

bool operator ==(Date const &d1, Date const &d2)
{
    return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day &&
            d1.hour == d2.hour && d1.minute == d2.minute && d1.second == d2.second;
}

bool operator !=(Date const &d1, Date const &d2)
{
    return !(d1 == d2);
}

time_t Date::DateToTime_t() const
{
    time_t res = second + minute * SEC_IN_MINUTE + hour * SEC_IN_HOUR;
    for (int i = month - 1; i >= 0; i--){
        if (i == 1 && isLeap())
            res += (MDays[i] + 1) * SEC_IN_DAY;
        else res += MDays[i] * SEC_IN_DAY;
    }
    Date buf(year - 1, month, day);
    for (; buf.year >= 1970; buf.year--){
        if (buf.isLeap())
            res += SEC_IN_LEAP_YEAR;
        else res += SEC_IN_YEAR;
    }
    return res;
}

TimeSpan Diff(Date const &d1, Date const &d2)
{
    TimeSpan res(abs(d1.DateToTime_t() - d2.DateToTime_t()));
    return res;
}

Date operator +(Date const &d1, TimeSpan const &t)
{
    time_t sec = d1.DateToTime_t() + t.get();
    Date res(sec);
    return res;
}

Date operator -(Date const &d1, TimeSpan const &t)
{
    time_t sec = d1.DateToTime_t() - t.get();
    Date res(sec);
    return res;
}
