/**
 * @file   msg.cc
 * @author George Neville-Neil <gnn@neville-neil.com>
 * @date   Tue Jul 20 16:17:05 2010
 * 
 * @brief  Functions to pack and unpack messages.
 * 
 * See spec annex d
 */


#include "classes/ptpd.h"
#include "classes/ptpd_dep.h"

Boolean 
msgPeek(void *buf, ssize_t length)
{
	/* not imlpemented yet */
	return true;
}

void 
msgUnpackHeader(void *buf, MsgHeader * header)
{
	header->set_versionPTP(flip16(*(UInteger16 *) (buf + 0)));
	header->set_versionNetwork(flip16(*(UInteger16 *) (buf + 2)));
	//printf("msgUnpackHeader: versionPTP %d\n", header->get_versionPTP());
	//printf("msgUnpackHeader: versionNetwork %d\n", header->get_versionNetwork());


	header->set_subdomain((buf+4),16);
	DBGV("msgUnpackHeader: subdomain %s\n", header->get_subdomain());

	header->set_messageType(*(UInteger8 *) (buf + 20));
	header->set_sourceCommunicationTechnology(*(UInteger8 *) (buf + 21));
	DBGV("msgUnpackHeader: messageType %d\n", header->get_messageType());
	DBGV("msgUnpackHeader: sourceCommunicationTechnology %d\n", header->get_sourceCommunicationTechnology90);

	header->set_sourceUuid((buf+22),6);
	//printf("header sourceUuid (msgUnpackHeader) = %d\n",*header->get_sourceUuid());
//	memcpy(header->sourceUuid, (buf + 22), 6);
/*	DBGV("msgUnpackHeader: sourceUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
	    header->sourceUuid[0], header->sourceUuid[1], header->sourceUuid[2],
	    header->sourceUuid[3], header->sourceUuid[4], header->sourceUuid[5]);
*/

	header->set_sourcePortId(flip16(*(UInteger16 *) (buf + 28)));
	header->set_sequenceId(flip16(*(UInteger16 *) (buf + 30)));
	DBGV("msgUnpackHeader: sourcePortId %d\n", header->get_sourcePortId());
	DBGV("msgUnpackHeader: sequenceId %d\n", header->get_sequenceId());

	header->set_control(*(UInteger8 *) (buf + 32));
	DBGV("msgUnpackHeader: control %d\n", header->get_control());

	header->set_flags((buf+34),2);
	memcpy(header->get_flags(), (buf + 34), 2);
//	DBGV("msgUnpackHeader: flags %02hhx %02hhx\n", header->flags[0], header->flags[1]);
}

void 
msgUnpackSync(void *buf, MsgSync * sync)
{
	sync->set_originTimestamp_seconds((flip32(*(UInteger32 *) (buf + 40))));
	DBGV("msgUnpackSync: originTimestamp.seconds %u\n", sync->originTimestamp.seconds);
	sync->set_originTimestamp_nanoseconds(flip32(*(Integer32 *) (buf + 44)));
	DBGV("msgUnpackSync: originTimestamp.nanoseconds %d\n", sync->originTimestamp.nanoseconds);
	sync->set_epochNumber(flip16(*(UInteger16 *) (buf + 48)));
	DBGV("msgUnpackSync: epochNumber %d\n", sync->epochNumber);
	sync->set_currentUTCOffset(flip16(*(Integer16 *) (buf + 50)));
	DBGV("msgUnpackSync: currentUTCOffset %d\n", sync->currentUTCOffset);
	sync->set_grandmasterCommunicationTechnology(*(UInteger8 *) (buf + 53));
	DBGV("msgUnpackSync: grandmasterCommunicationTechnology %d\n", sync->grandmasterCommunicationTechnology);
	sync->set_grandmasterClockUuid((buf + 54), 6);
/*	DBGV("msgUnpackSync: grandmasterClockUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
	    sync->grandmasterClockUuid[0], sync->grandmasterClockUuid[1], sync->grandmasterClockUuid[2],
	    sync->grandmasterClockUuid[3], sync->grandmasterClockUuid[4], sync->grandmasterClockUuid[5]);*/
	sync->set_grandmasterPortId(flip16(*(UInteger16 *) (buf + 60)));
	DBGV("msgUnpackSync: grandmasterPortId %d\n", sync->grandmasterPortId);
	sync->set_grandmasterSequenceId(flip16(*(UInteger16 *) (buf + 62)));
	DBGV("msgUnpackSync: grandmasterSequenceId %d\n", sync->grandmasterSequenceId);
	sync->set_grandmasterClockStratum(*(UInteger8 *) (buf + 67));
	DBGV("msgUnpackSync: grandmasterClockStratum %d\n", sync->grandmasterClockStratum);
	sync->set_grandmasterClockIdentifier((buf + 68), 4);
/*	DBGV("msgUnpackSync: grandmasterClockIdentifier %c%c%c%c\n",
	    sync->grandmasterClockIdentifier[0], sync->grandmasterClockIdentifier[1],
	    sync->grandmasterClockIdentifier[2], sync->grandmasterClockIdentifier[3]);*/
	sync->set_grandmasterClockVariance(flip16(*(Integer16 *) (buf + 74)));
//	DBGV("msgUnpackSync: grandmasterClockVariance %d\n", sync->grandmasterClockVariance);
	sync->set_grandmasterPreferred(*(UInteger8 *) (buf + 77));
	DBGV("msgUnpackSync: grandmasterPreferred %d\n", sync->grandmasterPreferred);
	sync->set_grandmasterIsBoundaryClock(*(UInteger8 *) (buf + 79));
//	DBGV("msgUnpackSync: grandmasterIsBoundaryClock %d\n", sync->grandmasterIsBoundaryClock);
	sync->set_syncInterval(*(Integer8 *) (buf + 83));
//	DBGV("msgUnpackSync: syncInterval %d\n", sync->syncInterval);
	sync->set_localClockVariance(flip16(*(Integer16 *) (buf + 86)));
//	DBGV("msgUnpackSync: localClockVariance %d\n", sync->localClockVariance);
	sync->set_localStepsRemoved(flip16(*(UInteger16 *) (buf + 90)));
//	DBGV("msgUnpackSync: localStepsRemoved %d\n", sync->localStepsRemoved);
	sync->set_localClockStratum(*(UInteger8 *) (buf + 95));
//	DBGV("msgUnpackSync: localClockStratum %d\n", sync->localClockStratum);
	sync->set_localClockIdentifier((buf + 96), PTP_CODE_STRING_LENGTH);
/*	DBGV("msgUnpackSync: localClockIdentifer %c%c%c%c\n",
	    sync->localClockIdentifer[0], sync->localClockIdentifer[1],
	    sync->localClockIdentifer[2], sync->localClockIdentifer[3]);
*/
	sync->set_parentCommunicationTechnology(*(UInteger8 *) (buf + 101));
//	DBGV("msgUnpackSync: parentCommunicationTechnology %d\n", sync->parentCommunicationTechnology);
	sync->set_parentUuid((buf + 102), PTP_UUID_LENGTH);
/*	DBGV("msgUnpackSync: parentUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
	    sync->parentUuid[0], sync->parentUuid[1], sync->parentUuid[2],
	    sync->parentUuid[3], sync->parentUuid[4], sync->parentUuid[5]);
*/
	sync->set_parentPortField(flip16(*(UInteger16 *) (buf + 110)));
//	DBGV("msgUnpackSync: parentPortField %d\n", sync->parentPortField);
	sync->set_estimatedMasterVariance(flip16(*(Integer16 *) (buf + 114)));
//	DBGV("msgUnpackSync: estimatedMasterVariance %d\n", sync->estimatedMasterVariance);
	sync->set_estimatedMasterDrift(flip32(*(Integer32 *) (buf + 116)));
//	DBGV("msgUnpackSync: estimatedMasterDrift %d\n", sync->estimatedMasterDrift);
	sync->set_utcReasonable(*(UInteger8 *) (buf + 123));
//	DBGV("msgUnpackSync: utcReasonable %d\n", sync->utcReasonable);
}

