#include "ForeignMasterRecord.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	ForeignMasterRecord one;
	MsgHeader head;
	MsgSync sync;
	UInteger8 x;

	one.set_foreign_master_communication_technology('x');
	one.set_foreign_master_port_id(383);
	one.set_foreign_master_syncs(324);
	cout << one << endl;
}

