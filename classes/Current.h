#ifndef CURRENT_H
#define CURRENT_H
#include "TimeRepresentation.h"
#include "constants.h"
#include <iostream>

using namespace std;

class Current{

public:

	/*************Constructor************/
	Current();

	/****************accessors***********/
	UInteger16 get_stepsRemoved() const;
	TimeRepresentation &get_offsetFromMaster();
	TimeRepresentation &get_oneWayDelay();

	/****************mutators***********/
	void set_stepsRemoved(UInteger16 sr);
	void set_offsetFromMaster(TimeRepresentation ofm);
	void set_oneWayDelay(TimeRepresentation owd);

	Current &operator=(const Current & other_t);

        friend ostream& operator<<(ostream& s, const Current& it);


private:
	UInteger16 stepsRemoved;
	TimeRepresentation offsetFromMaster;
	TimeRepresentation oneWayDelay;
};

ostream& operator<<(ostream& s, const Current& it);

#endif
