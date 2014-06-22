/**
 * @file   servo.c
 * @date   Tue Jul 20 16:19:19 2010
 * 
 * @brief  Code which implements the clock servo in software.
 * 
 * 
 */

#include "classes/ptpd.h"

void 
initClock(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	DBG("initClock\n");

	/* clear vars */
	ptpClock->set_master_to_slave_delay_seconds(0);
	ptpClock->set_master_to_slave_delay_nanoseconds(0);
	ptpClock->set_slave_to_master_delay_seconds(0);
	ptpClock->set_slave_to_master_delay_nanoseconds(0);
	ptpClock->set_observedVariance(0);
	ptpClock->set_observedDrift(0);/* clears clock servo accumulator (the
					 * I term) */
	ptpClock->set_owd_filt_s_exp(0);	/* clears one-way delay filter */
	ptpClock->set_halfEpoch( ptpClock->get_halfEpoch()||rtOpts->get_halfEpoch());
	rtOpts->set_halfEpoch(0);

	/* level clock */
	if (!rtOpts->get_noAdjust())
		adjFreq(0);
}

void 
updateDelay(TimeInternal * send_time, TimeInternal * recv_time,
    one_way_delay_filter * owd_filt, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	Integer16 s;
	TimeInternal slave_to_master_delay;

	DBGV("updateDelay\n");
	//printf("updateDelay\n");

	/* calc 'slave_to_master_delay' */
	subTime(&slave_to_master_delay, recv_time, send_time);

	if (rtOpts->get_maxDelay()) { /* If maxDelay is 0 then it's OFF */
		if (slave_to_master_delay.get_seconds() && rtOpts->get_maxDelay()) {
			INFO("updateDelay aborted, delay greater than 1");
			return;
		}

		if (slave_to_master_delay.get_nanoseconds() > rtOpts->get_maxDelay()) {
			INFO("updateDelay aborted, delay %d greater than "
			     "administratively set maximum %d\n",
			     slave_to_master_delay.get_nanoseconds(), 
			     rtOpts->get_maxDelay());
			return;
		}
	}

	ptpClock->set_slave_to_master_delay(slave_to_master_delay);

	/* update 'one_way_delay' */
	addTime(&ptpClock->get_one_way_delay(), &ptpClock->get_master_to_slave_delay(), &ptpClock->get_slave_to_master_delay());
	ptpClock->set_oneWayDelay_seconds(ptpClock->get_one_way_delay_seconds()/2);
	ptpClock->set_oneWayDelay_nanoseconds(ptpClock->get_one_way_delay_nanoseconds()/2);
//printf("owd: seconds = %d, nanoseconds = %d\n",ptpClock->get_one_way_delay_seconds(),ptpClock->get_one_way_delay_nanoseconds());

	if (ptpClock->get_one_way_delay_seconds()) {
		/* cannot filter with secs, clear filter */
		owd_filt->set_s_exp(0);
		owd_filt->set_nsec_prev(0);;
		return;
	}
	/* avoid overflowing filter */
	s = rtOpts->get_s();
	while (abs(owd_filt->get_y()) >> (31 - s))
		--s;

	/* crank down filter cutoff by increasing 's_exp' */
	if (owd_filt->get_s_exp() < 1)
		owd_filt->set_s_exp(1);
	else if (owd_filt->get_s_exp() < 1 << s)
		//++owd_filt->s_exp;	//NOT SURE IF SAME
		owd_filt->set_s_exp(owd_filt->get_s_exp() + 1);
	else if (owd_filt->get_s_exp() > 1 << s)
		owd_filt->set_s_exp(1 << s);

	/* filter 'one_way_delay' */
	owd_filt->set_y((owd_filt->get_s_exp() - 1) * owd_filt->get_y() / owd_filt->get_s_exp() +
	    (ptpClock->get_one_way_delay_nanoseconds() / 2 + owd_filt->get_nsec_prev() / 2) / owd_filt->get_s_exp());

	owd_filt->set_nsec_prev(ptpClock->get_one_way_delay_nanoseconds());
	ptpClock->set_oneWayDelay_nanoseconds(owd_filt->get_y());

	DBG("delay filter %d, %d\n", owd_filt->get_y(), owd_filt->get_s_exp());
}

