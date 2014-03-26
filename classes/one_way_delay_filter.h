#ifndef ONEWAYDELAYFILTER_H
#define ONEWAYDELAYFILTER_H
#include "datatypes_dep.h"
#include "constants.h"
#include <iostream>

using namespace std;

class one_way_delay_filter{

public:

	/*************Constructor************/
	one_way_delay_filter();

	/****************accessors***********/
	Integer32 get_nsec_prev() const;
	Integer32 get_y() const;
	Integer32 get_s_exp() const;

	/****************mutators***********/
	void set_nsec_prev(Integer32 np);
	void set_y(Integer32 x);
	void set_s_exp(Integer32 se);

        friend ostream& operator<<(ostream& s, const one_way_delay_filter& it);


private:
	Integer32 nsec_prev;
	Integer32 y;
	Integer32 s_exp;
};

ostream& operator<<(ostream& s, const one_way_delay_filter& it);

#endif
