#include "Current.h"

using namespace std;

/*****************Constructor****************/
Current::Current()
{
        stepsRemoved=0;
        offsetFromMaster;
        oneWayDelay;

}

/*****************accessors***************/
UInteger16 Current::get_stepsRemoved() const
{return stepsRemoved;}

TimeRepresentation &Current::get_offsetFromMaster()
{return offsetFromMaster;}

TimeRepresentation &Current::get_oneWayDelay()
{return oneWayDelay;}

/****************mutators******************/
void Current::set_stepsRemoved(UInteger16 sr)
{stepsRemoved = sr;}

void Current::set_offsetFromMaster(TimeRepresentation ofm)
{offsetFromMaster = ofm;}

void Current::set_oneWayDelay(TimeRepresentation owd)
{oneWayDelay = owd;}

Current &Current::operator=(const Current & other_t)
{
	stepsRemoved = other_t.stepsRemoved;
	offsetFromMaster = other_t.offsetFromMaster;
	oneWayDelay = other_t.oneWayDelay;
	return *this;
}
ostream& operator<<(ostream& s, const Current& it)
{
        cout << "steps removed : " << it.stepsRemoved << endl;
        cout << "offset from master : " << it.offsetFromMaster << endl;
        cout << "one way delay : " << it.oneWayDelay << endl;

        return s;
}

