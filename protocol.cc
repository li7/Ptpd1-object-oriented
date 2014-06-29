 /*
 * one more line
 * @file   protocol.c
 * @date   Wed Jun 23 09:40:39 2010
 * 
 * @brief  The code that handles the IEEE-1588 protocol and state machine
 * 
 * 
 */

#include "classes/ptpd.h"

Boolean	doInit(RunTimeOpts *, PtpClock *);
void	doState(RunTimeOpts *, PtpClock *);
void	toState(UInteger8, RunTimeOpts *, PtpClock *);

void	handle(RunTimeOpts *, PtpClock *);
void	handleSync(MsgHeader *, Octet *, ssize_t, TimeInternal *, Boolean, RunTimeOpts *, PtpClock *);
void	handleFollowUp(MsgHeader *, Octet *, ssize_t, Boolean, RunTimeOpts *, PtpClock *);
void	handleDelayReq(MsgHeader *, Octet *, ssize_t, TimeInternal *, Boolean, RunTimeOpts *, PtpClock *);
void	handleDelayResp(MsgHeader *, Octet *, ssize_t, Boolean, RunTimeOpts *, PtpClock *);
void	handleManagement(MsgHeader *, Octet *, ssize_t, Boolean, RunTimeOpts *, PtpClock *);

void	issueSync(RunTimeOpts *, PtpClock *);
void	issueFollowup(TimeInternal *, RunTimeOpts *, PtpClock *);
void	issueDelayReq(RunTimeOpts *, PtpClock *);
void	issueDelayResp(TimeInternal *, MsgHeader *, RunTimeOpts *, PtpClock *);
void	issueManagement(MsgHeader *, MsgManagement *, RunTimeOpts *, PtpClock *);

MsgSync *addForeign(Octet *, MsgHeader *, PtpClock *);


/* loop forever. doState() has a switch for the actions and events to be
   checked for 'port_state'. the actions and events may or may not change
   'port_state' by calling toState(), but once they are done we loop around
   again and perform the actions required for the new 'port_state'. */
void 
protocol(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	DBG("event POWERUP\n");

	toState(PTP_INITIALIZING, rtOpts, ptpClock);

	DBGV("Debug Initializing...");

	for (;;) {
		//printf("iteration %d\n",count++);
		if (ptpClock->get_port_state() != PTP_INITIALIZING)
			doState(rtOpts, ptpClock);
		else if (!doInit(rtOpts, ptpClock))
			return;

		if (ptpClock->get_message_activity())
			DBGV("activity\n");
		else
			DBGV("no activity\n");
	}
}

Boolean 
doInit(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	DBG("manufacturerIdentity: %s\n", MANUFACTURER_ID);

	/* initialize networking */
	//printf("listen1\n");
	netShutdown(&ptpClock->get_netPath());
	//printf("listen2\n");
	if (!netInit(&ptpClock->get_netPath(), rtOpts, ptpClock)) {
		ERROR("failed to initialize network\n");
		toState(PTP_FAULTY, rtOpts, ptpClock);
		return false;
	}
	/* initialize other stuff */
	initData(rtOpts, ptpClock);
	//printf("listen6\n");
	initTimer();
	//printf("listen7\n");
	initClock(rtOpts, ptpClock);
	//printf("listen8\n");
	m1(ptpClock);
	//printf("listen9\n");
	msgPackHeader(ptpClock->get_msgObuf(), ptpClock);
	//printf("listen10\n");

	DBG("sync message interval: %d\n", PTP_SYNC_INTERVAL_TIMEOUT(ptpClock->get_sync_interval()));
	DBG("clock identifier: %s\n", ptpClock->get_clock_identifier());
	DBG("256*log2(clock variance): %d\n", ptpClock->get_clock_variance());
	DBG("clock stratum: %d\n", ptpClock->get_clock_stratum());
	DBG("clock preferred?: %s\n", ptpClock->get_preferred() ? "yes" : "no");
	DBG("bound interface name: %s\n", rtOpts->get_ifaceName());
	DBG("communication technology: %d\n", ptpClock->get_port_communication_technology());
	DBG("uuid: %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
	    ptpClock->get_port_uuid_field(0), ptpClock->get_port_uuid_field(1), ptpClock->get_port_uuid_field(2),
	    ptpClock->get_port_uuid_field(3), ptpClock->get_port_uuid_field(4), ptpClock->get_port_uuid_field(5));
	DBG("PTP subdomain name: %s\n", ptpClock->get_subdomain_name());
	DBG("subdomain address: %hhx.%hhx.%hhx.%hhx\n",
	    ptpClock->get_subdomain_address(0), ptpClock->get_subdomain_address(1),
	    ptpClock->get_subdomain_address(2), ptpClock->get_subdomain_address(3));
	DBG("event port address: %hhx %hhx\n",
	    ptpClock->get_event_port_address(0), ptpClock->get_event_port_address(1));
	DBG("general port address: %hhx %hhx\n",
	    ptpClock->get_general_port_address(0), ptpClock->get_general_port_address(1));

	//printf("listen11\n");
	toState(PTP_LISTENING, rtOpts, ptpClock);
	//printf("listen12\n");
	return true;
}

