#include "MsgManagement.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	MsgManagement mm;
	MsgManagementPayload mmp;

	mmp.get_foreign().set_returnedPortNumber(3);
	mmp.get_parent().set_observedDrift(3);
	mm.set_targetCommunicationTechnology('x');
	mm.set_payload(mmp);
	cout << mm << endl;
	cout << mmp << endl;
}

