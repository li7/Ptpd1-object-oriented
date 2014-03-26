#include "MsgHeader.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	MsgHeader head;
	MsgHeader head2;

	head.set_messageType('1');
	head.set_subdomain(DEFAULT_PTP_DOMAIN_NAME,PTP_SUBDOMAIN_NAME_LENGTH);
	head.set_sourceCommunicationTechnology('2');
	head.set_sourcePortId(234);
	head.set_sequenceId(43);
	head.set_control('2');
	cout << "head" << endl << head << endl;
	cout << "head2" << endl << head2 << endl;
	head2 = head;
	cout << "new head2" << endl << head2 << endl;
}

