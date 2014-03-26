#include "TimeInternal.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	TimeInternal internal;
	UInteger32 x;

	cout << internal << endl;
	internal.set_seconds(5);
	internal.set_nanoseconds(20);
	x = internal.get_seconds();
	cout << x << endl;
	cout << internal << endl;
}