/* handle actions and events for 'port_state' */
void 
doState(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter doState\n");
	UInteger8 state;
	int i;

	ptpClock->set_message_activity(false);
//	printf("%d\n",ptpClock->get_port_state());
	switch (ptpClock->get_port_state()) {
	case PTP_LISTENING:
	case PTP_PASSIVE:
	case PTP_SLAVE:
	case PTP_MASTER:
	//ptpClock->set_record_update(1);
	//ptpClock->set_record_update(3);
	//printf("%d\n",ptpClock->get_record_update());
		if (ptpClock->get_record_update()) {
			//printf("get here\n");
			ptpClock->set_record_update(false);
			state = bmc(&ptpClock->get_foreign(), rtOpts, ptpClock);
			//printf("#state = %d\n",ptpClock->get_port_state());
			//printf("###state = %d\n",state);
			if (state != ptpClock->get_port_state()){
				//printf("toState(state %d) 2\n",state);
				toState(state, rtOpts, ptpClock);
			}
		}
		break;

	default:
		break;
	}

	switch (ptpClock->get_port_state()) {
	case PTP_FAULTY:
		/* imaginary troubleshooting */

		DBG("event FAULT_CLEARED\n");
		toState(PTP_INITIALIZING, rtOpts, ptpClock);
		return;

	case PTP_LISTENING:
	case PTP_PASSIVE:
	case PTP_UNCALIBRATED:
	case PTP_SLAVE:
		handle(rtOpts, ptpClock);
		//printf("return from handle\n");

		i = timerExpired(SYNC_RECEIPT_TIMER, &ptpClock->get_itimer());
		//printf("%%sync receipt timer %d\n",SYNC_RECEIPT_TIMER);
		//printf("%%timerExpired = %d\n",i);
		//if (timerExpired(SYNC_RECEIPT_TIMER, &ptpClock->get_itimer())) {
		if (i) {
			//printf("event SYNC_RECEIPT_TIMEOUT_EXPIRES\n");
			ptpClock->set_numberForeignRecords(0);
			ptpClock->set_foreign_record_i(0);
			if (!rtOpts->get_slaveOnly() && ptpClock->get_clock_stratum() != 255) {
				m1(ptpClock);
				//printf("toState(PTP_MASTER)\n");
				toState(PTP_MASTER, rtOpts, ptpClock);
			} else if (ptpClock->get_port_state() != PTP_LISTENING)
				toState(PTP_LISTENING, rtOpts, ptpClock);
		}
		break;

	case PTP_MASTER:
		if (timerExpired(SYNC_INTERVAL_TIMER, &ptpClock->get_itimer())) {
			DBGV("event SYNC_INTERVAL_TIMEOUT_EXPIRES\n");
			issueSync(rtOpts, ptpClock);
		}
		handle(rtOpts, ptpClock);

		if (rtOpts->get_slaveOnly() || ptpClock->get_clock_stratum() == 255)
			toState(PTP_LISTENING, rtOpts, ptpClock);

		break;

	case PTP_DISABLED:
		//printf("handle disabled\n");
		handle(rtOpts, ptpClock);
		break;

	default:
		DBG("do unrecognized state\n");
		break;
	}
//printf("exit doState\n");
}

/* perform actions required when leaving 'port_state' and entering 'state' */
void 
toState(UInteger8 state, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter toState\n");
	ptpClock->set_message_activity(true);

	/* leaving state tasks */
	switch (ptpClock->get_port_state()) {
	case PTP_MASTER:
		timerStop(SYNC_INTERVAL_TIMER, &ptpClock->get_itimer());
		timerStart(SYNC_RECEIPT_TIMER, PTP_SYNC_RECEIPT_TIMEOUT(ptpClock->get_sync_interval()), &ptpClock->get_itimer());
		break;

	case PTP_SLAVE:
		initClock(rtOpts, ptpClock);
		break;

	default:
		break;
	}

	/* entering state tasks */
	switch (state) {
	case PTP_INITIALIZING:
		DBG("state PTP_INITIALIZING\n");
		timerStop(SYNC_RECEIPT_TIMER, &ptpClock->get_itimer());

		ptpClock->set_portState(PTP_INITIALIZING);
		break;

	case PTP_FAULTY:
		DBG("state PTP_FAULTY\n");
		timerStop(SYNC_RECEIPT_TIMER, &ptpClock->get_itimer());

		ptpClock->set_portState(PTP_FAULTY);
		break;

	case PTP_DISABLED:
		DBG("state change to PTP_DISABLED\n");
		timerStop(SYNC_RECEIPT_TIMER, &ptpClock->get_itimer());

		ptpClock->set_portState(PTP_DISABLED);
		break;

	case PTP_LISTENING:
		DBG("state PTP_LISTENING\n");

		timerStart(SYNC_RECEIPT_TIMER, PTP_SYNC_RECEIPT_TIMEOUT(ptpClock->get_sync_interval()), &ptpClock->get_itimer());

		ptpClock->set_portState(PTP_LISTENING);
		break;

	case PTP_MASTER:
		DBG("state PTP_MASTER\n");

		if (ptpClock->get_port_state() != PTP_PRE_MASTER)
			timerStart(SYNC_INTERVAL_TIMER, PTP_SYNC_INTERVAL_TIMEOUT(ptpClock->get_sync_interval()), &ptpClock->get_itimer());

		timerStop(SYNC_RECEIPT_TIMER, &ptpClock->get_itimer());

		ptpClock->set_portState(PTP_MASTER);
		break;

	case PTP_PASSIVE:
		DBG("state PTP_PASSIVE\n");
		ptpClock->set_portState(PTP_PASSIVE);
		break;

	case PTP_UNCALIBRATED:
		DBG("state PTP_UNCALIBRATED\n");
		ptpClock->set_portState(PTP_UNCALIBRATED);
		break;

	case PTP_SLAVE:
		DBG("state PTP_PTP_SLAVE\n");

		initClock(rtOpts, ptpClock);

		/*
		 * R is chosen to allow a few syncs before we first get a
		 * one-way delay estimate
		 */
		/*
		 * this is to allow the offset filter to fill for an
		 * accurate initial clock reset
		 */
		ptpClock->set_Q(0);
		ptpClock->set_R(getRand(&ptpClock->get_random_seed()) % 4 + 4);
		DBG("Q = %d, R = %d\n", ptpClock->get_Q(), ptpClock->get_R());

		ptpClock->set_waitingForFollow(false);
		ptpClock->get_delay_req_send_time().set_seconds(0);
		ptpClock->get_delay_req_send_time().set_nanoseconds(0);
		ptpClock->get_delay_req_receive_time().set_seconds(0);
		ptpClock->get_delay_req_receive_time().set_nanoseconds(0);

		timerStart(SYNC_RECEIPT_TIMER, PTP_SYNC_RECEIPT_TIMEOUT(ptpClock->get_sync_interval()), &ptpClock->get_itimer());

		ptpClock->set_portState(PTP_SLAVE);
		break;

	default:
		DBG("to unrecognized state\n");
		break;
	}

	NOTIFY("Port state changed to %s\n", translatePortState(ptpClock));

	if (rtOpts->get_displayStats())
		displayStats(rtOpts, ptpClock);
//printf("exit toState\n");
}

