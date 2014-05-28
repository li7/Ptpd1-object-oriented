#include "DefaultData.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	DefaultData one;

	one.set_clockCommunicationTechnology('f');
	one.set_clockPortField(15);
	one.set_clockUuidField("default",7);
	one.set_clockStratum('a');
	one.set_clockIdentifier("id",2);
	one.set_clockVariance(2);
	one.set_clockFollowupCapable(true);
	one.set_preferred(true);
	one.set_initializable(true);
	one.set_externalTiming(true);
	one.set_isBoundaryClock(true);
	one.set_syncInterval('b');
	one.set_subdomainName("PTP default",11);
	one.set_numberPorts(11);
	one.set_numberForeignRecords(11);

	cout << one << endl;
}

