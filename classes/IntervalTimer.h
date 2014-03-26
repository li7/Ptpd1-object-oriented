#ifndef INTERVALTIMER_H
#define INTERVALTIMER_H
#include "datatypes_dep.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

using namespace std;

class IntervalTimer{

public:

	/*************Constructor************/
	IntervalTimer();

	/****************accessors***********/
	Integer32 get_interval() const;
	Integer32 get_left() const;
	Boolean get_expire() const;

	/****************mutators***********/
	void set_interval(Integer32 i);
	void set_left(Integer32 l);
	void set_expire(Boolean e);

        friend ostream& operator<<(ostream& s, const IntervalTimer& it);


private:
	Integer32 interval;
	Integer32 left;
	Boolean expire;
};

ostream& operator<<(ostream& s, const IntervalTimer& it);

#endif
