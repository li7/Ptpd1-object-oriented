/**
 * @file   sys.c
 * @date   Tue Jul 20 16:19:46 2010
 * 
 * @brief  Code to call kernel time routines and also display server statistics.
 * 
 * 
 */

#include "classes/ptpd.h"


int 
isTimeInternalNegative(const TimeInternal * p)
{
	return (p->get_seconds() < 0) || (p->get_nanoseconds() < 0);
}


int 
snprint_TimeInternal(char *s, int max_len, const TimeInternal * p)
{
	int len = 0;

	if (isTimeInternalNegative(p))
		len += snprintf(&s[len], max_len - len, "-");

	len += snprintf(&s[len], max_len - len, "%d.%09d",
	    abs(p->get_seconds()), abs(p->get_nanoseconds()));

	return len;
}



int 
snprint_ClockIdentity(char *s, int max_len, const Octet uuid[PTP_UUID_LENGTH], const char *info)
{
	int len = 0;
	int i;

	if (info)
		len += snprintf(&s[len], max_len - len, "%s", info);

	for (i = 0; ;) {
		len += snprintf(&s[len], max_len - len, "%02x", (unsigned char) uuid[i]);

		if (++i >= PTP_UUID_LENGTH)
			break;

		// uncomment the line below to print a separator after each byte except the last one
		// len += snprintf(&s[len], max_len - len, "%s", "-");
	}

	return len;
}


int 
snprint_PortIdentity(char *s, int max_len, const Octet uuid[PTP_UUID_LENGTH],
                     UInteger16 portId, const char *info)
{
	int len = 0;

	if (info)
		len += snprintf(&s[len], max_len - len, "%s", info);

	len += snprint_ClockIdentity(&s[len], max_len - len, uuid, NULL);
	len += snprintf(&s[len], max_len - len, ":%02x", portId);
	return len;
}


void
message(int priority, const char *format, ...)
{
	//extern RunTimeOpts rtOpts;  //not sure what to do about this
	RunTimeOpts rtOpts;		//replaced above line with this one
	va_list ap;
	va_start(ap, format);
	if(rtOpts.get_useSysLog()) {
		static Boolean logOpened;
		if(!logOpened) {
			openlog("ptpd", 0, LOG_USER);
			logOpened = true;
		}
		vsyslog(priority, format, ap);
	} else {
		fprintf(stderr, "(ptpd %s) ",
			priority == LOG_EMERG ? "emergency" :
			priority == LOG_ALERT ? "alert" :
			priority == LOG_CRIT ? "critical" :
			priority == LOG_ERR ? "error" :
			priority == LOG_WARNING ? "warning" :
			priority == LOG_NOTICE ? "notice" :
			priority == LOG_INFO ? "info" :
			priority == LOG_DEBUG ? "debug" :
			"???");
		vfprintf(stderr, format, ap);
	}
	va_end(ap);
}

char *
translatePortState(PtpClock *ptpClock)
{
	char *s;
	switch(ptpClock->get_port_state()) {
	case PTP_INITIALIZING:  s = "init";  break;
	case PTP_FAULTY:        s = "flt";   break;
	case PTP_LISTENING:     s = "lstn";  break;
	case PTP_PASSIVE:       s = "pass";  break;
	case PTP_UNCALIBRATED:  s = "uncl";  break;
	case PTP_SLAVE:         s = "slv";   break;
	case PTP_PRE_MASTER:    s = "pmst";  break;
	case PTP_MASTER:        s = "mst";   break;
	case PTP_DISABLED:      s = "dsbl";  break;
	default:                s = "?";     break;
	}
	return s;
}

