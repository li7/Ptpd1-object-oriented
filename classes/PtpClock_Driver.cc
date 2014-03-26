#include "PtpClock.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	PtpClock one;
	Octet x;

	one.set_portUuidField("eot",6);
	x = one.get_port_uuid_field(2);
	one.get_port_uuid_field();
	one.set_offsetFromMaster_seconds(32);
	one.set_offsetFromMaster_nanoseconds(16);
	one.get_offset_from_master().set_seconds(49);
	one.get_offset_from_master().set_nanoseconds(49);
	one.get_msgtmp().get_sync().set_grandmasterClockStratum(3);

	cout << "x = " << x << endl << endl;
	cout << one << endl;
}

