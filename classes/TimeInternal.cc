#include "TimeInternal.h"
#include <iostream>

using namespace std;

/*****************Constructor****************/
TimeInternal::TimeInternal()
{
seconds = 0;
nanoseconds = 0;
}

/*****************accessors***************/
UInteger32 TimeInternal::get_seconds() const
{return seconds;}

Integer32 TimeInternal::get_nanoseconds() const
{return nanoseconds;}

/****************mutators******************/
void TimeInternal::set_seconds(UInteger32 s)
{seconds = s;}

void TimeInternal::set_nanoseconds(Integer32 ns)
{nanoseconds = ns;}

ostream& operator<<(ostream& s, const TimeInternal& it)
{
        cout << "Seconds : " << it.seconds << endl;
        cout << "Nanoseconds : " << it.nanoseconds << endl;

        return s;
}

