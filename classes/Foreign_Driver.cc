#include "Foreign.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	Foreign one;

	one.set_returnedPortNumber(19);
	one.set_returnedRecordNumber(15);

	cout << one << endl;
}

