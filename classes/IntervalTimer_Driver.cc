#include "IntervalTimer.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	IntervalTimer interval;
	Integer32 x;

	cout << interval << endl;
	interval.set_interval(5);
	interval.set_left(20);
	interval.set_expire(false);
	x = interval.get_interval();
	cout << x << endl;
	cout << interval << endl;
}