void 
msgUnpackDelayReq(void *buf, MsgDelayReq * req)
{
}

void 
msgUnpackFollowUp(void *buf, MsgFollowUp * follow)
{
	follow->set_associatedSequenceId(flip16(*(UInteger16 *) (buf + 42)));
//	DBGV("msgUnpackFollowUp: associatedSequenceId %u\n", follow->associatedSequenceId);
	follow->set_preciseOriginTimestamp_seconds(flip32(*(UInteger32 *) (buf + 44)));
//	DBGV("msgUnpackFollowUp: preciseOriginTimestamp.seconds %u\n", follow->preciseOriginTimestamp.seconds);
	follow->set_preciseOriginTimestamp_nanoseconds(flip32(*(Integer32 *) (buf + 48)));
//	DBGV("msgUnpackFollowUp: preciseOriginTimestamp.nanoseconds %d\n", follow->preciseOriginTimestamp.nanoseconds);
}

void 
msgUnpackDelayResp(void *buf, MsgDelayResp * resp)
{
	resp->set_delayReceiptTimestamp_seconds(flip32(*(UInteger32 *) (buf + 40)));
//	printf("msgUnpackDelayResp: delayReceiptTimestamp.seconds %u\n", resp->get_delayReceiptTimestamp().get_seconds());
	resp->set_delayReceiptTimestamp_nanoseconds(flip32(*(Integer32 *) (buf + 44)));
//	printf("msgUnpackDelayResp: delayReceiptTimestamp.nanoseconds %d\n", resp->get_delayReceiptTimestamp().get_nanoseconds());
	resp->set_requestingSourceCommunicationTechnology(*(UInteger8 *) (buf + 49));
//	printf("msgUnpackDelayResp: requestingSourceCommunicationTechnology %d\n", resp->get_requestingSourceCommunicationTechnology());
	resp->set_requestingSourceUuid((buf + 50), 6);
	DBGV("msgUnpackDelayResp: requestingSourceUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
	    resp->get_requestingSourceUuid(0), resp->get_requestingSourceUuid(1), resp->get_requestingSourceUuid(2),
	    resp->get_requestingSourceUuid(3), resp->get_requestingSourceUuid(4), resp->get_requestingSourceUuid(5));

	resp->set_requestingSourcePortId(flip16(*(UInteger16 *) (buf + 56)));
//	printf("msgUnpackDelayResp: requestingSourcePortId %d\n", resp->get_requestingSourcePortId());
	resp->set_requestingSourceSequenceId(flip16(*(UInteger16 *) (buf + 58)));
//	printf("msgUnpackDelayResp: requestingSourceSequenceId %d\n", resp->get_requestingSourceSequenceId());
}

void 
msgUnpackManagement(void *buf, MsgManagement * manage)
{
	manage->set_targetCommunicationTechnology(*(UInteger8 *) (buf + 41));
//	DBGV("msgUnpackManagement: targetCommunicationTechnology %d\n", manage->targetCommunicationTechnology);
	manage->set_targetUuid((buf + 42), 6);
/*	DBGV("msgUnpackManagement: targetUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
	    manage->targetUuid[0], manage->targetUuid[1], manage->targetUuid[2],
	    manage->targetUuid[3], manage->targetUuid[4], manage->targetUuid[5]);
*/
	manage->set_targetPortId(flip16(*(UInteger16 *) (buf + 48)));
//	DBGV("msgUnpackManagement: targetPortId %d\n", manage->targetPortId);
	manage->set_startingBoundaryHops(flip16(*(Integer16 *) (buf + 50)));
//	DBGV("msgUnpackManagement: startingBoundaryHops %d\n", manage->startingBoundaryHops);
	manage->set_boundaryHops(flip16(*(Integer16 *) (buf + 52)));
//	DBGV("msgUnpackManagement: boundaryHops %d\n", manage->boundaryHops);
	manage->set_managementMessageKey(*(UInteger8 *) (buf + 55));
//	DBGV("msgUnpackManagement: managementMessageKey %d\n", manage->managementMessageKey);
	manage->set_parameterLength(flip16(*(UInteger16 *) (buf + 58)));
//	DBGV("msgUnpackManagement: parameterLength %d\n", manage->parameterLength);

	if (manage->get_managementMessageKey() == PTP_MM_GET_FOREIGN_DATA_SET)
		manage->set_recordKey(flip16(*(UInteger16 *) (buf + 62)));
}

