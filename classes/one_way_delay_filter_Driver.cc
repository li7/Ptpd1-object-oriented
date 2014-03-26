#include "one_way_delay_filter.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	one_way_delay_filter owdf;

	cout << owdf << endl;
	owdf.set_nsec_prev(5);
	owdf.set_y(20);
	owdf.set_s_exp(13);
	cout << owdf << endl;
}

