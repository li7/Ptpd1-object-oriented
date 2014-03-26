#ifndef OFFSETFROMMASTERFILTER_H
#define OFFSETFROMMASTERFILTER_H
#include "datatypes_dep.h"
#include "constants.h"
#include <iostream>

using namespace std;

class offset_from_master_filter{

public:

	/*************Constructor************/
	offset_from_master_filter();

	/****************accessors***********/
	Integer32 get_nsec_prev() const;
	Integer32 get_y() const;

	/****************mutators***********/
	void set_nsec_prev(Integer32 np);
	void set_y(Integer32 x);

        friend ostream& operator<<(ostream& s, const offset_from_master_filter& it);


private:
	Integer32 nsec_prev;
	Integer32 y;
};

ostream& operator<<(ostream& s, const offset_from_master_filter& it);

#endif
