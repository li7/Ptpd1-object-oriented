#include "GlobalTime.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
GlobalTime::GlobalTime()
{
        localTime;
        currentUtcOffset=0;
        leap59=0;
        leap61=0;
        epochNumber=0;
}

/*****************accessors***************/
TimeRepresentation& GlobalTime::get_localTime()
{return localTime;}

Integer16 GlobalTime::get_currentUtcOffset() const
{return currentUtcOffset;}

Boolean GlobalTime::get_leap59() const
{return leap59;}

Boolean GlobalTime::get_leap61() const
{return leap61;}

UInteger16 GlobalTime::get_epochNumber() const
{return epochNumber;}

/****************mutators******************/
void GlobalTime::set_localTime(TimeRepresentation lt)
{localTime = lt;}

void GlobalTime::set_currentUtcOffset(Integer16 cuo)
{currentUtcOffset = cuo;}

void GlobalTime::set_leap59(Boolean l59)
{leap59 = l59;}

void GlobalTime::set_leap61(Boolean l61)
{leap61 = l61;}

void GlobalTime::set_epochNumber(UInteger16 en)
{epochNumber = en;}

GlobalTime &GlobalTime::operator=(const GlobalTime & other_t)
{
	localTime = other_t.localTime;
	currentUtcOffset = other_t.currentUtcOffset;
	leap59 = other_t.leap59;
	leap61 = other_t.leap61;
	epochNumber = other_t.epochNumber;
	
	return *this;
}
ostream& operator<<(ostream& s, const GlobalTime& it)
{
        cout << "local time : " << it.localTime << endl;
/*        cout << "current utc offset : " << it.currentUtcOffset << endl;
        cout << "leap59 : " << it.leap59 << endl;
        cout << "leap61 : " << it.leap61 << endl;
        cout << "epochNumber : " << it.epochNumber << endl;
*/
        return s;
}

