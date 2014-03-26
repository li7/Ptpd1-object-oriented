#ifndef TIMEREPRESENTATION_H
#define TIMEREPRESENTATION_H
#include "datatypes_dep.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

using namespace std;

class TimeRepresentation{

public:

	/*************Constructor************/
	TimeRepresentation();

	/****************accessors***********/
	UInteger32 get_seconds() const;
	Integer32 get_nanoseconds() const;

	/****************mutators***********/
	void set_seconds(UInteger32 s);
	void set_nanoseconds(Integer32 ns);

	/*******Operator*******/
	TimeRepresentation &operator=(const TimeRepresentation & other_t);

        friend ostream& operator<<(ostream& s, const TimeRepresentation& it);


private:
	UInteger32 seconds;
	Integer32 nanoseconds;
};

ostream& operator<<(ostream& s, const TimeRepresentation& it);

#endif
