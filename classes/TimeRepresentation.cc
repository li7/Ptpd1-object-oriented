#include "TimeRepresentation.h"
#include <iostream>

using namespace std;

/*****************Constructor****************/
TimeRepresentation::TimeRepresentation()
{
seconds = 0;
nanoseconds = 0;
}

/*****************accessors***************/
UInteger32 TimeRepresentation::get_seconds() const
{return seconds;}

Integer32 TimeRepresentation::get_nanoseconds() const
{return nanoseconds;}

/****************mutators******************/
void TimeRepresentation::set_seconds(UInteger32 s)
{seconds = s;}

void TimeRepresentation::set_nanoseconds(Integer32 ns)
{nanoseconds = ns;}

TimeRepresentation &TimeRepresentation::operator=(const TimeRepresentation & other_t)
{
	seconds = other_t.seconds;
	nanoseconds = other_t.nanoseconds;
	return *this;
}

ostream& operator<<(ostream& s, const TimeRepresentation& it)
{
        cout << "Seconds : " << it.seconds << endl;
        cout << "Nanoseconds : " << it.nanoseconds << endl;

        return s;
}

