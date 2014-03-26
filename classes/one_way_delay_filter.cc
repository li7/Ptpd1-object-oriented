#include "one_way_delay_filter.h"
#include <iostream>

using namespace std;

/*****************Constructor****************/
one_way_delay_filter::one_way_delay_filter()
{
}

/*****************accessors***************/
Integer32 one_way_delay_filter::get_nsec_prev() const
{return nsec_prev;}

Integer32 one_way_delay_filter::get_y() const
{return y;}

Integer32 one_way_delay_filter::get_s_exp() const
{return s_exp;}

/****************mutators******************/
void one_way_delay_filter::set_nsec_prev(Integer32 np)
{nsec_prev = np;}

void one_way_delay_filter::set_y(Integer32 x)
{y = x;}

void one_way_delay_filter::set_s_exp(Integer32 se)
{s_exp = se;}

ostream& operator<<(ostream& s, const one_way_delay_filter& it)
{
        cout << "nsec_prev : " << it.nsec_prev << endl;
        cout << "y : " << it.y << endl;
        cout << "s_exp : " << it.s_exp << endl;

        return s;
}

