#include "classes/ptpd.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	RunTimeOpts opts;
	PtpClock clock;
	TimeInternal time;
	one_way_delay_filter owdf;
	offset_from_master_filter ofmf;

	initClock(opts, clock);
}

