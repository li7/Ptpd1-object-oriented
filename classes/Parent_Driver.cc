#include "Parent.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	Parent one;

	one.set_parentCommunicationTechnology('f');
	one.set_parentPortId(15);
	one.set_observedDrift(5);

	cout << one << endl;
}