UInteger8 
msgUnloadManagement(void *buf, MsgManagement * manage,
    PtpClock * ptpClock, RunTimeOpts * rtOpts)
{
	TimeInternal internalTime;
	TimeRepresentation externalTime;

	switch (manage->get_managementMessageKey()) {
	case PTP_MM_INITIALIZE_CLOCK:
		if (ptpClock->get_initializable())
			return PTP_INITIALIZING;
		break;

	case PTP_MM_GOTO_FAULTY_STATE:
		DBG("event FAULT_DETECTED (forced by management message)\n");
		return PTP_FAULTY;
		break;

	case PTP_MM_DISABLE_PORT:
		if (manage->get_targetPortId() == 1) {
			DBG("event DESIGNATED_DISABLED\n");
			return PTP_DISABLED;
		}
		break;

	case PTP_MM_ENABLE_PORT:
		if (manage->get_targetPortId() == 1) {
			DBG("event DESIGNATED_ENABLED\n");
			return PTP_INITIALIZING;
		}
		break;

	case PTP_MM_CLEAR_DESIGNATED_PREFERRED_MASTER:
		ptpClock->set_preferred(false);
		break;

	case PTP_MM_SET_DESIGNATED_PREFERRED_MASTER:
		ptpClock->set_preferred(true);
		break;

	case PTP_MM_DISABLE_BURST:
		break;

	case PTP_MM_ENABLE_BURST:
		break;

	case PTP_MM_SET_SYNC_INTERVAL:
		rtOpts->set_syncInterval(*(Integer8 *) (buf + 63));
		break;

	case PTP_MM_SET_SUBDOMAIN:
		rtOpts->set_subdomainName((buf + 60), 16);
		DBG("set subdomain to %s\n", rtOpts->get_subdomainName());
		break;

	case PTP_MM_SET_TIME:
		externalTime.set_seconds(flip32(*(UInteger32 *) (buf + 60)));
		externalTime.set_nanoseconds(flip32(*(Integer32 *) (buf + 64)));
		toInternalTime(&internalTime,&externalTime,&ptpClock->get_halfEpoch());
		setTime(&internalTime);
		break;

	case PTP_MM_UPDATE_DEFAULT_DATA_SET:
		if (!rtOpts->get_slaveOnly())
			ptpClock->set_clockStratum(*(UInteger8 *) (buf + 63));
		ptpClock->set_clockIdentifier((buf + 64), 4);
		ptpClock->set_clockVariance(flip16(*(Integer16 *) (buf + 70)));
		ptpClock->set_preferred(*(UInteger8 *) (buf + 75));
		rtOpts->set_syncInterval(*(UInteger8 *) (buf + 79));
		rtOpts->set_subdomainName((buf + 80), 16);
		break;

	case PTP_MM_UPDATE_GLOBAL_TIME_PROPERTIES:
		ptpClock->set_currentUtcOffset(flip16(*(Integer16 *) (buf + 62)));
		ptpClock->set_leap59(*(UInteger8 *) (buf + 67));
		ptpClock->set_leap61(*(UInteger8 *) (buf + 71));
		ptpClock->set_epochNumber(flip16(*(UInteger16 *) (buf + 74)));
		break;

	default:
		break;
	}

	return ptpClock->get_port_state();
}

