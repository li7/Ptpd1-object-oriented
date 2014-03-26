#include "MsgDelayResp.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	MsgDelayResp one;
	UInteger16 id;
	TimeRepresentation tr;

	id = 34;
	tr.set_seconds(5);
	tr.set_nanoseconds(15);
	one.set_delayReceiptTimestamp(tr);
	one.set_delayReceiptTimestamp_seconds(77);
	one.set_requestingSourcePortId(id);
	one.set_requestingSourceSequenceId(id);

	cout << one << endl;
}

