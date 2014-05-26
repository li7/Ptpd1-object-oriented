#include "Current.h"
#include <string.h>

using namespace std;

main()
{
	Current one;
	UInteger16 id;
	TimeRepresentation tr;

	id = 34;
	tr.set_seconds(5);
	tr.set_nanoseconds(15);
	one.set_stepsRemoved(1);
	one.set_offsetFromMaster(tr);
	one.set_oneWayDelay(tr);
	cout << one << endl;
	one.get_oneWayDelay().set_seconds(9);
	one.get_oneWayDelay().set_nanoseconds(10);
	one.get_offsetFromMaster().set_seconds(11);
	one.get_offsetFromMaster().set_nanoseconds(12);

	cout << one << endl;
}