/* check and handle received messages */
void 
handle(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	int ret;
	ssize_t length;
	Boolean isFromSelf;
	TimeInternal time;// = {0, 0};

	time.set_seconds(0);
	time.set_nanoseconds(0);

	if (!ptpClock->get_message_activity()) {
		ret = netSelect(0, &ptpClock->get_netPath());
		if (ret < 0) {
			//printf("failed to poll sockets\n");
			PERROR("failed to poll sockets");
			toState(PTP_FAULTY, rtOpts, ptpClock);
			return;
		} else if (!ret) {
			DBGV("handle: nothing\n");
			return;
		}
		/* else length > 0 */
	}
	DBGV("handle: something\n");

	length = netRecvEvent(ptpClock->get_msgIbuf(), &time, &ptpClock->get_netPath());
	if (length < 0) {
		PERROR("failed to receive on the event socket");
		toState(PTP_FAULTY, rtOpts, ptpClock);
		return;
	} else if (!length) {
		length = netRecvGeneral(ptpClock->get_msgIbuf(), &ptpClock->get_netPath());
		if (length < 0) {
			PERROR("failed to receive on the general socket");
			toState(PTP_FAULTY, rtOpts, ptpClock);
			return;
		} else if (!length)
			return;
	}
	ptpClock->set_message_activity(true);

	if (!msgPeek(ptpClock->get_msgIbuf(), length))
		return;

	if (length < HEADER_LENGTH) {
		ERROR("message shorter than header length\n");
		toState(PTP_FAULTY, rtOpts, ptpClock);
		return;
	}
	msgUnpackHeader(ptpClock->get_msgIbuf(), &ptpClock->get_msgTmpHeader());
	 //printf("sourceUuid msgUnpackHeader returned = %d\n",*ptpClock->get_msgTmpHeader().get_sourceUuid());
        //printf("sourceCommunicationTech msgUnpackHeader returned  = %d\n",ptpClock->get_msgTmpHeader().get_sourceCommunicationTechnology());
        //printf("source port id msgUnpackHeader returned = %d\n",ptpClock->get_msgTmpHeader().get_sourcePortId());
        //printf("sequence id msgUnpackHeader returned = %d\n",ptpClock->get_msgTmpHeader().get_sequenceId());
	//printf("-header source uuid return msgunpacheader1 = %d\n",*ptpClock->get_msgTmpHeader().get_sourceUuid());

	DBGV("event Receipt of Message\n"
	    "   version %d\n"
	    "   type %d\n"
	    "   uuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n"
	    "   sequence %d\n"
	    "   time %us %dns\n",
	    ptpClock->get_msgTmpHeader().get_versionPTP(),
	    ptpClock->get_msgTmpHeader().get_control(),
	    ptpClock->get_msgTmpHeader().get_sourceUuid(0), ptpClock->get_msgTmpHeader().get_sourceUuid(1),
	    ptpClock->get_msgTmpHeader().get_sourceUuid(2), ptpClock->get_msgTmpHeader().get_sourceUuid(3),
	    ptpClock->get_msgTmpHeader().get_sourceUuid(4), ptpClock->get_msgTmpHeader().get_sourceUuid(5),
	    ptpClock->get_msgTmpHeader().get_sequenceId(),
	    time.get_seconds(), time.get_nanoseconds());

	if (ptpClock->get_msgTmpHeader().get_versionPTP() != VERSION_PTP) {
		DBGV("ignore version %d message\n", ptpClock->get_msgTmpHeader().get_versionPTP());
		return;
	}
	if (memcmp(ptpClock->get_msgTmpHeader().get_subdomain(), ptpClock->get_subdomain_name(),
	    PTP_SUBDOMAIN_NAME_LENGTH)) {
		DBGV("ignore message from subdomain %s\n", ptpClock->get_msgTmpHeader().get_subdomain());
		return;
	}
	isFromSelf = ptpClock->get_msgTmpHeader().get_sourceCommunicationTechnology() == ptpClock->get_port_communication_technology()
	    && ptpClock->get_msgTmpHeader().get_sourcePortId() == ptpClock->get_port_id_field()
	    && !memcmp(ptpClock->get_msgTmpHeader().get_sourceUuid(), ptpClock->get_port_uuid_field(), PTP_UUID_LENGTH);

	/*
	 * subtract the inbound latency adjustment if it is not a loop back
	 * and the time stamp seems reasonable
	 */
	if (!isFromSelf && time.get_seconds() > 0)
		subTime(&time, &time, &rtOpts->get_inboundLatency());

	//printf("control = %d\n",ptpClock->get_msgTmpHeader().get_control());
	switch (ptpClock->get_msgTmpHeader().get_control()) {
	case PTP_SYNC_MESSAGE:
		handleSync(&ptpClock->get_msgTmpHeader(), ptpClock->get_msgIbuf(), length, &time, isFromSelf, rtOpts, ptpClock);
		break;

	case PTP_FOLLOWUP_MESSAGE:
		handleFollowUp(&ptpClock->get_msgTmpHeader(), ptpClock->get_msgIbuf(), length, isFromSelf, rtOpts, ptpClock);
		break;

	case PTP_DELAY_REQ_MESSAGE:
		handleDelayReq(&ptpClock->get_msgTmpHeader(), ptpClock->get_msgIbuf(), length, &time, isFromSelf, rtOpts, ptpClock);
		break;

	case PTP_DELAY_RESP_MESSAGE:
		handleDelayResp(&ptpClock->get_msgTmpHeader(), ptpClock->get_msgIbuf(), length, isFromSelf, rtOpts, ptpClock);
		break;

	case PTP_MANAGEMENT_MESSAGE:
		handleManagement(&ptpClock->get_msgTmpHeader(), ptpClock->get_msgIbuf(), length, isFromSelf, rtOpts, ptpClock);
		break;

	default:
		DBG("handle: unrecognized message\n");
		break;
	}
//printf("exit handle\n");
}

