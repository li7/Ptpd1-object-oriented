#include "RunTimeOpts.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	RunTimeOpts one;

	one.set_noAdjust(false);
	one.set_syncInterval(15);

	cout << one << endl;
}