void 
updateOffset(TimeInternal * send_time, TimeInternal * recv_time,
    offset_from_master_filter * ofm_filt, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	TimeInternal master_to_slave_delay;
	DBGV("updateOffset\n");

	/* calc 'master_to_slave_delay' */
	subTime(&master_to_slave_delay, recv_time, send_time);

	if (rtOpts->get_maxDelay()) { /* If maxDelay is 0 then it's OFF */
		if (master_to_slave_delay.get_seconds() && rtOpts->get_maxDelay()) {
			INFO("updateDelay aborted, delay greater than 1");
			//printf("updateDelay aborted, delay greater than 1");
			return;
		}

		if (master_to_slave_delay.get_nanoseconds() > rtOpts->get_maxDelay()) {
			INFO("updateDelay aborted, delay %d greater than "
			     "administratively set maximum %d\n",
			     master_to_slave_delay.get_nanoseconds(), 
			     rtOpts->get_maxDelay());
			return;
		}
	}
	ptpClock->set_master_to_slave_delay(master_to_slave_delay);

	/* update 'offset_from_master' */
	subTime(&ptpClock->get_offset_from_master(), &ptpClock->get_master_to_slave_delay(), &ptpClock->get_one_way_delay());

	if (ptpClock->get_offset_from_master_seconds()) {
		/* cannot filter with secs, clear filter */
		ofm_filt->set_nsec_prev(0);
		return;
	}
	/* filter 'offset_from_master' */
	ofm_filt->set_y(ptpClock->get_offset_from_master_nanoseconds() / 2 + ofm_filt->get_nsec_prev() / 2);
	ofm_filt->set_nsec_prev(ptpClock->get_offset_from_master_nanoseconds());
	ptpClock->set_offsetFromMaster_nanoseconds(ofm_filt->get_y());

	DBGV("offset filter %d\n", ofm_filt->get_y());
}

/**********************************START HERE*************************************/
void 
updateClock(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	Integer32 adj;
	TimeInternal timeTmp;

	DBGV("updateClock\n");

	if (rtOpts->get_maxReset()) { /* If maxReset is 0 then it's OFF */
		if (ptpClock->get_offset_from_master_seconds()) {
			INFO("updateClock aborted, offset greater than 1");
			//printf("updateClock aborted, offset greater than 1");
			goto display;
		}
		
		if (ptpClock->get_offset_from_master_nanoseconds() > 
		    rtOpts->get_maxReset()) {
			INFO("updateClock aborted, offset %d greater than ");
			//printf("updateClock aborted, offset %d greater than ");
			     ptpClock->get_offset_from_master_nanoseconds(), 
			     rtOpts->get_maxReset();
			goto display;
		}
	}

	if (ptpClock->get_offset_from_master_seconds()) {
		/* if secs, reset clock or set freq adjustment to max */
		if (!rtOpts->get_noAdjust()) {
			if (!rtOpts->get_noResetClock()) {
				getTime(&timeTmp);
				subTime(&timeTmp, &timeTmp, &ptpClock->get_offset_from_master());
				setTime(&timeTmp);
				initClock(rtOpts, ptpClock);
			} else {
				adj = ptpClock->get_offset_from_master_nanoseconds() > 0 ? ADJ_FREQ_MAX : -ADJ_FREQ_MAX;	//NOT SURE
				adjFreq(-adj);
			}
		}
	} else {
		/* the PI controller */

		/* no negative or zero attenuation */
		if (rtOpts->get_ap() < 1)
			rtOpts->set_ap(1);
		if (rtOpts->get_ai() < 1)
			rtOpts->set_ai(1);

		/* the accumulator for the I component */
		ptpClock->set_observedDrift(ptpClock->get_observed_drift() + ptpClock->get_offset_from_master_nanoseconds() / rtOpts->get_ai());

		/* clamp the accumulator to ADJ_FREQ_MAX for sanity */
		if (ptpClock->get_observed_drift() > ADJ_FREQ_MAX)
			ptpClock->set_observedDrift(ADJ_FREQ_MAX);
		else if (ptpClock->get_observed_drift() < -ADJ_FREQ_MAX)
			ptpClock->set_observedDrift(-ADJ_FREQ_MAX);

		adj = ptpClock->get_offset_from_master_nanoseconds() / rtOpts->get_ap() + ptpClock->get_observed_drift();

		/* apply controller output as a clock tick rate adjustment */
		if (!rtOpts->get_noAdjust())
			adjFreq(-adj);
	}

display:

	if (rtOpts->get_displayStats())
		displayStats(rtOpts, ptpClock);

	DBGV("master-to-slave delay:   %10ds %11dns\n",
	    ptpClock->get_master_to_slave_delay_seconds(), ptpClock->get_master_to_slave_delay_nanoseconds());
	DBGV("slave-to-master delay:   %10ds %11dns\n",
	    ptpClock->get_slave_to_master_delay_seconds(), ptpClock->get_slave_to_master_delay_nanoseconds());
	DBGV("one-way delay:           %10ds %11dns\n",
	    ptpClock->get_one_way_delay_seconds(), ptpClock->get_one_way_delay_nanoseconds());
	DBG("offset from master:      %10ds %11dns\n",
	    ptpClock->get_offset_from_master_seconds(), ptpClock->get_offset_from_master_nanoseconds());
	DBG("observed drift: %10d\n", ptpClock->get_observed_drift());
}