void 
handleSync(MsgHeader * header, Octet * msgIbuf, ssize_t length, TimeInternal * time, Boolean isFromSelf, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter handleSync\n");
	MsgSync *sync;
	TimeInternal originTimestamp;

	if (length < SYNC_PACKET_LENGTH) {
		ERROR("short sync message\n");
		toState(PTP_FAULTY, rtOpts, ptpClock);
		return;
	}
	switch (ptpClock->get_port_state()) {
	case PTP_FAULTY:
	case PTP_INITIALIZING:
	case PTP_DISABLED:
		DBGV("handleSync: disreguard\n");
		return;

	case PTP_UNCALIBRATED:
	case PTP_SLAVE:
		if (isFromSelf) {
			DBG("handleSync: ignore from self\n");
			return;
		}
		if (getFlag(header->get_flags(), PTP_SYNC_BURST) && !ptpClock->get_burst_enabled())
			return;

		DBGV("handleSync: looking for uuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    ptpClock->get_parent_uuid(0), ptpClock->get_parent_uuid(1), ptpClock->get_parent_uuid(2),
		    ptpClock->get_parent_uuid(3), ptpClock->get_parent_uuid(4), ptpClock->get_parent_uuid(5));
//printf("source uuid = %d, parentUuid = %d\n",*header->get_sourceUuid(),*ptpClock->get_parent_uuid());
//printf("memcmp = %d\n", memcmp(header->get_sourceUuid(), ptpClock->get_parent_uuid(), PTP_UUID_LENGTH));
		//printf("%d > %d\n",header->get_sequenceId(),ptpClock->get_parent_last_sync_sequence_number());
		//printf("%d == %d\n",header->get_sourceCommunicationTechnology(),ptpClock->get_parent_communication_technology());
		//printf("%d == %d\n", header->get_sourcePortId(),ptpClock->get_parent_port_id());
		//printf("%d\n",!memcmp(header->get_sourceUuid(), ptpClock->get_parent_uuid(), PTP_UUID_LENGTH));
		if (header->get_sequenceId() > ptpClock->get_parent_last_sync_sequence_number()
		    && header->get_sourceCommunicationTechnology() == ptpClock->get_parent_communication_technology()
		    && header->get_sourcePortId() == ptpClock->get_parent_port_id()
		    && !memcmp(header->get_sourceUuid(), ptpClock->get_parent_uuid(), PTP_UUID_LENGTH)) {
			/* addForeign() takes care of msgUnpackSync() */
			ptpClock->set_record_update(true);
			sync = addForeign(ptpClock->get_msgIbuf(), &ptpClock->get_msgTmpHeader(), ptpClock);

			if (sync->get_syncInterval() != ptpClock->get_sync_interval()) {
				DBGV("message's sync interval is %d, but clock's is %d\n", sync->get_syncInterval(), ptpClock->get_sync_interval());
				/*
				 * spec recommends handling a sync interval
				 * discrepancy as a fault
				 */
			}
			ptpClock->get_sync_receive_time().set_seconds(time->get_seconds());
			ptpClock->get_sync_receive_time().set_nanoseconds(time->get_nanoseconds());

			if (!getFlag(header->get_flags(), PTP_ASSIST)) {
				ptpClock->set_waitingForFollow(false);

				toInternalTime(&originTimestamp, &sync->get_originTimestamp(), &ptpClock->get_halfEpoch());
				updateOffset(&originTimestamp, &ptpClock->get_sync_receive_time(),
				    &ptpClock->get_ofm_filt(), rtOpts, ptpClock);
				updateClock(rtOpts, ptpClock);
			} else {
				ptpClock->set_waitingForFollow(true);
			}

			s1(header, sync, ptpClock);

			ptpClock->set_R(ptpClock->get_R() - 1);
			if (!(ptpClock->get_R())) {
				issueDelayReq(rtOpts, ptpClock);

				ptpClock->set_Q(0);
				ptpClock->set_R(getRand(&ptpClock->get_random_seed()) % (PTP_DELAY_REQ_INTERVAL - 2) + 2);
				DBG("Q = %d, R = %d\n", ptpClock->get_Q(), ptpClock->get_R());
			}
			DBGV("SYNC_RECEIPT_TIMER reset\n");
			timerStart(SYNC_RECEIPT_TIMER, PTP_SYNC_RECEIPT_TIMEOUT(ptpClock->get_sync_interval()), &ptpClock->get_itimer());

			if (rtOpts->get_recordFP() != NULL) 
				fprintf(rtOpts->get_recordFP(), "%d %llu\n", 
					header->get_sequenceId(), 
					((time->get_seconds() * 1000000000ULL) + 
					 time->get_nanoseconds()));

		} else {
			DBGV("handleSync: unwanted\n");
		}

	case PTP_MASTER:
	default:
		if (header->get_sourceCommunicationTechnology() == ptpClock->get_clock_communication_technology()
		    || header->get_sourceCommunicationTechnology() == PTP_DEFAULT
		    || ptpClock->get_clock_communication_technology() == PTP_DEFAULT) {
			if (!isFromSelf) {
				ptpClock->set_record_update(true);
				addForeign(ptpClock->get_msgIbuf(), &ptpClock->get_msgTmpHeader(), ptpClock);
			} else if (ptpClock->get_port_state() == PTP_MASTER && ptpClock->get_clock_followup_capable()) {
				addTime(time, time, &rtOpts->get_outboundLatency());
				issueFollowup(time, rtOpts, ptpClock);
			}
		}
		break;
	}
//printf("exit handleSync\n");
}

