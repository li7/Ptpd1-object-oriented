#include "DefaultData.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	DefaultData one;

	one.set_clockCommunicationTechnology('f');
	one.set_clockPortField(15);

	cout << one << endl;
}

