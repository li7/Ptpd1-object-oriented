/**
 * @file   bmc.c
 * @date   Wed Jun 23 09:36:09 2010
 * 
 * @brief  Best master clock selection code.
 * 
 * The functions in this file are used by the daemon to select the
 * best master clock from any number of possibilities.
 */

#include "classes/ptpd.h"
#include "classes/datatypes_dep.h"
#include "classes/RunTimeOpts.h"
#include "classes/PtpClock.h"
#include "classes/MsgSync.h"
#include "classes/MsgHeader.h"
#include "classes/ForeignMasterRecord.h"

void 
initData(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	DBG("initData\n");

	if (rtOpts->get_slaveOnly())
		rtOpts->set_clockStratum(255);

	/* Port configuration data set */
	ptpClock->set_lastSyncEventSequenceNumber(0);
	ptpClock->set_lastGeneralEventSequenceNumber(0);
	ptpClock->set_portIdField(1);
	ptpClock->set_burstEnabled(BURST_ENABLED);

	/* Default data set */
	ptpClock->set_clockCommunicationTechnology(ptpClock->get_port_communication_technology());
	//printf("port uuid field = %d\n",ptpClock->get_port_uuid_field());
	ptpClock->set_clockUuidField(ptpClock->get_port_uuid_field(), PTP_UUID_LENGTH);
	ptpClock->set_clockPortField(0);
	ptpClock->set_clockStratum(rtOpts->get_clockStratum());
	ptpClock->set_clockIdentifier(rtOpts->get_clockIdentifier(), PTP_CODE_STRING_LENGTH);
	ptpClock->set_syncInterval(rtOpts->get_syncInterval());

	ptpClock->set_clockVariance(rtOpts->get_clockVariance());	/* see spec 7.7 */
	ptpClock->set_clockFollowupCapable(CLOCK_FOLLOWUP);
	ptpClock->set_preferred(rtOpts->get_clockPreferred());
	ptpClock->set_initializable(INITIALIZABLE);
	ptpClock->set_externalTiming(EXTERNAL_TIMING);
	ptpClock->set_isBoundaryClock(BOUNDARY_CLOCK);
	ptpClock->set_subdomainName(rtOpts->get_subdomainName(), PTP_SUBDOMAIN_NAME_LENGTH);
	ptpClock->set_numberPorts(NUMBER_PORTS);
	ptpClock->set_numberForeignRecords(0);
	ptpClock->set_max_foreign_records(rtOpts->get_max_foreign_records());

	/* Global time properties data set */
	ptpClock->set_currentUtcOffset(rtOpts->get_currentUtcOffset());
	ptpClock->set_epochNumber(rtOpts->get_epochNumber());

	/* other stuff */
	ptpClock->set_random_seed(ptpClock->get_port_uuid_field(PTP_UUID_LENGTH - 1));
}

/* see spec table 18 */
void 
m1(PtpClock * ptpClock)
{
//	printf("In m1\n");
	/* Default data set */
	ptpClock->set_stepsRemoved(0);
	ptpClock->set_offsetFromMaster_seconds(0);
	ptpClock->set_offsetFromMaster_nanoseconds(0);
	ptpClock->set_oneWayDelay_seconds(0);
	ptpClock->set_oneWayDelay_nanoseconds(0);

	/* Parent data set */
	ptpClock->set_parentCommunicationTechnology(ptpClock->get_clock_communication_technology());
	ptpClock->set_parentUuid(ptpClock->get_clock_uuid_field(), PTP_UUID_LENGTH);
	ptpClock->set_parentPortId(ptpClock->get_clock_port_id_field());
	ptpClock->set_parentLastSyncSequenceNumber(0);
	ptpClock->set_parentFollowupCapable(ptpClock->get_clock_followup_capable());
	ptpClock->set_parentExternalTiming(ptpClock->get_external_timing());
	ptpClock->set_parentVariance(ptpClock->get_clock_variance());
	ptpClock->set_grandmasterCommunicationTechnology(ptpClock->get_clock_communication_technology());
	ptpClock->set_grandmasterUuidField(ptpClock->get_clock_uuid_field(), PTP_UUID_LENGTH);
	ptpClock->set_grandmasterPortIdField(ptpClock->get_clock_port_id_field());
	ptpClock->set_grandmasterStratum(ptpClock->get_clock_stratum());
	ptpClock->set_grandmasterIdentifier(ptpClock->get_clock_identifier(), PTP_CODE_STRING_LENGTH);
	ptpClock->set_grandmasterVariance(ptpClock->get_clock_variance());
	ptpClock->set_grandmasterPreferred(ptpClock->get_preferred());
	ptpClock->set_grandmasterIsBoundaryClock(ptpClock->get_is_boundary_clock());
	ptpClock->set_grandmasterSequenceNumber(ptpClock->get_last_sync_event_sequence_number());
//printf("exit m1\n");
}