void 
handleFollowUp(MsgHeader * header, Octet * msgIbuf, ssize_t length, Boolean isFromSelf, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter handleFollowUp\n");
	MsgFollowUp *follow;
	TimeInternal preciseOriginTimestamp;

	if (length < FOLLOW_UP_PACKET_LENGTH) {
		ERROR("short folow up message\n");
		toState(PTP_FAULTY, rtOpts, ptpClock);
		return;
	}
	switch (ptpClock->get_port_state()) {
	case PTP_SLAVE:
		if (isFromSelf) {
			DBG("handleFollowUp: ignore from self\n");
			return;
		}
		if (getFlag(header->get_flags(), PTP_SYNC_BURST) && !ptpClock->get_burst_enabled())
			return;

		DBGV("handleFollowUp: looking for uuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    ptpClock->get_parent_uuid(0), ptpClock->get_parent_uuid(1), ptpClock->get_parent_uuid(2),
		    ptpClock->get_parent_uuid(3), ptpClock->get_parent_uuid(4), ptpClock->get_parent_uuid(5));

		follow = &ptpClock->get_msgtmp().get_follow();
		msgUnpackFollowUp(ptpClock->get_msgIbuf(), follow);

		if (ptpClock->get_waitingForFollow()
		    && follow->get_associatedSequenceId() == ptpClock->get_parent_last_sync_sequence_number()
		    && header->get_sourceCommunicationTechnology() == ptpClock->get_parent_communication_technology()
		    && header->get_sourcePortId() == ptpClock->get_parent_port_id()
		    && !memcmp(header->get_sourceUuid(), ptpClock->get_parent_uuid(), PTP_UUID_LENGTH)) {
			ptpClock->set_waitingForFollow(false);

			toInternalTime(&preciseOriginTimestamp, &follow->get_preciseOriginTimestamp(), &ptpClock->get_halfEpoch());
			updateOffset(&preciseOriginTimestamp, &ptpClock->get_sync_receive_time(),
			    &ptpClock->get_ofm_filt(), rtOpts, ptpClock);
			updateClock(rtOpts, ptpClock);
		} else {
			DBGV("handleFollowUp: unwanted\n");
		}
		break;

	default:
		DBGV("handleFollowUp: disreguard\n");
		return;
	}
//printf("exit handleFollowUp\n");
}