void 
displayStats(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	static int start = 1;
	static char sbuf[SCREEN_BUFSZ];
	int len = 0;
	struct timeval now;
	char time_str[MAXTIMESTR];

	if (start && rtOpts->get_csvStats()) {
		start = 0;
		printf("timestamp, state, clock ID, one way delay, "
		       "offset from master, master to slave, "
		       "slave to master, drift, variance");
		fflush(stdout);
	}
	memset(sbuf, ' ', sizeof(sbuf));

	gettimeofday(&now, 0);
	strftime(time_str, MAXTIMESTR, "%Y-%m-%d %X", localtime(&now.tv_sec));

	len += snprintf(sbuf + len, sizeof(sbuf) - len, "%s%s:%06d, %s",
		       rtOpts->get_csvStats() ? "\n" : "\rstate: ",
		       time_str, (int)now.tv_usec,
		       translatePortState(ptpClock));

	if (ptpClock->get_port_state() == PTP_SLAVE) {
		len += snprint_PortIdentity(sbuf + len, sizeof(sbuf) - len,
			 ptpClock->get_parent_uuid(), ptpClock->get_parent_port_id(), ", ");

		 /* 
		  * if grandmaster ID differs from parent port ID then also 
		  * print GM ID 
		  */
		 if (memcmp(ptpClock->get_grandmaster_uuid_field(), 
			    ptpClock->get_parent_uuid(), PTP_UUID_LENGTH)) {
			 len += snprint_ClockIdentity(sbuf + len, 
						      sizeof(sbuf) - len,
						      ptpClock->get_grandmaster_uuid_field(), 
						      " GM:");
		}

		len += snprintf(sbuf + len, sizeof(sbuf) - len, ", ");

		if (!rtOpts->get_csvStats())
			len += snprintf(sbuf + len, 
					sizeof(sbuf) - len, "owd: ");

		len += snprint_TimeInternal(sbuf + len, sizeof(sbuf) - len,
					    &ptpClock->get_one_way_delay());

		len += snprintf(sbuf + len, sizeof(sbuf) - len, ", ");

		if (!rtOpts->get_csvStats())
			len += snprintf(sbuf + len, sizeof(sbuf) - len, 
					"ofm: ");

		len += snprint_TimeInternal(sbuf + len, sizeof(sbuf) - len,
		    &ptpClock->get_offset_from_master());

		len += snprintf(sbuf + len, sizeof(sbuf) - len,
				", %s%d.%09d" ", %s%d.%09d",
				rtOpts->get_csvStats() ? "" : "stm: ",
				ptpClock->get_slave_to_master_delay_seconds(),
				abs(ptpClock->get_slave_to_master_delay_nanoseconds()),
				rtOpts->get_csvStats() ? "" : "mts: ",
				ptpClock->get_master_to_slave_delay_seconds(),
				abs(ptpClock->get_master_to_slave_delay_nanoseconds()));

		len += snprintf(sbuf + len, sizeof(sbuf) - len, 
			       ", %s%d",
			       rtOpts->get_csvStats() ? "" : "drift: ", 
			       ptpClock->get_observed_drift());

		len += snprintf(sbuf + len, sizeof(sbuf) - len, 
			       ", %s%d",
			       rtOpts->get_csvStats() ? "" : "var: ", 
			       ptpClock->get_observed_variance());
	}
	else {
		if (ptpClock->get_port_state() == PTP_MASTER) {
			len += snprint_ClockIdentity(sbuf + len, sizeof(sbuf) - len,
					ptpClock->get_clock_uuid_field(), " (ID:");
			len += snprintf(sbuf + len, sizeof(sbuf) - len, ")");
		}
	}
	write(1, sbuf, rtOpts->get_csvStats() ? len : SCREEN_MAXSZ + 1);
}

Boolean 
nanoSleep(TimeInternal * t)
{
	struct timespec ts, tr;

	ts.tv_sec = t->get_seconds();
	ts.tv_nsec = t->get_nanoseconds();

	if (nanosleep(&ts, &tr) < 0) {
		t->set_seconds(tr.tv_sec);
		t->set_nanoseconds(tr.tv_nsec);
		return false;
	}
	return true;
}

void 
getTime(TimeInternal * time)
{
#if defined(linux)

	struct timeval tv;
	gettimeofday(&tv, 0);
	time->set_seconds(tv.tv_sec);
	time->set_nanoseconds(tv.tv_usec * 1000);

#else /* FreeBSD */

	struct timespec tp;
	if (clock_gettime(CLOCK_REALTIME, &tp) < 0) {
		PERROR("clock_gettime() failed, exiting.");
		exit(0);
	}
	time->set_seconds(tp.tv_sec);
	time->set_nanoseconds(tp.tv_nsec);
#endif /* FreeBSD or Linux */
}

void 
setTime(TimeInternal * time)
{
	struct timeval tv;

	tv.tv_sec = time->get_seconds();
	tv.tv_usec = time->get_nanoseconds() / 1000;
	settimeofday(&tv, 0);

	NOTIFY("resetting system clock to %ds %dns\n", 
	       time->get_seconds(), time->get_nanoseconds());
}

UInteger16 
getRand(UInteger32 * seed)
{
	return rand_r((unsigned int *)seed);
}

Boolean 
adjFreq(Integer32 adj)
{
	struct timex t;

	if (adj > ADJ_FREQ_MAX)
		adj = ADJ_FREQ_MAX;
	else if (adj < -ADJ_FREQ_MAX)
		adj = -ADJ_FREQ_MAX;

	t.modes = MOD_FREQUENCY;
	t.freq = adj * ((1 << 16) / 1000);

	return !adjtimex(&t);
}
