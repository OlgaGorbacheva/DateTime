#ifndef TIMESPAN_H
#define TIMESPAN_H

#include "date.h"
#include <time.h>

using namespace std;

class TimeSpan
{
private:
    time_t interval;
public:
    friend class Date;
    friend TimeSpan Diff(class Date d1, Date d2);
    TimeSpan():interval(0)
    {; }
    TimeSpan(time_t _interval):interval(_interval)
    {; }

    friend istream & operator>> (istream &cin, TimeSpan &_t)
    {
        cin >> _t.interval;
        return cin;
    }

    friend ostream & operator<< (ostream &cout, TimeSpan const &_t)
    {
        cout << _t.interval;
        return cout;
    }
    time_t get() const
    {
        return interval;
    }
};

#endif // TIMESPAN_H