void 
msgUnpackManagementPayload(void *buf, MsgManagement * manage)
{
	switch (manage->get_managementMessageKey()) {
		case PTP_MM_CLOCK_IDENTITY:
		DBGV("msgUnloadManagementPayload: managementMessageKey PTP_MM_CLOCK_IDENTITY\n");
		manage->get_payload().set_clockIdentity_clockComTech(*(UInteger8 *) (buf + 63));
		manage->get_payload().get_clockIdentity().set_clockUuidField(buf + 64, PTP_UUID_LENGTH);
		manage->get_payload().get_clockIdentity().set_clockPortField(flip16(*(UInteger16 *) (buf + 74)));
		manage->get_payload().get_clockIdentity().set_manufacturerIdentity(buf + 76, MANUFACTURER_ID_LENGTH);
		break;

	case PTP_MM_DEFAULT_DATA_SET:
		DBGV("msgUnloadManagementPayload: managementMessageKey PTP_MM_DEFAULT_DATA_SET\n");
		manage->get_payload().get_defaultData().set_clockCommunicationTechnology(*(UInteger8 *) (buf + 63));
		manage->get_payload().get_defaultData().set_clockUuidField(buf + 64, PTP_UUID_LENGTH);
		manage->get_payload().get_defaultData().set_clockPortField(flip16(*(UInteger16 *) (buf + 74)));
		manage->get_payload().get_defaultData().set_clockStratum(*(UInteger16 *) (buf + 79));
		manage->get_payload().get_defaultData().set_clockIdentifier(buf + 80, PTP_CODE_STRING_LENGTH);
		manage->get_payload().get_defaultData().set_clockVariance(flip16(*(UInteger16 *) (buf + 86)));
		manage->get_payload().get_defaultData().set_clockFollowupCapable(*(UInteger8 *) (buf + 91));
		manage->get_payload().get_defaultData().set_preferred(*(UInteger8 *) (buf + 95));
		manage->get_payload().get_defaultData().set_initializable(*(UInteger8 *) (buf + 99));
		manage->get_payload().get_defaultData().set_externalTiming(*(UInteger8 *) (buf + 103));
		manage->get_payload().get_defaultData().set_isBoundaryClock(*(UInteger8 *) (buf + 107));
		manage->get_payload().get_defaultData().set_syncInterval(*(UInteger8 *) (buf + 111));
		manage->get_payload().get_defaultData().set_subdomainName(buf + 112, PTP_SUBDOMAIN_NAME_LENGTH);
		manage->get_payload().get_defaultData().set_numberPorts(flip16(*(UInteger16 *) (buf + 130)));
		manage->get_payload().get_defaultData().set_numberForeignRecords(flip16(*(UInteger16 *) (buf + 134)));
		break;

	case PTP_MM_CURRENT_DATA_SET:
		DBGV("msgUnloadManagementPayload: managementMessageKey PTP_MM_CURRENT_DATA_SET\n");
		manage->get_payload().get_current().set_stepsRemoved(flip16(*(UInteger16 *) (buf + 62)));
		manage->get_payload().get_current().get_offsetFromMaster().set_seconds(flip32(*(UInteger32 *) (buf + 64)));
		manage->get_payload().get_current().get_offsetFromMaster().set_nanoseconds(flip32(*(UInteger32 *) (buf + 68)));
		manage->get_payload().get_current().get_oneWayDelay().set_seconds(flip32(*(UInteger32 *) (buf + 72)));
		manage->get_payload().get_current().get_oneWayDelay().set_nanoseconds(flip32(*(Integer32 *) (buf + 76)));
		break;

	case PTP_MM_PARENT_DATA_SET:
		DBGV("msgUnloadManagementPayload: managementMessageKey PTP_MM_PORT_DATA_SET\n");
		manage->get_payload().get_parent().set_parentCommunicationTechnology(*(UInteger8 *) (buf + 63));
		manage->get_payload().get_parent().set_parentUuid(buf + 64, PTP_UUID_LENGTH);
		manage->get_payload().get_parent().set_parentPortId(flip16(*(UInteger16 *) (buf + 74)));
		manage->get_payload().get_parent().set_parentLastSyncSequenceNumber(flip16(*(UInteger16 *) (buf + 74)));
		manage->get_payload().get_parent().set_parentFollowupCapable(*(UInteger8 *) (buf + 83));

		manage->get_payload().get_parent().set_parentExternalTiming(*(UInteger8 *) (buf + 87));
		manage->get_payload().get_parent().set_parentVariance(flip16(*(UInteger16 *) (buf + 90)));
		manage->get_payload().get_parent().set_parentStats(*(UInteger8 *) (buf + 85));
		manage->get_payload().get_parent().set_observedVariance(flip16(*(Integer16 *) (buf + 98)));
		manage->get_payload().get_parent().set_observedDrift(flip32(*(Integer32 *) (buf + 100)));
		manage->get_payload().get_parent().set_utcReasonable(*(UInteger8 *) (buf + 107));
		manage->get_payload().get_parent().set_grandmasterCommunicationTechnology(*(UInteger8 *) (buf + 111));
		manage->get_payload().get_parent().set_grandmasterUuidField(buf + 112, PTP_UUID_LENGTH);
		manage->get_payload().get_parent().set_grandmasterPortIdField(flip16(*(UInteger16 *) (buf + 122)));
		manage->get_payload().get_parent().set_grandmasterStratum(*(UInteger8 *) (buf + 127));
		manage->get_payload().get_parent().set_grandmasterIdentifier(buf + 128, PTP_CODE_STRING_LENGTH);
		manage->get_payload().get_parent().set_grandmasterVariance(flip16(*(Integer16 *) (buf + 134)));
		manage->get_payload().get_parent().set_grandmasterPreferred(*(UInteger8 *) (buf + 139));
		manage->get_payload().get_parent().set_grandmasterIsBoundaryClock(*(UInteger8 *) (buf + 144));
		manage->get_payload().get_parent().set_grandmasterSequenceNumber(flip16(*(UInteger16 *) (buf + 146)));
		break;

	case PTP_MM_PORT_DATA_SET:
		DBGV("msgUnloadManagementPayload: managementMessageKey PTP_MM_FOREIGN_DATA_SET\n");
		manage->get_payload().get_port().set_returnedPortNumber(flip16(*(UInteger16 *) (buf + 62)));
		manage->get_payload().get_port().set_portState(*(UInteger8 *) (buf + 67));
		manage->get_payload().get_port().set_lastSyncEventSequenceNumber(flip16(*(UInteger16 *) (buf + 70)));
		manage->get_payload().get_port().set_lastGeneralEventSequenceNumber(flip16(*(UInteger16 *) (buf + 74)));
		manage->get_payload().get_port().set_portCommunicationTechnology(*(UInteger8 *) (buf + 79));
		manage->get_payload().get_port().set_portUuidField(buf + 80, PTP_UUID_LENGTH);
		manage->get_payload().get_port().set_portIdField(flip16(*(UInteger16 *) (buf + 90)));
		manage->get_payload().get_port().set_burstEnabled(*(UInteger8 *) (buf + 95));
		manage->get_payload().get_port().set_subdomainAddressOctets(*(UInteger8 *) (buf + 97));
		manage->get_payload().get_port().set_eventPortAddressOctets(*(UInteger8 *) (buf + 98));
		manage->get_payload().get_port().set_generalPortAddressOctets(*(UInteger8 *) (buf + 99));
		manage->get_payload().get_port().set_subdomainAddress(buf + 100, SUBDOMAIN_ADDRESS_LENGTH);
		manage->get_payload().get_port().set_eventPortAddress(buf + 106, PORT_ADDRESS_LENGTH);
		manage->get_payload().get_port().set_generalPortAddress(buf + 110, PORT_ADDRESS_LENGTH);
		break;

	case PTP_MM_GLOBAL_TIME_DATA_SET:
		DBGV("msgUnloadManagementPayload: managementMessageKey PTP_MM_GLOBAL_TIME_DATA_SET\n");
		manage->get_payload().get_globalTime().get_localTime().set_seconds(flip32(*(UInteger32 *) (buf + 60)));
		manage->get_payload().get_globalTime().get_localTime().set_nanoseconds(flip32(*(Integer32 *) (buf + 64)));
		manage->get_payload().get_globalTime().set_currentUtcOffset(flip16(*(Integer16 *) (buf + 70)));
		manage->get_payload().get_globalTime().set_leap59(*(UInteger8 *) (buf + 75));
		manage->get_payload().get_globalTime().set_leap61(*(UInteger8 *) (buf + 79));
		manage->get_payload().get_globalTime().set_epochNumber(flip16(*(UInteger16 *) (buf + 82)));
		break;


	case PTP_MM_FOREIGN_DATA_SET:
		DBGV("msgUnloadManagementPayload: managementMessageKey PTP_MM_FOREIGN_DATA_SET\n");
		manage->get_payload().get_foreign().set_returnedPortNumber(flip16(*(UInteger16 *) (buf + 62)));
		manage->get_payload().get_foreign().set_returnedRecordNumber(flip16(*(UInteger16 *) (buf + 68)));
		manage->get_payload().get_foreign().set_foreignMasterCommunicationTechnology(*(UInteger8 *) (buf + 71));
		manage->get_payload().get_foreign().set_foreignMasterUuid(buf + 72, PTP_UUID_LENGTH);
		manage->get_payload().get_foreign().set_foreignMasterPortId(flip16(*(UInteger16 *) (buf + 82)));
		manage->get_payload().get_foreign().set_foreignMasterSyncs(flip16(*(UInteger16 *) (buf + 66)));
		break;

	case PTP_MM_NULL:
		DBGV("msgUnloadManagementPayload: managementMessageKey NULL\n");
		break;

	default:
		DBGV("msgUnloadManagementPayload: managementMessageKey ?\n");
		break;
	}

	return;
}

