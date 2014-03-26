#include "msgTmp.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	msgTmp one;
	MsgSync ci;
	MsgFollowUp dd;
	MsgDelayReq c;
	MsgDelayResp p;
	MsgManagement po;

	one.set_sync(ci);

	cout << one << endl;
}

