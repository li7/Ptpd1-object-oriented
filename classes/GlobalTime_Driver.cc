#include "GlobalTime.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	GlobalTime one;
	TimeRepresentation tr;

	tr.set_seconds(19);
	tr.set_nanoseconds(575);
	one.set_localTime(tr);
	one.set_currentUtcOffset(1234);
	one.set_epochNumber(5678);
	one.set_leap59(true);
	one.set_leap61(false);

	one.get_localTime().set_seconds(15);

	cout << one << endl;
	one.set_localTime(tr);
	one.get_localTime().set_nanoseconds(60);
	cout << one << endl;
}

