/**
 * @file   timer.c
 * @date   Wed Jun 23 09:41:26 2010
 * 
 * @brief  The timers which run the state machine.
 * 
 * Timers in the PTP daemon are run off of the signal system.  
 */

#include "classes/ptpd.h"

#define TIMER_INTERVAL 1
int	elapsed;

void 
catch_alarm(int sig)
{
	elapsed += TIMER_INTERVAL;

	DBGV("catch_alarm: elapsed %d\n", elapsed);
}

void 
initTimer(void)
{
	struct itimerval itimer;

	DBG("initTimer\n");

	signal(SIGALRM, SIG_IGN);

	elapsed = 0;
	itimer.it_value.tv_sec = itimer.it_interval.tv_sec = TIMER_INTERVAL;
	itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;

	signal(SIGALRM, catch_alarm);
	setitimer(ITIMER_REAL, &itimer, 0);
}

void 
timerUpdate(IntervalTimer * itimer)
{
	int i, delta;

	//printf("1 elapsed = %d\n",elapsed);
	delta = elapsed;
	//printf("2 delta = %d, elapsed = %d\n",delta,elapsed);
	elapsed = 0;
	//printf("3 delta = %d, elapsed = %d \n",delta,elapsed);

	if (delta <= 0)
		return;

	for (i = 0; i < TIMER_ARRAY_SIZE; ++i) {
		//printf("i (timerUpdate) = %d\n",i);
		itimer[i].set_left(itimer[i].get_left() - delta);
		if (itimer[i].get_interval() > 0 &&  itimer[i].get_left() <= 0) {
		//printf("in if timerUpdate\n");
			itimer[i].set_left(itimer[i].get_interval());
			itimer[i].set_expire(true);
			DBGV("timerUpdate: timer %u expired\n", i);
		}
	}
}

void 
timerStop(UInteger16 index, IntervalTimer * itimer)
{
	if (index >= TIMER_ARRAY_SIZE)
		return;

	itimer[index].set_interval(0);
}

void 
timerStart(UInteger16 index, UInteger16 interval, IntervalTimer * itimer)
{
	if (index >= TIMER_ARRAY_SIZE)
		return;

	itimer[index].set_expire(false);
	itimer[index].set_left(interval);
	itimer[index].set_interval(itimer[index].get_left());

	DBGV("timerStart: set timer %d to %d\n", index, interval);
}

Boolean 
timerExpired(UInteger16 index, IntervalTimer * itimer)
{
	//printf("%%index = %d\n",index);
	timerUpdate(itimer);

	if (index >= TIMER_ARRAY_SIZE)
		return false;

	if (!itimer[index].get_expire())
		return false;

	itimer[index].set_expire(false);

	return true;
}
