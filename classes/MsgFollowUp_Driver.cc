#include "MsgFollowUp.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	MsgFollowUp one;
	UInteger16 id;
	TimeRepresentation tr;

	id = 34;
	tr.set_seconds(5);
	tr.set_nanoseconds(15);
	one.set_associatedSequenceId(id);
	one.set_preciseOriginTimestamp(tr);

	cout << one << endl;
}