void 
msgPackHeader(void *buf, PtpClock * ptpClock)
{
	*(Integer32 *) (buf + 0) = shift16(flip16(VERSION_PTP), 0) | shift16(flip16(VERSION_NETWORK), 1);
	memcpy((buf + 4), ptpClock->get_subdomain_name(), 16);
	*(Integer32 *) (buf + 20) = shift8(ptpClock->get_port_communication_technology(), 1);
	memcpy((buf + 22), ptpClock->get_port_uuid_field(), 6);

	if (ptpClock->get_external_timing())
		setFlag((buf + 34), PTP_EXT_SYNC);
	if (ptpClock->get_clock_followup_capable())
		setFlag((buf + 34), PTP_ASSIST);
	if (ptpClock->get_is_boundary_clock())
		setFlag((buf + 34), PTP_BOUNDARY_CLOCK);
}

void 
msgPackSync(void *buf, Boolean burst,
    TimeRepresentation * originTimestamp, PtpClock * ptpClock)
{
	*(UInteger8 *) (buf + 20) = 1;	/* messageType */
	*(Integer32 *) (buf + 28) = shift16(flip16(ptpClock->get_port_id_field()), 0) | shift16(flip16(ptpClock->get_last_sync_event_sequence_number()), 1);
	*(UInteger8 *) (buf + 32) = PTP_SYNC_MESSAGE;	/* control */
	if (ptpClock->get_burst_enabled() && burst)
		setFlag((buf + 34), PTP_SYNC_BURST);
	else
		clearFlag((buf + 34), PTP_SYNC_BURST);
	if (ptpClock->get_parent_stats())
		setFlag((buf + 34), PARENT_STATS);
	else
		clearFlag((buf + 34), PARENT_STATS);


	*(Integer32 *) (buf + 40) = flip32(originTimestamp->get_seconds());
	*(Integer32 *) (buf + 44) = flip32(originTimestamp->get_nanoseconds());
	*(Integer32 *) (buf + 48) = shift16(flip16(ptpClock->get_epoch_number()), 0) | shift16(flip16(ptpClock->get_current_utc_offset()), 1);
	*(Integer32 *) (buf + 52) = shift8(ptpClock->get_grandmaster_communication_technology(), 1);
	memcpy((buf + 54), ptpClock->get_grandmaster_uuid_field(), 6);
	*(Integer32 *) (buf + 60) = shift16(flip16(ptpClock->get_grandmaster_port_id_field()), 0) | shift16(flip16(ptpClock->get_grandmaster_sequence_number()), 1);
	*(Integer32 *) (buf + 64) = shift8(ptpClock->get_grandmaster_stratum(), 3);
	memcpy((buf + 68), ptpClock->get_grandmaster_identifier(), 4);
	*(Integer32 *) (buf + 72) = shift16(flip16(ptpClock->get_grandmaster_variance()), 1);
	*(Integer32 *) (buf + 76) = shift16(flip16(ptpClock->get_grandmaster_preferred()), 0) | shift16(flip16(ptpClock->get_grandmaster_is_boundary_clock()), 1);
	*(Integer32 *) (buf + 80) = shift16(flip16(ptpClock->get_sync_interval()), 1);
	*(Integer32 *) (buf + 84) = shift16(flip16(ptpClock->get_clock_variance()), 1);
	*(Integer32 *) (buf + 88) = shift16(flip16(ptpClock->get_steps_removed()), 1);
	*(Integer32 *) (buf + 92) = shift8(ptpClock->get_clock_stratum(), 3);
	memcpy((buf + 96), ptpClock->get_clock_identifier(), 4);
	*(Integer32 *) (buf + 100) = shift8(ptpClock->get_parent_communication_technology(), 1);
	memcpy((buf + 102), ptpClock->get_parent_uuid(), 6);
	*(Integer32 *) (buf + 108) = shift16(flip16(ptpClock->get_parent_port_id()), 1);
	*(Integer32 *) (buf + 112) = shift16(flip16(ptpClock->get_observed_variance()), 1);
	*(Integer32 *) (buf + 116) = flip32(ptpClock->get_observed_drift());
	*(Integer32 *) (buf + 120) = shift8(ptpClock->get_utc_reasonable(), 3);
}

