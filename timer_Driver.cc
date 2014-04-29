#include "classes/IntervalTimer.h"
#include "classes/ptpd_dep.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	IntervalTimer itimer[TIMER_ARRAY_SIZE];
	int sig = 0;
	Boolean b;
	int i;

	catch_alarm(sig);
	initTimer();
	timerStart(3,2,itimer);
	timerUpdate(itimer);
	b = timerExpired(3,itimer);
	cout << "timer expired " << b << endl;
	for(i=0;i<TIMER_ARRAY_SIZE;++i)
	{
		itimer[i].set_left(itimer[i].get_interval());
		itimer[i].set_expire(true);
	}
	timerUpdate(itimer);
	b = timerExpired(0,itimer);
	cout << "timer expired " << b << endl;
	timerStop(0,itimer);

}

