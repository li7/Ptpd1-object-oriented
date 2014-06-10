#ifndef GLOBALTIME_H
#define GLOBALTIME_H
#include "TimeRepresentation.h"
#include "constants.h"
#include <iostream>

using namespace std;

class GlobalTime{

public:

	/*************Constructor************/
	GlobalTime();

	/****************accessors***********/
	TimeRepresentation& get_localTime();
	Integer16 get_currentUtcOffset() const;
	Boolean get_leap59() const;
	Boolean get_leap61() const;
	UInteger16 get_epochNumber() const;

	/****************mutators***********/
	void set_localTime(TimeRepresentation lt);
	void set_currentUtcOffset(Integer16 cuo);
	void set_leap59(Boolean l59);
	void set_leap61(Boolean l61);
	void set_epochNumber(UInteger16 en);

	GlobalTime &operator=(const GlobalTime & other_t);

        friend ostream& operator<<(ostream& s, const GlobalTime& it);

private:
	TimeRepresentation localTime;
	Integer16 currentUtcOffset;
	Boolean	leap59;
	Boolean	leap61;
	UInteger16 epochNumber;
};

ostream& operator<<(ostream& s, const GlobalTime& it);
#endif
