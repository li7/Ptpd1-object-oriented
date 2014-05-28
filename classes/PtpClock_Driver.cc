#include "PtpClock.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	PtpClock one;
	Octet x;
	UInteger16 y;

	one.set_portUuidField("eot",6);
	x = one.get_port_uuid_field(0);
	one.get_port_uuid_field();
	one.set_offsetFromMaster_seconds(32);
	one.set_offsetFromMaster_nanoseconds(16);
	cout << one << endl;
	one.get_delay_req_send_time().set_seconds(5);
	one.get_delay_req_send_time().set_nanoseconds(10);
	one.get_delay_req_receive_time().set_seconds(15);
	one.get_delay_req_receive_time().set_nanoseconds(20);
	one.get_offset_from_master().set_seconds(49);
	one.get_offset_from_master().set_nanoseconds(49);
	one.get_msgtmp().get_sync().set_grandmasterClockStratum(3);
	one.get_msgTmpHeader().set_versionPTP(VERSION_PTP);
	y = one.get_msgTmpHeader().get_versionPTP();

	cout << "x = " << x << endl << endl;
	cout << "y = " << y << endl << endl;
	cout << one << endl;
}