/* see spec table 21 */
void 
s1(MsgHeader * header, MsgSync * sync, PtpClock * ptpClock)
{
//printf("enter s1\n");
	/* Current data set */
	ptpClock->set_stepsRemoved(sync->get_localStepsRemoved() + 1);

	/* Parent data set */
	ptpClock->set_parentCommunicationTechnology(header->get_sourceCommunicationTechnology());
	//printf("--parent comm tech (s1) = %d\n",ptpClock->get_parent_communication_technology());
	//printf("--header source com tech (s1) = %d\n",header->get_sourceCommunicationTechnology());
	ptpClock->set_parentUuid(header->get_sourceUuid(), PTP_UUID_LENGTH);
	//printf("-header source uuid (s1) = %d\n",*header->get_sourceUuid());
	//printf("-parent uuid (s1) = %d\n",*ptpClock->get_parent_uuid());
	ptpClock->set_parentPortId(header->get_sourcePortId());
	ptpClock->set_parentLastSyncSequenceNumber(header->get_sequenceId());
	ptpClock->set_parentFollowupCapable(getFlag(header->get_flags(), PTP_ASSIST));
	ptpClock->set_parentExternalTiming(getFlag(header->get_flags(), PTP_EXT_SYNC));
	ptpClock->set_parentVariance(sync->get_localClockVariance());
	ptpClock->set_grandmasterCommunicationTechnology(sync->get_grandmasterCommunicationTechnology());
	ptpClock->set_grandmasterUuidField(sync->get_grandmasterClockUuid(), PTP_UUID_LENGTH);
	ptpClock->set_grandmasterPortIdField(sync->get_grandmasterPortId());
	ptpClock->set_grandmasterStratum(sync->get_grandmasterClockStratum());
	ptpClock->set_grandmasterIdentifier(sync->get_grandmasterClockIdentifier(), PTP_CODE_STRING_LENGTH);
	ptpClock->set_grandmasterVariance(sync->get_grandmasterClockVariance());
	ptpClock->set_grandmasterPreferred(sync->get_grandmasterPreferred());
	ptpClock->set_grandmasterIsBoundaryClock(sync->get_grandmasterIsBoundaryClock());
	ptpClock->set_grandmasterSequenceNumber(sync->get_grandmasterSequenceId());

	/* Global time properties data set */
	ptpClock->set_currentUtcOffset(sync->get_currentUTCOffset());
	ptpClock->set_leap59(getFlag(header->get_flags(), PTP_LI_59));
	ptpClock->set_leap61(getFlag(header->get_flags(), PTP_LI_61));
	ptpClock->set_epochNumber(sync->get_epochNumber());
//printf("exit s1\n");
}