void 
msgPackDelayReq(void *buf, Boolean burst,
    TimeRepresentation * originTimestamp, PtpClock * ptpClock)
{
	*(UInteger8 *) (buf + 20) = 1;	/* messageType */
	*(Integer32 *) (buf + 28) = shift16(flip16(ptpClock->get_port_id_field()), 0) | shift16(flip16(ptpClock->get_last_sync_event_sequence_number()), 1);
	*(UInteger8 *) (buf + 32) = PTP_DELAY_REQ_MESSAGE;	/* control */
	if (ptpClock->get_burst_enabled() && burst)
		setFlag((buf + 34), PTP_SYNC_BURST);
	else
		clearFlag((buf + 34), PTP_SYNC_BURST);
	if (ptpClock->get_parent_stats())
		setFlag((buf + 34), PARENT_STATS);
	else
		clearFlag((buf + 34), PARENT_STATS);

	*(Integer32 *) (buf + 40) = flip32(originTimestamp->get_seconds());
	*(Integer32 *) (buf + 44) = flip32(originTimestamp->get_nanoseconds());
	*(Integer32 *) (buf + 48) = shift16(flip16(ptpClock->get_epoch_number()), 0) | shift16(flip16(ptpClock->get_current_utc_offset()), 1);
	*(Integer32 *) (buf + 52) = shift8(ptpClock->get_grandmaster_communication_technology(), 1);
	memcpy((buf + 54), ptpClock->get_grandmaster_uuid_field(), 6);
	*(Integer32 *) (buf + 60) = shift16(flip16(ptpClock->get_grandmaster_port_id_field()), 0) | shift16(flip16(ptpClock->get_grandmaster_sequence_number()), 1);
	*(Integer32 *) (buf + 64) = shift8(ptpClock->get_grandmaster_stratum(), 3);
	memcpy((buf + 68), ptpClock->get_grandmaster_identifier(), 4);
	*(Integer32 *) (buf + 72) = shift16(flip16(ptpClock->get_grandmaster_variance()), 1);
	*(Integer32 *) (buf + 76) = shift16(flip16(ptpClock->get_grandmaster_preferred()), 0) | shift16(flip16(ptpClock->get_grandmaster_is_boundary_clock()), 1);
	*(Integer32 *) (buf + 80) = shift16(flip16(ptpClock->get_sync_interval()), 1);
	*(Integer32 *) (buf + 84) = shift16(flip16(ptpClock->get_clock_variance()), 1);
	*(Integer32 *) (buf + 88) = shift16(flip16(ptpClock->get_steps_removed()), 1);
	*(Integer32 *) (buf + 92) = shift8(ptpClock->get_clock_stratum(), 3);
	memcpy((buf + 96), ptpClock->get_clock_identifier(), 4);
	*(Integer32 *) (buf + 100) = shift8(ptpClock->get_parent_communication_technology(), 1);
	memcpy((buf + 102), ptpClock->get_parent_uuid(), 6);
	*(Integer32 *) (buf + 108) = shift16(flip16(ptpClock->get_parent_port_id()), 1);
	*(Integer32 *) (buf + 112) = shift16(flip16(ptpClock->get_observed_variance()), 1);
	*(Integer32 *) (buf + 116) = flip32(ptpClock->get_observed_drift());
	*(Integer32 *) (buf + 120) = shift8(ptpClock->get_utc_reasonable(), 3);
}

void 
msgPackFollowUp(void *buf, UInteger16 associatedSequenceId,
    TimeRepresentation * preciseOriginTimestamp, PtpClock * ptpClock)
{
	*(UInteger8 *) (buf + 20) = 2;	/* messageType */
	*(Integer32 *) (buf + 28) = shift16(flip16(ptpClock->get_port_id_field()), 0) | shift16(flip16(ptpClock->get_last_general_event_sequence_number()), 1);
	*(UInteger8 *) (buf + 32) = PTP_FOLLOWUP_MESSAGE;	/* control */
	clearFlag((buf + 34), PTP_SYNC_BURST);
	clearFlag((buf + 34), PARENT_STATS);

	*(Integer32 *) (buf + 40) = shift16(flip16(associatedSequenceId), 1);
	*(Integer32 *) (buf + 44) = flip32(preciseOriginTimestamp->get_seconds());
	*(Integer32 *) (buf + 48) = flip32(preciseOriginTimestamp->get_nanoseconds());
}

void 
msgPackDelayResp(void *buf, MsgHeader * header,
    TimeRepresentation * delayReceiptTimestamp, PtpClock * ptpClock)
{
	*(UInteger8 *) (buf + 20) = 2;	/* messageType */
	*(Integer32 *) (buf + 28) = shift16(flip16(ptpClock->get_port_id_field()), 0) | shift16(flip16(ptpClock->get_last_general_event_sequence_number()), 1);
	*(UInteger8 *) (buf + 32) = PTP_DELAY_RESP_MESSAGE;	/* control */
	clearFlag((buf + 34), PTP_SYNC_BURST);
	clearFlag((buf + 34), PARENT_STATS);

	*(Integer32 *) (buf + 40) = flip32(delayReceiptTimestamp->get_seconds());
	*(Integer32 *) (buf + 44) = flip32(delayReceiptTimestamp->get_nanoseconds());
	*(Integer32 *) (buf + 48) = shift8(header->get_sourceCommunicationTechnology(), 1);
	memcpy(buf + 50, header->get_sourceUuid(), 6);
	*(Integer32 *) (buf + 56) = shift16(flip16(header->get_sourcePortId()), 0) | shift16(flip16(header->get_sequenceId()), 1);
}

	/***********************START HERE********************/
UInteger16 
msgPackManagement(void *buf, MsgManagement * manage, PtpClock * ptpClock)
{
	*(UInteger8 *) (buf + 20) = 2;	/* messageType */
	*(Integer32 *) (buf + 28) = shift16(flip16(ptpClock->get_port_id_field()), 0) | shift16(flip16(ptpClock->get_last_general_event_sequence_number()), 1);
	*(UInteger8 *) (buf + 32) = PTP_MANAGEMENT_MESSAGE;	/* control */
	clearFlag((buf + 34), PTP_SYNC_BURST);
	clearFlag((buf + 34), PARENT_STATS);
	*(Integer32 *) (buf + 40) = shift8(manage->get_targetCommunicationTechnology(), 1);
	memcpy(buf + 42, manage->get_targetUuid(), 6);
	*(Integer32 *) (buf + 48) = shift16(flip16(manage->get_targetPortId()), 0) | shift16(flip16(MM_STARTING_BOUNDARY_HOPS), 1);
	*(Integer32 *) (buf + 52) = shift16(flip16(MM_STARTING_BOUNDARY_HOPS), 0);

	*(UInteger8 *) (buf + 55) = manage->get_managementMessageKey();

	switch (manage->get_managementMessageKey()) {
	case PTP_MM_GET_FOREIGN_DATA_SET:
		*(UInteger16 *) (buf + 62) = manage->get_recordKey();
		*(Integer32 *) (buf + 56) = shift16(flip16(4), 1);
		return 64;

	default:
		*(Integer32 *) (buf + 56) = shift16(flip16(0), 1);
		return 60;
	}
}

