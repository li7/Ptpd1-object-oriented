#include "offset_from_master_filter.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	offset_from_master_filter ofmf;

	cout << ofmf << endl;
	ofmf.set_nsec_prev(5);
	ofmf.set_y(20);
	cout << ofmf << endl;
}

