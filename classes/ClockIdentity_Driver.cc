#include "ClockIdentity.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	ClockIdentity one;

	one.set_clockCommunicationTechnology('f');
	one.set_clockPortField(15);
	one.set_clockUuidField("fourteen",6);

	cout << one << endl;
}

