/**
 * @file   ptpd.c
 * @date   Wed Jun 23 10:13:38 2010
 * 
 * @brief  The main() function for the PTP daemon
 * 
 * This file contains very little code, as should be obvious,
 * and only serves to tie together the rest of the daemon.
 * All of the default options are set here, but command line
 * arguments are processed in the ptpdStartup() routine called
 * below.
 */

#include "classes/ptpd.h"

RunTimeOpts rtOpts;			/* statically allocated run-time
					 * configuration data */

int
main(int argc, char **argv)
{
	PtpClock *ptpClock;
	Integer16 ret;

	/* initialize run-time options to reasonable values */
	rtOpts.set_syncInterval(DEFAULT_SYNC_INTERVAL);
	rtOpts.set_subdomainName(DEFAULT_PTP_DOMAIN_NAME, PTP_SUBDOMAIN_NAME_LENGTH);
	rtOpts.set_clockIdentifier(IDENTIFIER_DFLT, PTP_CODE_STRING_LENGTH);
	rtOpts.set_clockVariance(DEFAULT_CLOCK_VARIANCE);
	rtOpts.set_clockStratum(DEFAULT_CLOCK_STRATUM);
	rtOpts.set_unicastAddress(0,0);
	rtOpts.set_inboundLatency_nanoseconds(DEFAULT_INBOUND_LATENCY);
	rtOpts.set_outboundLatency_nanoseconds(DEFAULT_OUTBOUND_LATENCY);
	rtOpts.set_noResetClock(DEFAULT_NO_RESET_CLOCK);
	rtOpts.set_s(DEFAULT_DELAY_S);
	rtOpts.set_ap(DEFAULT_AP);
	rtOpts.set_ai(DEFAULT_AI);
	rtOpts.set_max_foreign_records(DEFAULT_MAX_FOREIGN_RECORDS);
	rtOpts.set_currentUtcOffset(DEFAULT_UTC_OFFSET);
	rtOpts.set_logFd(-1);
	rtOpts.set_recordFP(NULL);
	rtOpts.set_useSysLog(false);
	rtOpts.set_ttl(1);
	
	if (!(ptpClock = ptpdStartup(argc, argv, &ret, &rtOpts)))
		return ret;

	if (rtOpts.get_probe()) {
		probe(&rtOpts, ptpClock);
	} else {
		/* do the protocol engine */
		protocol(&rtOpts, ptpClock);
	}

	ptpdShutdown();

	NOTIFY("self shutdown, probably due to an error\n");
	return 1;
}
