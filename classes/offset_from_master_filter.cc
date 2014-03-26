#include "offset_from_master_filter.h"
#include <iostream>

using namespace std;

/*****************Constructor****************/
offset_from_master_filter::offset_from_master_filter()
{
}

/*****************accessors***************/
Integer32 offset_from_master_filter::get_nsec_prev() const
{return nsec_prev;}

Integer32 offset_from_master_filter::get_y() const
{return y;}

/****************mutators******************/
void offset_from_master_filter::set_nsec_prev(Integer32 np)
{nsec_prev = np;}

void offset_from_master_filter::set_y(Integer32 x)
{y = x;}

ostream& operator<<(ostream& s, const offset_from_master_filter& it)
{
        cout << "nsec_prev : " << it.nsec_prev << endl;
        cout << "y : " << it.y << endl;

        return s;
}

