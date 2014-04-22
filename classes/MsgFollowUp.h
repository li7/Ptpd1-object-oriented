#ifndef MSGFOLLOWUP_H
#define MSGFOLLOWUP_H
#include "TimeRepresentation.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

using namespace std;

class MsgFollowUp{

public:

	/*************Constructor************/
	MsgFollowUp();

	/****************accessors***********/
	UInteger16 get_associatedSequenceId() const;
	TimeRepresentation& get_preciseOriginTimestamp();
	UInteger32 get_preciseOriginTimestamp_seconds() const;
	Integer32 get_preciseOriginTimestamp_nanoseconds() const;

	/****************mutators***********/
	void set_associatedSequenceId(UInteger16 asi);
	void set_preciseOriginTimestamp(TimeRepresentation pot);
	void set_preciseOriginTimestamp_seconds(UInteger32 sec);
	void set_preciseOriginTimestamp_nanoseconds(Integer32 nsec);

        friend ostream& operator<<(ostream& s, const MsgFollowUp& it);
	MsgFollowUp &operator=(const MsgFollowUp & other);


private:
	UInteger16 associatedSequenceId;
	TimeRepresentation preciseOriginTimestamp;
};

ostream& operator<<(ostream& s, const MsgFollowUp& it);

#endif