void 
handleDelayReq(MsgHeader * header, Octet * msgIbuf, ssize_t length, TimeInternal * time, Boolean isFromSelf, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter handleDelayReq\n");
	if (length < DELAY_REQ_PACKET_LENGTH) {
		ERROR("short delay request message\n");
		toState(PTP_FAULTY, rtOpts, ptpClock);
		return;
	}
	switch (ptpClock->get_port_state()) {
	case PTP_MASTER:
		if (isFromSelf) {
			DBG("handleDelayReq: ignore from self\n");
			return;
		}
		if (header->get_sourceCommunicationTechnology() == ptpClock->get_clock_communication_technology()
		    || header->get_sourceCommunicationTechnology() == PTP_DEFAULT
		    || ptpClock->get_clock_communication_technology() == PTP_DEFAULT) {
			issueDelayResp(time, &ptpClock->get_msgTmpHeader(), rtOpts, ptpClock);
		}
		break;

	case PTP_SLAVE:
		if (isFromSelf) {
			DBG("handleDelayReq: self\n");

			ptpClock->get_delay_req_send_time().set_seconds(time->get_seconds());
			ptpClock->get_delay_req_send_time().set_nanoseconds(time->get_nanoseconds());

			addTime(&ptpClock->get_delay_req_send_time(), &ptpClock->get_delay_req_send_time(), &rtOpts->get_outboundLatency());

			if (ptpClock->get_delay_req_receive_time().get_seconds()) {
//printf("updateDelay 2\n");
				updateDelay(&ptpClock->get_delay_req_send_time(), 
					    &ptpClock->get_delay_req_receive_time(),
					    &ptpClock->get_owd_filt(), rtOpts, 
					    ptpClock);

				ptpClock->get_delay_req_send_time().set_seconds(0);
				ptpClock->get_delay_req_send_time().set_nanoseconds(0);
				ptpClock->get_delay_req_receive_time().set_seconds(0);
				ptpClock->get_delay_req_receive_time().set_nanoseconds(0);
			}
		}
		break;

	default:
		DBGV("handleDelayReq: disreguard\n");
		return;
	}
//printf("exit handleDelayReq\n");
}

void 
handleDelayResp(MsgHeader * header, Octet * msgIbuf, ssize_t length, Boolean isFromSelf, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter handleDelayResp\n");
	MsgDelayResp *resp;

	if (length < DELAY_RESP_PACKET_LENGTH) {
		ERROR("short delay request message\n");
		toState(PTP_FAULTY, rtOpts, ptpClock);
		return;
	}
	switch (ptpClock->get_port_state()) {
	case PTP_SLAVE:
		if (isFromSelf) {
			DBG("handleDelayResp: ignore from self\n");
			return;
		}
		resp = &ptpClock->get_msgtmp().get_resp();
		msgUnpackDelayResp(ptpClock->get_msgIbuf(), resp);

/*printf("%d\n",ptpClock->get_sentDelayReq());
printf("%d == %d\n",resp->get_requestingSourceSequenceId(),ptpClock->get_sentDelayReqSequenceId());
printf("%d == %d\n",resp->get_requestingSourceCommunicationTechnology(),ptpClock->get_port_communication_technology());
printf("%d == %d\n",resp->get_requestingSourcePortId(),ptpClock->get_port_id_field());
printf("%d\n",!memcmp(resp->get_requestingSourceUuid(), ptpClock->get_port_uuid_field(), PTP_UUID_LENGTH));
printf("%d == %d\n",header->get_sourceCommunicationTechnology(),ptpClock->get_parent_communication_technology());
printf("%d == %d\n",header->get_sourcePortId(),ptpClock->get_parent_port_id());
printf("%d\n",!memcmp(header->get_sourceUuid(), ptpClock->get_parent_uuid(), PTP_UUID_LENGTH));
*/

		if (ptpClock->get_sentDelayReq()
		    && resp->get_requestingSourceSequenceId() == ptpClock->get_sentDelayReqSequenceId()
		    && resp->get_requestingSourceCommunicationTechnology() == ptpClock->get_port_communication_technology()
		    && resp->get_requestingSourcePortId() == ptpClock->get_port_id_field()
		    && !memcmp(resp->get_requestingSourceUuid(), ptpClock->get_port_uuid_field(), PTP_UUID_LENGTH)
		    && header->get_sourceCommunicationTechnology() == ptpClock->get_parent_communication_technology()
		    && header->get_sourcePortId() == ptpClock->get_parent_port_id()
		    && !memcmp(header->get_sourceUuid(), ptpClock->get_parent_uuid(), PTP_UUID_LENGTH)) {
			ptpClock->set_sentDelayReq(false);

			toInternalTime(&ptpClock->get_delay_req_receive_time(), &resp->get_delayReceiptTimestamp(), &ptpClock->get_halfEpoch());

//printf("del req send time = %d\n",ptpClock->get_delay_req_send_time().get_seconds());
			if (ptpClock->get_delay_req_send_time().get_seconds()) {
//printf("updateDelay 1\n");
				updateDelay(&ptpClock->get_delay_req_send_time(), &ptpClock->get_delay_req_receive_time(),
				    &ptpClock->get_owd_filt(), rtOpts, ptpClock);

				ptpClock->get_delay_req_send_time().set_seconds(0);
				ptpClock->get_delay_req_send_time().set_nanoseconds(0);
				ptpClock->get_delay_req_receive_time().set_seconds(0);
				ptpClock->get_delay_req_receive_time().set_nanoseconds(0);
			}
		} else {
			DBGV("handleDelayResp: unwanted\n");
		}
		break;

	default:
		DBGV("handleDelayResp: disreguard\n");
		return;
	}
//printf("exit handleDelayResp\n");
}