UInteger16 
msgPackManagementResponse(void *buf, MsgHeader * header, MsgManagement * manage, PtpClock * ptpClock)
{
	TimeInternal internalTime;
	TimeRepresentation externalTime;

	*(UInteger8 *) (buf + 20) = 2;	/* messageType */
	*(Integer32 *) (buf + 28) = shift16(flip16(ptpClock->get_port_id_field()), 0) | shift16(flip16(ptpClock->get_last_general_event_sequence_number()), 1);
	*(UInteger8 *) (buf + 32) = PTP_MANAGEMENT_MESSAGE;	/* control */
	clearFlag((buf + 34), PTP_SYNC_BURST);
	clearFlag((buf + 34), PARENT_STATS);
	*(Integer32 *) (buf + 40) = shift8(header->get_sourceCommunicationTechnology(), 1);
	memcpy(buf + 42, header->get_sourceUuid(), 6);
	*(Integer32 *) (buf + 48) = shift16(flip16(header->get_sourcePortId()), 0) | shift16(flip16(MM_STARTING_BOUNDARY_HOPS), 1);
	*(Integer32 *) (buf + 52) = shift16(flip16(manage->get_startingBoundaryHops() - manage->get_boundaryHops() + 1), 0);

	switch (manage->get_managementMessageKey()) {
	case PTP_MM_OBTAIN_IDENTITY:
		*(UInteger8 *) (buf + 55) = PTP_MM_CLOCK_IDENTITY;
		*(Integer32 *) (buf + 56) = shift16(flip16(64), 1);
		*(Integer32 *) (buf + 60) = shift8(ptpClock->get_clock_communication_technology(), 3);
		memcpy(buf + 64, ptpClock->get_clock_uuid_field(), 6);
		*(Integer32 *) (buf + 72) = shift16(flip16(ptpClock->get_clock_port_id_field()), 1);
		memcpy((buf + 76), MANUFACTURER_ID, 48);
		return 124;

	case PTP_MM_GET_DEFAULT_DATA_SET:
		*(UInteger8 *) (buf + 55) = PTP_MM_DEFAULT_DATA_SET;
		*(Integer32 *) (buf + 56) = shift16(flip16(76), 1);
		*(Integer32 *) (buf + 60) = shift8(ptpClock->get_clock_communication_technology(), 3);
		memcpy(buf + 64, ptpClock->get_clock_uuid_field(), 6);
		*(Integer32 *) (buf + 72) = shift16(flip16(ptpClock->get_clock_port_id_field()), 1);
		*(Integer32 *) (buf + 76) = shift8(ptpClock->get_clock_stratum(), 3);
		memcpy(buf + 80, ptpClock->get_clock_identifier(), 4);
		*(Integer32 *) (buf + 84) = shift16(flip16(ptpClock->get_clock_variance()), 1);
		*(Integer32 *) (buf + 88) = shift8(ptpClock->get_clock_followup_capable(), 3);
		*(Integer32 *) (buf + 92) = shift8(ptpClock->get_preferred(), 3);
		*(Integer32 *) (buf + 96) = shift8(ptpClock->get_initializable(), 3);
		*(Integer32 *) (buf + 100) = shift8(ptpClock->get_external_timing(), 3);
		*(Integer32 *) (buf + 104) = shift8(ptpClock->get_is_boundary_clock(), 3);
		*(Integer32 *) (buf + 108) = shift8(ptpClock->get_sync_interval(), 3);
		memcpy(buf + 112, ptpClock->get_subdomain_name(), 16);
		*(Integer32 *) (buf + 128) = shift16(flip16(ptpClock->get_number_ports()), 1);
		*(Integer32 *) (buf + 132) = shift16(flip16(ptpClock->get_number_foreign_records()), 1);
		return 136;

	case PTP_MM_GET_CURRENT_DATA_SET:
		*(UInteger8 *) (buf + 55) = PTP_MM_CURRENT_DATA_SET;
		*(Integer32 *) (buf + 56) = shift16(flip16(20), 1);
		*(Integer32 *) (buf + 60) = shift16(flip16(ptpClock->get_steps_removed()), 1);

		fromInternalTime(&ptpClock->get_offset_from_master(), &externalTime, 0);
		*(Integer32 *) (buf + 64) = flip32(externalTime.get_seconds());
		*(Integer32 *) (buf + 68) = flip32(externalTime.get_nanoseconds());

		fromInternalTime(&ptpClock->get_one_way_delay(), &externalTime, 0);
		*(Integer32 *) (buf + 72) = flip32(externalTime.get_seconds());
		*(Integer32 *) (buf + 76) = flip32(externalTime.get_nanoseconds());
		return 80;

	case PTP_MM_GET_PARENT_DATA_SET:
		*(UInteger8 *) (buf + 55) = PTP_MM_PARENT_DATA_SET;
		*(Integer32 *) (buf + 56) = shift16(flip16(90), 1);
		*(Integer32 *) (buf + 60) = shift8(ptpClock->get_parent_communication_technology(), 3);
		memcpy(buf + 64, ptpClock->get_parent_uuid(), 6);
		*(Integer32 *) (buf + 72) = shift16(flip16(ptpClock->get_parent_port_id()), 1);
		*(Integer32 *) (buf + 76) = shift16(flip16(ptpClock->get_parent_last_sync_sequence_number()), 1);
		*(Integer32 *) (buf + 80) = shift8(ptpClock->get_parent_followup_capable(), 1);
		*(Integer32 *) (buf + 84) = shift8(ptpClock->get_parent_external_timing(), 3);
		*(Integer32 *) (buf + 88) = shift16(flip16(ptpClock->get_parent_variance()), 1);
		*(Integer32 *) (buf + 92) = shift8(ptpClock->get_parent_stats(), 3);
		*(Integer32 *) (buf + 96) = shift16(flip16(ptpClock->get_observed_variance()), 1);
		*(Integer32 *) (buf + 100) = flip32(ptpClock->get_observed_drift());
		*(Integer32 *) (buf + 104) = shift8(ptpClock->get_utc_reasonable(), 3);
		*(Integer32 *) (buf + 108) = shift8(ptpClock->get_grandmaster_communication_technology(), 3);
		memcpy(buf + 112, ptpClock->get_grandmaster_uuid_field(), 6);
		*(Integer32 *) (buf + 120) = shift16(flip16(ptpClock->get_grandmaster_port_id_field()), 1);
		*(Integer32 *) (buf + 124) = shift8(ptpClock->get_grandmaster_stratum(), 3);
		memcpy(buf + 128, ptpClock->get_grandmaster_identifier(), 4);
		*(Integer32 *) (buf + 132) = shift16(flip16(ptpClock->get_grandmaster_variance()), 1);
		*(Integer32 *) (buf + 136) = shift8(ptpClock->get_grandmaster_preferred(), 3);
		*(Integer32 *) (buf + 140) = shift8(ptpClock->get_grandmaster_is_boundary_clock(), 3);
		*(Integer32 *) (buf + 144) = shift16(flip16(ptpClock->get_grandmaster_sequence_number()), 1);
		return 148;

	case PTP_MM_GET_PORT_DATA_SET:
		if (manage->get_targetPortId() && manage->get_targetPortId() != ptpClock->get_port_id_field()) {
			*(UInteger8 *) (buf + 55) = PTP_MM_NULL;
			*(Integer32 *) (buf + 56) = shift16(flip16(0), 1);
			return 0;
		}
		*(UInteger8 *) (buf + 55) = PTP_MM_PORT_DATA_SET;
		*(Integer32 *) (buf + 56) = shift16(flip16(52), 1);
		*(Integer32 *) (buf + 60) = shift16(flip16(ptpClock->get_port_id_field()), 1);
		*(Integer32 *) (buf + 64) = shift8(ptpClock->get_port_state(), 3);
		*(Integer32 *) (buf + 68) = shift16(flip16(ptpClock->get_last_sync_event_sequence_number()), 1);
		*(Integer32 *) (buf + 72) = shift16(flip16(ptpClock->get_last_general_event_sequence_number()), 1);
		*(Integer32 *) (buf + 76) = shift8(ptpClock->get_port_communication_technology(), 3);
		memcpy(buf + 80, ptpClock->get_port_uuid_field(), 6);
		*(Integer32 *) (buf + 88) = shift16(flip16(ptpClock->get_port_id_field()), 1);
		*(Integer32 *) (buf + 92) = shift8(ptpClock->get_burst_enabled(), 3);
		*(Integer32 *) (buf + 96) = shift8(4, 1) | shift8(2, 2) | shift8(2, 3);
		memcpy(buf + 100, ptpClock->get_subdomain_address(), 4);
		memcpy(buf + 106, ptpClock->get_event_port_address(), 2);
		memcpy(buf + 110, ptpClock->get_general_port_address(), 2);
		return 112;

	case PTP_MM_GET_GLOBAL_TIME_DATA_SET:
		*(UInteger8 *) (buf + 55) = PTP_MM_GLOBAL_TIME_DATA_SET;
		*(Integer32 *) (buf + 56) = shift16(flip16(24), 1);

		getTime(&internalTime);
		fromInternalTime(&internalTime, &externalTime, ptpClock->get_halfEpoch());
		*(Integer32 *) (buf + 60) = flip32(externalTime.get_seconds());
		*(Integer32 *) (buf + 64) = flip32(externalTime.get_nanoseconds());

		*(Integer32 *) (buf + 68) = shift16(flip16(ptpClock->get_current_utc_offset()), 1);
		*(Integer32 *) (buf + 72) = shift8(ptpClock->get_leap59(), 3);
		*(Integer32 *) (buf + 76) = shift8(ptpClock->get_leap61(), 3);
		*(Integer32 *) (buf + 80) = shift16(flip16(ptpClock->get_epoch_number()), 1);
		return 84;

	case PTP_MM_GET_FOREIGN_DATA_SET:
		if ((manage->get_targetPortId() && manage->get_targetPortId() != ptpClock->get_port_id_field())
		    || !manage->get_recordKey() || manage->get_recordKey() > ptpClock->get_number_foreign_records()) {
			*(UInteger8 *) (buf + 55) = PTP_MM_NULL;
			*(Integer32 *) (buf + 56) = shift16(flip16(0), 1);
			return 0;
		}
		*(UInteger8 *) (buf + 55) = PTP_MM_FOREIGN_DATA_SET;
		*(Integer32 *) (buf + 56) = shift16(flip16(28), 1);
		*(Integer32 *) (buf + 60) = shift16(flip16(ptpClock->get_port_id_field()), 1);
		*(Integer32 *) (buf + 64) = shift16(flip16(manage->get_recordKey() - 1), 1);
//		*(Integer32 *) (buf + 68) = shift8(ptpClock->foreign[manage->recordKey - 1].foreign_master_communication_technology, 3);
		*(Integer32 *) (buf + 68) = shift8(ptpClock->get_foreign().get_foreign_master_communication_technology(), 3);
//		memcpy(buf + 72, ptpClock->foreign[manage->recordKey - 1].foreign_master_uuid, 6);
		memcpy(buf + 72, ptpClock->get_foreign().get_foreign_master_uuid(), 6);
//		*(Integer32 *) (buf + 80) = shift16(flip16(ptpClock->foreign[manage->recordKey - 1].foreign_master_port_id), 1);
//		*(Integer32 *) (buf + 84) = shift16(flip16(ptpClock->foreign[manage->recordKey - 1].foreign_master_syncs), 1);
		*(Integer32 *) (buf + 80) = shift16(flip16(ptpClock->get_foreign().get_foreign_master_port_id()), 1);
		*(Integer32 *) (buf + 84) = shift16(flip16(ptpClock->get_foreign().get_foreign_master_syncs()), 1);
		return 88;

	default:
		return 0;
	}
}
