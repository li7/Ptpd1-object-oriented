#include "classes/IntervalTimer.h"
#include "classes/ptpd_dep.h"
#include <iostream>
#include <string.h>

using namespace std;

main()
{
	IntervalTimer itimer[TIMER_ARRAY_SIZE];
	int sig = 0;
	Boolean b,c;
	int i;

	catch_alarm(sig);
	initTimer();
	timerStart(2,0,itimer);
	timerUpdate(itimer);
	b = timerExpired(3,itimer);
	cout << "timer expired " << b << " expected 0" << endl;
	for(i=1;i<TIMER_ARRAY_SIZE;++i)
	{
		itimer[i].set_left(itimer[i].get_interval());
		itimer[i].set_expire(true);
	}
	timerUpdate(itimer);
	b = timerExpired(2,itimer);
	timerStart(1,0,itimer);
	c = timerExpired(1,itimer);
	cout << "timer 2 expired " << b << " expected 1" << endl;
	cout << "timer 1 expired " << c << " expected 0" << endl;
	timerStop(2,itimer);

}