void 
copyD0(MsgHeader * header, MsgSync * sync, PtpClock * ptpClock)
{
	sync->set_grandmasterCommunicationTechnology(ptpClock->get_clock_communication_technology());
	sync->set_grandmasterClockUuid(ptpClock->get_port_uuid_field(), PTP_UUID_LENGTH);
	sync->set_grandmasterPortId(ptpClock->get_port_id_field());
	sync->set_grandmasterClockStratum(ptpClock->get_clock_stratum());
	sync->set_grandmasterClockIdentifier(ptpClock->get_clock_identifier(), PTP_CODE_STRING_LENGTH);
	sync->set_grandmasterClockVariance(ptpClock->get_clock_variance());
	sync->set_grandmasterIsBoundaryClock(ptpClock->get_is_boundary_clock());
	sync->set_grandmasterPreferred(ptpClock->get_preferred());
	sync->set_localStepsRemoved(ptpClock->get_steps_removed());
	header->set_sourceCommunicationTechnology(ptpClock->get_clock_communication_technology());
	//printf("--source communication tech (copyD0) = %d\n",header->get_sourceCommunicationTechnology());
	//printf("--clock communication tech (copyD0) = %d\n",ptpClock->get_clock_communication_technology());
	header->set_sourceUuid(ptpClock->get_port_uuid_field(), PTP_UUID_LENGTH);
	//printf("-port uuid field (copyD0) = %d\n", *ptpClock->get_port_uuid_field());
	//printf("-header source uuid (copyD0) = %d\n", *header->get_sourceUuid());
	header->set_sourcePortId(ptpClock->get_port_id_field());
	sync->set_grandmasterSequenceId(ptpClock->get_grandmaster_sequence_number());
	header->set_sequenceId(ptpClock->get_grandmaster_sequence_number());
}

int 
getIdentifierOrder(Octet identifier[PTP_CODE_STRING_LENGTH])
{
	if (!memcmp(identifier, IDENTIFIER_ATOM, PTP_CODE_STRING_LENGTH))
		return 1;
	else if (!memcmp(identifier, IDENTIFIER_GPS, PTP_CODE_STRING_LENGTH))
		return 1;
	else if (!memcmp(identifier, IDENTIFIER_NTP, PTP_CODE_STRING_LENGTH))
		return 2;
	else if (!memcmp(identifier, IDENTIFIER_HAND, PTP_CODE_STRING_LENGTH))
		return 3;
	else if (!memcmp(identifier, IDENTIFIER_INIT, PTP_CODE_STRING_LENGTH))
		return 4;
	else if (!memcmp(identifier, IDENTIFIER_DFLT, PTP_CODE_STRING_LENGTH))
		return 5;

	return 6;
}

/* return similar to memcmp()s
   note: communicationTechnology can be ignored because
   if they differed they would not have made it here */

