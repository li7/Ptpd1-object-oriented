#include "ClockIdentity.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	ClockIdentity one;

	one.set_clockCommunicationTechnology('d');
	one.set_clockPortField(1);
	one.set_clockUuidField("clockU",6);//max length 6
	one.set_manufacturerIdentity("manufacturer identity",40);//max length 48

	cout << one << endl;
}

