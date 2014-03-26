#include "TimeRepresentation.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	TimeRepresentation time;
	TimeRepresentation subb;
	UInteger32 x;

	cout << time << endl;
	time.set_seconds(2);
	time.set_nanoseconds(2);
	x = time.get_seconds();
	cout << x << endl;
	cout << time << endl;

	subb = time;
	cout << subb << endl;
}

