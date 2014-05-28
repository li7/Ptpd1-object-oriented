#include "GlobalTime.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	GlobalTime one;
	TimeRepresentation tr;
	UInteger32 x;

	tr.set_seconds(19);
	tr.set_nanoseconds(575);
	one.set_localTime(tr);
	one.set_currentUtcOffset(1234);
	one.set_epochNumber(5678);
	one.set_leap59(true);
	one.set_leap61(false);
	cout << one << endl;
	x = one.get_localTime().get_seconds();
	cout << "x: " << x << endl;

	one.get_localTime().set_seconds(15);
	one.get_localTime().set_nanoseconds(15);

	x = one.get_localTime().get_seconds();
	cout << "x: " << x << endl;
	cout << one << endl;
}

