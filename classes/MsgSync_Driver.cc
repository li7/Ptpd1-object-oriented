#include "MsgSync.h"

main()
{
	MsgSync sync1;
	TimeRepresentation tr;

	cout << sync1 << endl;
//	    tr = sync1.get_originTimestamp();
//	    tr.set_seconds(55);
//	    tr.set_nanoseconds(15);
//	    sync1.set_originTimestamp(tr);
	
//	    sync1.set_originTimestamp_seconds(60);
	sync1.get_originTimestamp().set_seconds(2);
	sync1.get_originTimestamp().set_nanoseconds(3);

            sync1.set_epochNumber(1);
            sync1.set_currentUTCOffset(2);
            sync1.set_grandmasterCommunicationTechnology('c');
            sync1.set_grandmasterClockUuid(DEFAULT_PTP_DOMAIN_NAME,PTP_SUBDOMAIN_NAME_LENGTH);
            sync1.set_grandmasterPortId(3);
            sync1.set_grandmasterSequenceId(4);
            sync1.set_grandmasterClockStratum(5);
            //sync1.set_grandmasterClockIdentifier('b',1);
            sync1.set_grandmasterClockVariance(6);
            sync1.set_grandmasterPreferred(false);
            sync1.set_grandmasterIsBoundaryClock(false);
            sync1.set_syncInterval(7);
            sync1.set_localClockVariance(8);
            sync1.set_localStepsRemoved(9);
            sync1.set_localClockStratum(10);
            //sync1.set_localClockIdentifer('c',1);
            sync1.set_parentCommunicationTechnology(11);
            //sync1.set_parentUuid('d',1);
            sync1.set_parentPortField(12);
            sync1.set_estimatedMasterVariance(13);
            sync1.set_estimatedMasterDrift(14);
            sync1.set_utcReasonable(false);
	
	//cout << tr << endl;
	cout << "sync1" << sync1 << endl;
}
