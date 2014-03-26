#include "NetPath.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	NetPath owdf;

	cout << owdf << endl;
	owdf.set_eventSock(5);
	owdf.set_generalSock(20);
	owdf.set_multicastAddr(13);
	owdf.set_unicastAddr(39);
	cout << owdf << endl;
}

