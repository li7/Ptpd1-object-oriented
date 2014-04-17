/**
 * @file   probe.c
 * @date   Tue Jul 20 16:13:30 2010
 * 
 * @brief  Management packet handling
 * 
 * 
 */

#include "classes/ptpd.h"

#define KEY_ARRAY_LEN 6
UInteger8 management_key_array[KEY_ARRAY_LEN] =
{PTP_MM_OBTAIN_IDENTITY, PTP_MM_GET_DEFAULT_DATA_SET, PTP_MM_GET_CURRENT_DATA_SET,
PTP_MM_GET_PARENT_DATA_SET, PTP_MM_GET_PORT_DATA_SET, PTP_MM_GET_GLOBAL_TIME_DATA_SET};

void	displayHeader(MsgHeader *);
void	displayManagement(MsgHeader *, MsgManagement *);

void 
probe(RunTimeOpts * rtOpts, PtpClock * ptpClock)
{
	UInteger16 i;
	UInteger16 length;
	TimeInternal interval, now, finish, timestamp;

	/* check */
	if (rtOpts->get_probe_management_key() == PTP_MM_UPDATE_DEFAULT_DATA_SET
	    || rtOpts->get_probe_management_key() == PTP_MM_UPDATE_GLOBAL_TIME_PROPERTIES
	    || rtOpts->get_probe_management_key() == PTP_MM_SET_SYNC_INTERVAL) {
		ERROR("send not supported for that management message\n");
		return;
	}
	/* init */
	if (!netInit(&ptpClock->get_netPath(), rtOpts, ptpClock)) {
		ERROR("failed to initialize network\n");
		return;
	}
	initData(rtOpts, ptpClock);
	msgPackHeader(ptpClock->get_msgObuf(), ptpClock);

	//&ptpClock->get_msgtmp()->set_manage(0, sizeof(MsgManagement));
	ptpClock->get_msgtmp().get_manage().set_targetCommunicationTechnology(PTP_DEFAULT);

	/* send */
	for (i = 0; i < KEY_ARRAY_LEN; ++i) {
		if (rtOpts->get_probe_management_key() > 0) {
			ptpClock->get_msgtmp().get_manage().set_managementMessageKey(rtOpts->get_probe_management_key());
			ptpClock->get_msgtmp().get_manage().set_recordKey(rtOpts->get_probe_record_key());
		} else
			ptpClock->get_msgtmp().get_manage().set_managementMessageKey(management_key_array[i]);

		if (!(length = msgPackManagement(ptpClock->get_msgObuf(), &ptpClock->get_msgtmp().get_manage(), ptpClock))) {
			ERROR("failed to pack management message\n");
			return;
		}
		printf("\n(sending managementMessageKey %hhu)\n", ptpClock->get_msgtmp().get_manage().get_managementMessageKey());

		if (!netSendGeneral(ptpClock->get_msgObuf(), length, &ptpClock->get_netPath())) {
			ERROR("failed to send message\n");
			return;
		}
		if (rtOpts->get_probe_management_key() > 0)
			break;
	}

	getTime(&finish);
	finish.set_seconds(finish.get_seconds() + PTP_SYNC_INTERVAL_TIMEOUT(ptpClock->get_sync_interval()));
	for (;;) {
		interval.set_seconds(PTP_SYNC_INTERVAL_TIMEOUT(ptpClock->get_sync_interval()));
		interval.set_nanoseconds(0);
		netSelect(&interval, &ptpClock->get_netPath());

		netRecvEvent(ptpClock->get_msgIbuf(), &timestamp, &ptpClock->get_netPath());

		if (netRecvGeneral(ptpClock->get_msgIbuf(), &ptpClock->get_netPath())) {
			msgUnpackHeader(ptpClock->get_msgIbuf(), &ptpClock->get_msgTmpHeader());

			if (ptpClock->get_msgTmpHeader().get_control() == PTP_MANAGEMENT_MESSAGE) {
				msgUnpackManagement(ptpClock->get_msgIbuf(), &ptpClock->get_msgtmp().get_manage());
				msgUnpackManagementPayload(ptpClock->get_msgIbuf(), &ptpClock->get_msgtmp().get_manage());

				displayManagement(&ptpClock->get_msgTmpHeader(), &ptpClock->get_msgtmp().get_manage());
			}
			fflush(stdout);
		}
		getTime(&now);
		if (now.get_seconds() > finish.get_seconds() || (now.get_seconds() == finish.get_seconds()
		    && now.get_nanoseconds() > finish.get_nanoseconds()))
			break;
	}

	/* done */
	printf("\n");
	ptpdShutdown();

	exit(0);
}

