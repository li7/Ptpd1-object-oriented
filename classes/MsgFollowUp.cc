#include "MsgFollowUp.h"
#include <iostream>

using namespace std;

/*****************Constructor****************/
MsgFollowUp::MsgFollowUp()
{
associatedSequenceId = 0;
}

/*****************accessors***************/
UInteger16 MsgFollowUp::get_associatedSequenceId() const
{return associatedSequenceId;}

TimeRepresentation& MsgFollowUp::get_preciseOriginTimestamp()
{return preciseOriginTimestamp;}

UInteger32 MsgFollowUp::get_preciseOriginTimestamp_seconds() const
{return preciseOriginTimestamp.get_seconds();}

Integer32 MsgFollowUp::get_preciseOriginTimestamp_nanoseconds() const
{return preciseOriginTimestamp.get_nanoseconds();}

/****************mutators******************/
void MsgFollowUp::set_associatedSequenceId(UInteger16 asi)
{associatedSequenceId = asi;}

void MsgFollowUp::set_preciseOriginTimestamp(TimeRepresentation pot)
{preciseOriginTimestamp = pot;}

void MsgFollowUp::set_preciseOriginTimestamp_seconds(UInteger32 sec)
{preciseOriginTimestamp.set_seconds(sec);}

void MsgFollowUp::set_preciseOriginTimestamp_nanoseconds(Integer32 nsec)
{preciseOriginTimestamp.set_nanoseconds(nsec);}

MsgFollowUp &MsgFollowUp::operator=(const MsgFollowUp & other)
{
	associatedSequenceId = other.associatedSequenceId;
	preciseOriginTimestamp = other.preciseOriginTimestamp;
	return *this;
}

ostream& operator<<(ostream& s, const MsgFollowUp& it)
{
        cout << "assiciatedSequenceId : " << it.associatedSequenceId << endl;
        cout << "PreciseOriginTimestamp : " << it.preciseOriginTimestamp << endl;

        return s;
}