Integer8 
bmcDataSetComparison(MsgHeader * headerA, MsgSync * syncA,
    MsgHeader * headerB, MsgSync * syncB, PtpClock * ptpClock)
{
	DBGV("bmcDataSetComparison: start\n");
	if (!(syncA->get_grandmasterPortId() == syncB->get_grandmasterPortId()
	    && !memcmp(syncA->get_grandmasterClockUuid(), syncB->get_grandmasterClockUuid(), PTP_UUID_LENGTH))) {
		if (syncA->get_grandmasterClockStratum() < syncB->get_grandmasterClockStratum())
			goto A;
		else if (syncA->get_grandmasterClockStratum() > syncB->get_grandmasterClockStratum())
			goto B;

		/* grandmasterClockStratums same */
		if (getIdentifierOrder(syncA->get_grandmasterClockIdentifier()) < getIdentifierOrder(syncB->get_grandmasterClockIdentifier()))
			goto A;
		if (getIdentifierOrder(syncA->get_grandmasterClockIdentifier()) > getIdentifierOrder(syncB->get_grandmasterClockIdentifier()))
			goto B;

		/* grandmasterClockIdentifiers same */
		if (syncA->get_grandmasterClockStratum() > 2) {
			if (syncA->get_grandmasterClockVariance() > syncB->get_grandmasterClockVariance() + PTP_LOG_VARIANCE_THRESHOLD
			    || syncA->get_grandmasterClockVariance() < syncB->get_grandmasterClockVariance() - PTP_LOG_VARIANCE_THRESHOLD) {
				/* grandmasterClockVariances are not similar */
				if (syncA->get_grandmasterClockVariance() < syncB->get_grandmasterClockVariance())
					goto A;
				else
					goto B;
			}
			/* grandmasterClockVariances are similar */
			if (!syncA->get_grandmasterIsBoundaryClock() != !syncB->get_grandmasterIsBoundaryClock()) {	/* XOR */
				if (syncA->get_grandmasterIsBoundaryClock())
					goto A;
				else
					goto B;
			}
			/* neither is grandmasterIsBoundaryClock */
			if (memcmp(syncA->get_grandmasterClockUuid(), syncB->get_grandmasterClockUuid(), PTP_UUID_LENGTH) < 0)
				goto A;
			else
				goto B;
		}
		/* syncA->grandmasterClockStratum <= 2 */
		if (!syncA->get_grandmasterPreferred() != !syncB->get_grandmasterPreferred()) {	/* XOR */
			if (syncA->get_grandmasterPreferred())
				return 1;	/* A1 */
			else
				return -1;	/* B1 */
		}
		/* neither or both grandmasterPreferred */
	}
	DBGV("bmcDataSetComparison: X\n");
	if (syncA->get_localStepsRemoved() > syncB->get_localStepsRemoved() + 1
	    || syncA->get_localStepsRemoved() < syncB->get_localStepsRemoved() - 1) {
		/* localStepsRemoved not within 1 */
		if (syncA->get_localStepsRemoved() < syncB->get_localStepsRemoved())
			return 1;	/* A1 */
		else
			return -1;	/* B1 */
	}
	/* localStepsRemoved within 1 */
	if (syncA->get_localStepsRemoved() < syncB->get_localStepsRemoved()) {
		DBGV("bmcDataSetComparison: A3\n");
		if (memcmp(ptpClock->get_port_uuid_field(), headerB->get_sourceUuid(), PTP_UUID_LENGTH) < 0)
			return 1;	/* A1 */
		else if (memcmp(ptpClock->get_port_uuid_field(), headerB->get_sourceUuid(), PTP_UUID_LENGTH) > 0)
			return 2;	/* A2 */

		/* this port_uuid_field same as headerB->sourceUuid */
		if (ptpClock->get_port_id_field() < headerB->get_sourcePortId())
			return 1;	/* A1 */
		else if (ptpClock->get_port_id_field() > headerB->get_sourcePortId())
			return 2;	/* A2 */

		/* this port_id_field same as headerB->sourcePortId */
		return 0;		/* same */
	}
	if (syncA->get_localStepsRemoved() > syncB->get_localStepsRemoved()) {
		DBGV("bmcDataSetComparison: B3\n");
		if (memcmp(ptpClock->get_port_uuid_field(), headerA->get_sourceUuid(), PTP_UUID_LENGTH) < 0)
			return -1;	/* B1 */
		else if (memcmp(ptpClock->get_port_uuid_field(), headerB->get_sourceUuid(), PTP_UUID_LENGTH) > 0)
			return -2;	/* B2 */

		/* this port_uuid_field same as headerA->sourceUuid */
		if (ptpClock->get_port_id_field() < headerA->get_sourcePortId())
			return -1;	/* B1 */
		else if (ptpClock->get_port_id_field() > headerA->get_sourcePortId())
			return -2;	/* B2 */

		/* this port_id_field same as headerA->sourcePortId */
		return 0;		/* same */
	}
	/* localStepsRemoved same */
	if (memcmp(headerA->get_sourceUuid(), headerB->get_sourceUuid(), PTP_UUID_LENGTH) < 0)
		return 2;		/* A2 */
	else if (memcmp(headerA->get_sourceUuid(), headerB->get_sourceUuid(), PTP_UUID_LENGTH) > 0)
		return -2;		/* B2 */

	/* sourceUuid same */
	DBGV("bmcDataSetComparison: Z\n");
	if (syncA->get_grandmasterSequenceId() > syncB->get_grandmasterSequenceId())
		return 3;
	else if (syncA->get_grandmasterSequenceId() < syncB->get_grandmasterSequenceId())
		return -3;

	/* grandmasterSequenceId same */
	if (headerA->get_sequenceId() > headerB->get_sequenceId())
		return 3;
	else if (headerA->get_sequenceId() < headerB->get_sequenceId())
		return -3;

	/* sequenceId same */
	return 0;			/* same */

	/* oh no, a goto label! the horror! */
A:
	if (!syncA->get_grandmasterPreferred() && syncB->get_grandmasterPreferred())
		return -1;		/* B1 */
	else
		return 1;		/* A1 */
B:
	if (syncA->get_grandmasterPreferred() && !syncB->get_grandmasterPreferred())
		return 1;		/* A1 */
	else
		return -1;		/* B1 */
}