void 
displayHeader(MsgHeader * header)
{
	printf(
	    "  sourceCommunicationTechnology %hhu\n"
	    "  sourceUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n"
	    "  sourcePortId %hu\n",
	    header->get_sourceCommunicationTechnology(),
	    header->get_sourceUuid(0), header->get_sourceUuid(1), header->get_sourceUuid(2),
	    header->get_sourceUuid(3), header->get_sourceUuid(4), header->get_sourceUuid(5),
	    header->get_sourcePortId());
}

void 
displayManagement(MsgHeader * header, MsgManagement * manage)
{
	Integer16 i;

	switch (manage->get_managementMessageKey()) {
	case PTP_MM_CLOCK_IDENTITY:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (PTP_MM_CLOCK_IDENTITY)\n", manage->get_managementMessageKey());
		printf("  clockCommunicationTechnology %hhu\n", manage->get_payload().get_clockIdentity().get_clockCommunicationTechnology());
		printf("  clockUuidField %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    manage->get_payload().get_clockIdentity().get_clockUuidField(0), manage->get_payload().get_clockIdentity().get_clockUuidField(1),
		    manage->get_payload().get_clockIdentity().get_clockUuidField(2), manage->get_payload().get_clockIdentity().get_clockUuidField(3),
		    manage->get_payload().get_clockIdentity().get_clockUuidField(4), manage->get_payload().get_clockIdentity().get_clockUuidField(5));
		printf("  clockPortField %hu\n", manage->get_payload().get_clockIdentity().get_clockPortField());
		printf("  manufacturerIdentity ");
		for (i = 0; i < MANUFACTURER_ID_LENGTH && manage->get_payload().get_clockIdentity().get_manufacturerIdentity(i); ++i)
			putchar(manage->get_payload().get_clockIdentity().get_manufacturerIdentity(i));
		putchar('\n');
		break;

	case PTP_MM_DEFAULT_DATA_SET:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (PTP_MM_DEFAULT_DATA_SET)\n", manage->get_managementMessageKey());
		printf("  clockCommunicationTechnology %hhu\n", manage->get_payload().get_defaultData().get_clockCommunicationTechnology());
		printf("  clockUuidField %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    manage->get_payload().get_defaultData().get_clockUuidField(0), manage->get_payload().get_defaultData().get_clockUuidField(1),
		    manage->get_payload().get_defaultData().get_clockUuidField(2), manage->get_payload().get_defaultData().get_clockUuidField(3),
		    manage->get_payload().get_defaultData().get_clockUuidField(4), manage->get_payload().get_defaultData().get_clockUuidField(5));
		printf("  clockPortField %hu\n", manage->get_payload().get_defaultData().get_clockPortField());
		printf("  clockStratum %hhu\n", manage->get_payload().get_defaultData().get_clockStratum());
		printf("  clockIdentifier ");
		for (i = 0; i < PTP_CODE_STRING_LENGTH && manage->get_payload().get_defaultData().get_clockIdentifier(i); ++i)
			putchar(manage->get_payload().get_defaultData().get_clockIdentifier(i));
		putchar('\n');
		printf("  clockVariance %hd\n", manage->get_payload().get_defaultData().get_clockVariance());
		printf("  clockFollowupCapable %hhu\n", manage->get_payload().get_defaultData().get_clockFollowupCapable());
		printf("  preferred %hhu\n", manage->get_payload().get_defaultData().get_preferred());
		printf("  initializable %hhu\n", manage->get_payload().get_defaultData().get_initializable());
		printf("  externalTiming %hhu\n", manage->get_payload().get_defaultData().get_externalTiming());
		printf("  isBoundaryClock %hhu\n", manage->get_payload().get_defaultData().get_isBoundaryClock());
		printf("  syncInterval %hhd\n", manage->get_payload().get_defaultData().get_syncInterval());
		printf("  subdomainName ");
		for (i = 0; i < PTP_SUBDOMAIN_NAME_LENGTH && manage->get_payload().get_defaultData().get_subdomainName(i); ++i)
			putchar(manage->get_payload().get_defaultData().get_subdomainName(i));
		putchar('\n');
		printf("  numberPorts %hu\n", manage->get_payload().get_defaultData().get_numberPorts());
		printf("  numberForeignRecords %hu\n", manage->get_payload().get_defaultData().get_numberForeignRecords());
		break;

	case PTP_MM_CURRENT_DATA_SET:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (PTP_MM_CURRENT_DATA_SET)\n", manage->get_managementMessageKey());
		printf("  stepsRemoved %hu\n", manage->get_payload().get_current().get_stepsRemoved());
		printf("  offsetFromMaster %s%u.%09d\n",
		    manage->get_payload().get_current().get_offsetFromMaster().get_nanoseconds() & 0x80000000 ? "-" : "",
		    manage->get_payload().get_current().get_offsetFromMaster().get_seconds(),
		    manage->get_payload().get_current().get_offsetFromMaster().get_nanoseconds() & ~0x80000000);
		printf("  oneWayDelay %s%u.%09d\n",
		    manage->get_payload().get_current().get_oneWayDelay().get_nanoseconds() & 0x80000000 ? "-" : "",
		    manage->get_payload().get_current().get_oneWayDelay().get_seconds(),
		    manage->get_payload().get_current().get_oneWayDelay().get_nanoseconds() & ~0x80000000);
		break;

	case PTP_MM_PARENT_DATA_SET:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (PTP_MM_PARENT_DATA_SET)\n", manage->get_managementMessageKey());
		printf("  parentCommunicationTechnology %hhu\n", manage->get_payload().get_parent().get_parentCommunicationTechnology());
		printf("  parentUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    manage->get_payload().get_parent().get_parentUuid(0), manage->get_payload().get_parent().get_parentUuid(1),
		    manage->get_payload().get_parent().get_parentUuid(2), manage->get_payload().get_parent().get_parentUuid(3),
		    manage->get_payload().get_parent().get_parentUuid(4), manage->get_payload().get_parent().get_parentUuid(5));
		printf("  parentPortId %hu\n", manage->get_payload().get_parent().get_parentPortId());
		printf("  parentLastSyncSequenceNumber %hu\n", manage->get_payload().get_parent().get_parentLastSyncSequenceNumber());
		printf("  parentFollowupCapable %hhu\n", manage->get_payload().get_parent().get_parentFollowupCapable());
		printf("  parentExternalTiming %hhu\n", manage->get_payload().get_parent().get_parentExternalTiming());
		printf("  parentVariance %hd\n", manage->get_payload().get_parent().get_parentVariance());
		printf("  parentStats %hhu\n", manage->get_payload().get_parent().get_parentStats());
		printf("  observedVariance %hd\n", manage->get_payload().get_parent().get_observedVariance());
		printf("  observedDrift %d\n", manage->get_payload().get_parent().get_observedDrift());
		printf("  utcReasonable %hhu\n", manage->get_payload().get_parent().get_utcReasonable());
		printf("  grandmasterCommunicationTechnology %hhu\n", manage->get_payload().get_parent().get_grandmasterCommunicationTechnology());
		printf("  grandmasterUuidField %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    manage->get_payload().get_parent().get_grandmasterUuidField(0), manage->get_payload().get_parent().get_grandmasterUuidField(1),
		    manage->get_payload().get_parent().get_grandmasterUuidField(2), manage->get_payload().get_parent().get_grandmasterUuidField(3),
		    manage->get_payload().get_parent().get_grandmasterUuidField(4), manage->get_payload().get_parent().get_grandmasterUuidField(5));
		printf("  grandmasterPortIdField %hu\n", manage->get_payload().get_parent().get_grandmasterPortIdField());
		printf("  grandmasterStratum %hhu\n", manage->get_payload().get_parent().get_grandmasterStratum());
		printf("  grandmasterIdentifier ");
		for (i = 0; i < PTP_CODE_STRING_LENGTH && manage->get_payload().get_parent().get_grandmasterIdentifier(i); ++i)
			putchar(manage->get_payload().get_parent().get_grandmasterIdentifier(i));
		putchar('\n');
		printf("  grandmasterVariance %hd\n", manage->get_payload().get_parent().get_grandmasterVariance());
		printf("  grandmasterPreferred %hhu\n", manage->get_payload().get_parent().get_grandmasterPreferred());
		printf("  grandmasterIsBoundaryClock %hhu\n", manage->get_payload().get_parent().get_grandmasterIsBoundaryClock());
		printf("  grandmasterSequenceNumber %hu\n", manage->get_payload().get_parent().get_grandmasterSequenceNumber());
		break;

	case PTP_MM_PORT_DATA_SET:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (PTP_MM_PORT_DATA_SET)\n", manage->get_managementMessageKey());
		printf("  returnedPortNumber %hu\n", manage->get_payload().get_port().get_returnedPortNumber());
		printf("  portState %hhu\n", manage->get_payload().get_port().get_portState());
		printf("  lastSyncEventSequenceNumber %hu\n", manage->get_payload().get_port().get_lastSyncEventSequenceNumber());
		printf("  lastGeneralEventSequenceNumber %hu\n", manage->get_payload().get_port().get_lastGeneralEventSequenceNumber());
		printf("  portCommunicationTechnology %hhu\n", manage->get_payload().get_port().get_portCommunicationTechnology());
		printf("  portUuidField %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    manage->get_payload().get_port().get_portUuidField(0), manage->get_payload().get_port().get_portUuidField(1),
		    manage->get_payload().get_port().get_portUuidField(2), manage->get_payload().get_port().get_portUuidField(3),
		    manage->get_payload().get_port().get_portUuidField(4), manage->get_payload().get_port().get_portUuidField(5));
		printf("  portIdField %hu\n", manage->get_payload().get_port().get_portIdField());
		printf("  burstEnabled %hhu\n", manage->get_payload().get_port().get_burstEnabled());
		printf("  subdomainAddressOctets %hhu\n", manage->get_payload().get_port().get_subdomainAddressOctets());
		printf("  eventPortAddressOctets %hhu\n", manage->get_payload().get_port().get_eventPortAddressOctets());
		printf("  generalPortAddressOctets %hhu\n", manage->get_payload().get_port().get_generalPortAddressOctets());
		printf("  subdomainAddress ");
		printf("%hhu", manage->get_payload().get_port().get_subdomainAddress(0));
		for (i = 1; i < SUBDOMAIN_ADDRESS_LENGTH; ++i)
			printf(".%hhu", manage->get_payload().get_port().get_subdomainAddress(i));
		putchar('\n');
		printf("  eventPortAddress %hu\n", *(UInteger16 *) manage->get_payload().get_port().get_eventPortAddress());
		printf("  generalPortAddress %hu\n", *(UInteger16 *) manage->get_payload().get_port().get_generalPortAddress());
		break;

	case PTP_MM_GLOBAL_TIME_DATA_SET:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (PTP_MM_GLOBAL_TIME_DATA_SET)\n", manage->get_managementMessageKey());
		printf("  localTime %s%u.%09d\n",
		    manage->get_payload().get_globalTime().get_localTime().get_nanoseconds() & 0x80000000 ? "-" : "",
		    manage->get_payload().get_globalTime().get_localTime().get_seconds(),
		    manage->get_payload().get_globalTime().get_localTime().get_nanoseconds() & ~0x80000000);
		printf("  currentUtcOffset %hd\n", manage->get_payload().get_globalTime().get_currentUtcOffset());
		printf("  leap59 %hhu\n", manage->get_payload().get_globalTime().get_leap59());
		printf("  leap61 %hhu\n", manage->get_payload().get_globalTime().get_leap61());
		printf("  epochNumber %hu\n", manage->get_payload().get_globalTime().get_epochNumber());
		break;


	case PTP_MM_FOREIGN_DATA_SET:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (PTP_MM_FOREIGN_DATA_SET)\n", manage->get_managementMessageKey());
		printf("  returnedPortNumber %hu\n", manage->get_payload().get_foreign().get_returnedPortNumber());
		printf("  returnedRecordNumber %hu\n", manage->get_payload().get_foreign().get_returnedRecordNumber());
		printf("  foreignMasterCommunicationTechnology %hu\n", manage->get_payload().get_foreign().get_foreignMasterCommunicationTechnology());
		printf("  foreignMasterUuid %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
		    manage->get_payload().get_foreign().get_foreignMasterUuid(0), manage->get_payload().get_foreign().get_foreignMasterUuid(1),
		    manage->get_payload().get_foreign().get_foreignMasterUuid(2), manage->get_payload().get_foreign().get_foreignMasterUuid(3),
		    manage->get_payload().get_foreign().get_foreignMasterUuid(4), manage->get_payload().get_foreign().get_foreignMasterUuid(5));

		printf("  foreignMasterPortId %hu\n", manage->get_payload().get_foreign().get_foreignMasterPortId());
		printf("  foreignMasterSyncs %hu\n", manage->get_payload().get_foreign().get_foreignMasterSyncs());
		break;

	case PTP_MM_NULL:
		printf("\n");
		displayHeader(header);
		printf("  managementMessageKey %hhu (NULL)\n", manage->get_managementMessageKey());
		break;

	default:
		break;
	}

	return;
}