void 
handleManagement(MsgHeader * header, Octet * msgIbuf, ssize_t length, Boolean isFromSelf, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter handleManagement\n");
	MsgManagement *manage;

	UInteger8 state;

	if (ptpClock->get_port_state() == PTP_INITIALIZING)
		return;

	manage = &ptpClock->get_msgtmp().get_manage();
	msgUnpackManagement(ptpClock->get_msgIbuf(), manage);

	if ((manage->get_targetCommunicationTechnology() == ptpClock->get_clock_communication_technology()
	    && !memcmp(manage->get_targetUuid(), ptpClock->get_clock_uuid_field(), PTP_UUID_LENGTH))
	    || ((manage->get_targetCommunicationTechnology() == PTP_DEFAULT
	    || manage->get_targetCommunicationTechnology() == ptpClock->get_clock_communication_technology())
	    && !sum(manage->get_targetUuid(), PTP_UUID_LENGTH))) {
		switch (manage->get_managementMessageKey()) {
		case PTP_MM_OBTAIN_IDENTITY:
		case PTP_MM_GET_DEFAULT_DATA_SET:
		case PTP_MM_GET_CURRENT_DATA_SET:
		case PTP_MM_GET_PARENT_DATA_SET:
		case PTP_MM_GET_PORT_DATA_SET:
		case PTP_MM_GET_GLOBAL_TIME_DATA_SET:
		case PTP_MM_GET_FOREIGN_DATA_SET:
			issueManagement(header, manage, rtOpts, ptpClock);
			break;

		default:
			ptpClock->set_record_update(true);
			state = msgUnloadManagement(ptpClock->get_msgIbuf(), manage, ptpClock, rtOpts);
			if (state != ptpClock->get_port_state())
				//printf("toState(state %d)\n",state);
				toState(state, rtOpts, ptpClock);
			break;
		}
	} else {
		DBG("handleManagement: unwanted\n");
	}
//printf("exit handleManagement\n");
}

/* pack and send various messages */
void 
issueSync(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter issueSync\n");
	TimeInternal internalTime;
	TimeRepresentation originTimestamp;

	//++ptpClock->last_sync_event_sequence_number;
	ptpClock->set_lastSyncEventSequenceNumber(ptpClock->get_last_sync_event_sequence_number() + 1);
	ptpClock->set_grandmasterSequenceNumber(ptpClock->get_last_sync_event_sequence_number());

	getTime(&internalTime);
	fromInternalTime(&internalTime, &originTimestamp, ptpClock->get_halfEpoch());
	msgPackSync(ptpClock->get_msgObuf(), false, &originTimestamp, ptpClock);

	if (!netSendEvent(ptpClock->get_msgObuf(), SYNC_PACKET_LENGTH, &ptpClock->get_netPath()))
		toState(PTP_FAULTY, rtOpts, ptpClock);
	else
		DBGV("sent sync message\n");
//printf("exit issueSync\n");
}

void 
issueFollowup(TimeInternal * time, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter issueFollowUp\n");
	TimeRepresentation preciseOriginTimestamp;

	//++ptpClock->last_general_event_sequence_number;
	ptpClock->set_lastGeneralEventSequenceNumber(ptpClock->get_last_general_event_sequence_number() + 1);

	fromInternalTime(time, &preciseOriginTimestamp, ptpClock->get_halfEpoch());
	msgPackFollowUp(ptpClock->get_msgObuf(), ptpClock->get_last_sync_event_sequence_number(), &preciseOriginTimestamp, ptpClock);

	if (!netSendGeneral(ptpClock->get_msgObuf(), FOLLOW_UP_PACKET_LENGTH, &ptpClock->get_netPath()))
		toState(PTP_FAULTY, rtOpts, ptpClock);
	else
		DBGV("sent followup message\n");
//printf("exit issueFollowUp\n");
}

void 
issueDelayReq(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter issueDelayReq\n");
	TimeInternal internalTime;
	TimeRepresentation originTimestamp;

	ptpClock->set_sentDelayReq(true);
	//ptpClock->sentDelayReqSequenceId = ++ptpClock->last_sync_event_sequence_number;
	
	ptpClock->set_lastSyncEventSequenceNumber(ptpClock->get_last_sync_event_sequence_number() + 1);
	ptpClock->set_sentDelayReqSequenceId(ptpClock->get_last_sync_event_sequence_number());

	getTime(&internalTime);
	fromInternalTime(&internalTime, &originTimestamp, ptpClock->get_halfEpoch());
	msgPackDelayReq(ptpClock->get_msgObuf(), false, &originTimestamp, ptpClock);

	if (!netSendEvent(ptpClock->get_msgObuf(), DELAY_REQ_PACKET_LENGTH, &ptpClock->get_netPath()))
		toState(PTP_FAULTY, rtOpts, ptpClock);
	else
		DBGV("sent delay request message\n");
//nprintf("exit issueDelayReq\n");
}

/*********************START HERE*******************/
void 
issueDelayResp(TimeInternal * time, MsgHeader * header, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter issueDelayResp\n");
	TimeRepresentation delayReceiptTimestamp;

	//++ptpClock->last_general_event_sequence_number;
	ptpClock->set_lastGeneralEventSequenceNumber(ptpClock->get_last_general_event_sequence_number() + 1);

	fromInternalTime(time, &delayReceiptTimestamp, ptpClock->get_halfEpoch());
	msgPackDelayResp(ptpClock->get_msgObuf(), header, &delayReceiptTimestamp, ptpClock);

	if (!netSendGeneral(ptpClock->get_msgObuf(), DELAY_RESP_PACKET_LENGTH, &ptpClock->get_netPath()))
		toState(PTP_FAULTY, rtOpts, ptpClock);
	else
		DBGV("sent delay response message\n");
//printf("exit issueDelayResp\n");
}

