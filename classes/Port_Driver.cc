#include "Port.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	Port one;

	one.set_returnedPortNumber(15);
	one.set_lastSyncEventSequenceNumber(35);

	cout << one << endl;
}

