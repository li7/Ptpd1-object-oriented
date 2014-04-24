#include "classes/ptpd.h"
#include "classes/RunTimeOpts.h"
#include "classes/PtpClock.h"
#include "classes/MsgSync.h"
#include "classes/MsgHeader.h"
#include "classes/ForeignMasterRecord.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	RunTimeOpts opts;
	PtpClock clock;
	MsgSync syncA, syncB;
	MsgHeader headerA, headerB;
	ForeignMasterRecord foreign;

	initData(&opts, &clock);
	m1(&clock);

	copyD0(&headerA, &syncA, &clock);
	bmcDataSetComparison(&headerA, &syncA, &headerB, &syncB, &clock);

	bmcStateDecision(&headerA, &syncA, &opts, &clock);

	bmc(&foreign, &opts, &clock);

}

