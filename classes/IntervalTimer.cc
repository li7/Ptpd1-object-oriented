#include "IntervalTimer.h"
#include <iostream>

using namespace std;

/*****************Constructor****************/
IntervalTimer::IntervalTimer()
{
interval = 0;
left = 0;
expire = false;
}

/*****************accessors***************/
Integer32 IntervalTimer::get_interval() const
{return interval;}

Integer32 IntervalTimer::get_left() const
{return left;}

Boolean IntervalTimer::get_expire() const
{return expire;}

/****************mutators******************/
void IntervalTimer::set_interval(Integer32 i)
{interval = i;}

void IntervalTimer::set_left(Integer32 l)
{left = l;}

void IntervalTimer::set_expire(Boolean e)
{expire = e;}

ostream& operator<<(ostream& s, const IntervalTimer& it)
{
        cout << "Interval : " << it.interval << endl;
        cout << "left : " << it.left << endl;

        return s;
}

