#include "MsgManagement.h"
#include "MsgManagementPayload.h"
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
	mm.get_payload().get_clockIdentity().set_clockPortField(6);
	mm.get_payload().get_clockIdentity().set_clockCommunicationTechnology(6);
//	mm.get_payload().get_clockIdentity().set_clockUuidField("fourteen",6);
	cout << mm << endl;
	cout << mmp << endl;
	cout << mm.get_payload().get_clockIdentity() << endl;
}