UInteger8 
bmcStateDecision(MsgHeader *header, MsgSync *sync, RunTimeOpts *rtOpts, PtpClock *ptpClock)
{
	//printf("--source communication tech (bmcsd) = %d\n",ptpClock->get_msgTmpHeader().get_sourceCommunicationTechnology());
	//printf("--clock communication tech (bmcsd) = %d\n",header->get_sourceCommunicationTechnology());
	//cout << *header << endl;
	//printf("messageType = %d\n",header->get_messageType());
	//printf("source communication tech = %d\n",header->get_sourceCommunicationTechnology());
	//cout << ptpClock->get_msgTmpHeader() << endl;
	if (rtOpts->get_slaveOnly()) {
		s1(header, sync, ptpClock);
		return PTP_SLAVE;
	}
	copyD0(&ptpClock->get_msgTmpHeader(), &ptpClock->get_msgtmp_sync(), ptpClock); /*iffy,pass by reference/pointer or value*/
	//printf("--source communication tech (bmcsd) = %d\n",ptpClock->get_msgTmpHeader().get_sourceCommunicationTechnology());
	//printf("--clock communication tech (bmcsd) = %d\n",ptpClock->get_clock_communication_technology());

	if (ptpClock->get_msgtmp().get_sync().get_grandmasterClockStratum() < 3) {
		if (bmcDataSetComparison(&ptpClock->get_msgTmpHeader(), &ptpClock->get_msgtmp().get_sync(), header, sync, ptpClock) > 0) {
			m1(ptpClock);
			return PTP_MASTER;
		}
		//cout << "call s1 1" << endl;
		s1(header, sync, ptpClock);
		return PTP_PASSIVE;
	} else if (bmcDataSetComparison(&ptpClock->get_msgTmpHeader(), &ptpClock->get_msgtmp().get_sync(), header, sync, ptpClock) > 0
	    && ptpClock->get_msgtmp().get_sync().get_grandmasterClockStratum() != 255) {
		m1(ptpClock);
		return PTP_MASTER;
	} else {
		//cout << "call s1 2" << endl;
		s1(header, sync, ptpClock);
		return PTP_SLAVE;
	}
}

UInteger8 
bmc(ForeignMasterRecord * foreign, RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	Integer16 i, best;

	//printf("number foreign records = %d\n",ptpClock->get_number_foreign_records());
	ptpClock->set_numberForeignRecords(1);
	if (!ptpClock->get_number_foreign_records()) {
	//cout << "get bmc" << endl;
		if (ptpClock->get_port_state() == PTP_MASTER)
			m1(ptpClock);
		return ptpClock->get_port_state();	/* no change */
	}
	for (i = 1, best = 0; i < ptpClock->get_number_foreign_records(); ++i) {
		if (bmcDataSetComparison(&foreign[i].get_header(), &foreign[i].get_sync(),
		    &foreign[best].get_header(), &foreign[best].get_sync(), ptpClock) > 0)
			best = i;
	}

	//printf("-bmc: best record %d\n", best);
	ptpClock->set_foreign_record_best(best);

	//printf("-foreign header = %d\n",foreign[best].get_header());
	return bmcStateDecision(&foreign[best].get_header(), &foreign[best].get_sync(), rtOpts, ptpClock);
}