void 
issueManagement(MsgHeader * header, MsgManagement * manage, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
//printf("enter issueManagament\n");
	UInteger16 length;

	//++ptpClock->last_general_event_sequence_number;
	ptpClock->set_lastGeneralEventSequenceNumber(ptpClock->get_last_general_event_sequence_number() + 1);

	if (!(length = msgPackManagementResponse(ptpClock->get_msgObuf(), header, manage, ptpClock)))
		return;

	if (!netSendGeneral(ptpClock->get_msgObuf(), length, &ptpClock->get_netPath()))
		toState(PTP_FAULTY, rtOpts, ptpClock);
	else
		DBGV("sent management message\n");
//printf("exit issueManagament\n");
}

/* add or update an entry in the foreign master data set */
MsgSync *
addForeign(Octet * buf, MsgHeader * header, PtpClock * ptpClock)
{
//printf("enter addForeign\n");
	int i, j;
	Boolean found = false;

	DBGV("updateForeign\n");

	j = ptpClock->get_foreign_record_best();
	//cout << "j = " << j << endl;
	for (i = 0; i < ptpClock->get_number_foreign_records(); ++i) {
	//cout << "i = " << i << endl;
        //printf("%d == %d\n",header->get_sourceCommunicationTechnology() ,ptpClock->get_foreign(j).get_foreign_master_communication_technology());
        //printf("%d == %d\n",header->get_sourcePortId(),ptpClock->get_foreign(j).get_foreign_master_port_id());
        //printf("%d\n",!memcmp(header->get_sourceUuid(), ptpClock->get_foreign(j).get_foreign_master_uuid(), PTP_UUID_LENGTH));

		if (header->get_sourceCommunicationTechnology() == ptpClock->get_foreign(j).get_foreign_master_communication_technology()
		    && header->get_sourcePortId() == ptpClock->get_foreign(j).get_foreign_master_port_id()
		    && !memcmp(header->get_sourceUuid(), ptpClock->get_foreign(j).get_foreign_master_uuid(), PTP_UUID_LENGTH)) {
			//++ptpClock->foreign[j].foreign_master_syncs;
			ptpClock->get_foreign(j).set_foreign_master_syncs(ptpClock->get_foreign(j).get_foreign_master_syncs() + 1);
			found = true;
			DBGV("updateForeign: update record %d\n", j);
			break;
		}
		j = (j + 1) % ptpClock->get_number_foreign_records();
	}

	if (!found) {
		if (ptpClock->get_number_foreign_records() < ptpClock->get_max_foreign_records())
			//++ptpClock->number_foreign_records;
			ptpClock->set_numberForeignRecords(ptpClock->get_number_foreign_records() + 1);
		j = ptpClock->get_foreign_record_i();

		ptpClock->get_foreign(j).set_foreign_master_communication_technology(header->get_sourceCommunicationTechnology());
		ptpClock->get_foreign(j).set_foreign_master_port_id(header->get_sourcePortId());
		ptpClock->get_foreign(j).set_foreign_master_uuid(header->get_sourceUuid(), PTP_UUID_LENGTH);

		/*DBG("updateForeign: new record (%d,%d) %d %d %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    ptpClock->get_foreign_record_i(), ptpClock->get_number_foreign_records(),
		    ptpClock->get_foreign(j).get_foreign_master_communication_technology(),
		    ptpClock->get_foreign(j).get_foreign_master_port_id(),
		    ptpClock->get_foreign(j).get_foreign_master_uuid(0), ptpClock->get_foreign(j).get_foreign_master_uuid(1),
		    ptpClock->get_foreign(j).get_foreign_master_uuid(2), ptpClock->get_foreign(j).get_foreign_master_uuid(3),
		    ptpClock->get_foreign(j).get_foreign_master_uuid(4), ptpClock->get_foreign(j).get_foreign_master_uuid(5));
*/
		ptpClock->set_foreign_record_i((ptpClock->get_foreign_record_i() + 1) % ptpClock->get_max_foreign_records());
	}
	msgUnpackHeader(buf, &ptpClock->get_foreign(j).get_header());
	//msgUnpackHeader(buf, &ptpClock->foreign[j].get_header());
	 //printf("versionPTP (addForeign) = %d\n",ptpClock->get_foreign(j).get_header().get_versionPTP()); 
	 //printf("****sourceUuid msgUnpackHeader returned (used for foreign[j].header) = %d\n",*ptpClock->get_foreign(j).get_header().get_sourceUuid());
        //printf("****sourceCommunicationTech msgUnpackHeader returned (used for foreign[j].header) = %d\n",ptpClock->get_foreign(j).get_header().get_sourceCommunicationTechnology());
        //printf("****source port id msgUnpackHeader returned (used for foreign[j].header) = %d\n",ptpClock->get_foreign(j).get_header().get_sourcePortId());
        //printf("****sequence id msgUnpackHeader returned (used for foreign[j].header) = %d\n",ptpClock->get_foreign(j).get_header().get_sequenceId());
	msgUnpackSync(buf, &ptpClock->get_foreign(j).get_sync());

	return &ptpClock->get_foreign(j).get_sync();
//printf("exit addForeign\n");
}
