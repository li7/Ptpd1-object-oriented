#ifndef MSGSYNC_H
#define MSGSYNC_H
#include "constants.h"
#include "TimeRepresentation.h"
#include <iostream>

using namespace std;

class MsgSync{

public:
	/* constructor */
	MsgSync();

	/* accessors */
	    //TimeRepresentation get_originTimestamp() const;
	    TimeRepresentation& get_originTimestamp();

	    UInteger32 get_originTimestamp_seconds() const;
	    Integer32 get_originTimestamp_nanoseconds() const;

            UInteger16 get_epochNumber() const;
            Integer16 get_currentUTCOffset() const;
            UInteger8 get_grandmasterCommunicationTechnology() const;
            Octet*   get_grandmasterClockUuid();
            UInteger16 get_grandmasterPortId() const;
            UInteger16 get_grandmasterSequenceId() const;
            UInteger8 get_grandmasterClockStratum() const;
            Octet*   get_grandmasterClockIdentifier();
            Integer16 get_grandmasterClockVariance() const;
            Boolean get_grandmasterPreferred() const;
            Boolean get_grandmasterIsBoundaryClock() const;
            Integer8 get_syncInterval() const;
            Integer16 get_localClockVariance() const;
            UInteger16 get_localStepsRemoved() const;
            UInteger8 get_localClockStratum() const;
            Octet   get_localClockIdentifier() const;
            UInteger8 get_parentCommunicationTechnology() const;
            Octet   get_parentUuid() const;
            UInteger16 get_parentPortField() const;
            Integer16 get_estimatedMasterVariance() const;
            Integer32 get_estimatedMasterDrift() const;
            Boolean get_utcReasonable() const;

	/* mutators */
	    void set_originTimestamp(TimeRepresentation ots);

	    void set_originTimestamp_seconds(UInteger32 sec);
	    void set_originTimestamp_nanoseconds(Integer32 nsec);

            void set_epochNumber(UInteger16 epn);
            void set_currentUTCOffset(Integer16 cutco);
            void set_grandmasterCommunicationTechnology(UInteger8 gmct);
            void set_grandmasterClockUuid(const void *gmcu, int length);
            void set_grandmasterPortId(UInteger16 gmpi);
            void set_grandmasterSequenceId(UInteger16 gmsi);
            void set_grandmasterClockStratum(UInteger8 gmcs);
            void set_grandmasterClockIdentifier(const void *gmci, int length);
            void set_grandmasterClockVariance(Integer16 gmcv);
            void set_grandmasterPreferred(Boolean gmp);
            void set_grandmasterIsBoundaryClock(Boolean gmbc);
            void set_syncInterval(Integer8 si);
            void set_localClockVariance(Integer16 lcv);
            void set_localStepsRemoved(UInteger16 lsr);
            void set_localClockStratum(UInteger8 lcs);
            void set_localClockIdentifier(const void *lci, int length);
            void set_parentCommunicationTechnology(UInteger8 pct);
            void set_parentUuid(const void *pu, int length);
            void set_parentPortField(UInteger16 ppf);
            void set_estimatedMasterVariance(Integer16 emv);
            void set_estimatedMasterDrift(Integer32 emd);
            void set_utcReasonable(Boolean utcr);

	/* operators */
	MsgSync &operator=(const MsgSync & other);
	friend ostream& operator<<(ostream& sit, const MsgSync& it);

private:
            TimeRepresentation originTimestamp;
            UInteger16 epochNumber;
            Integer16 currentUTCOffset;
            UInteger8 grandmasterCommunicationTechnology;
            Octet  grandmasterClockUuid[PTP_UUID_LENGTH];
            UInteger16 grandmasterPortId;
            UInteger16 grandmasterSequenceId;
            UInteger8 grandmasterClockStratum;
            Octet   grandmasterClockIdentifier[PTP_CODE_STRING_LENGTH];
            Integer16 grandmasterClockVariance;
            Boolean grandmasterPreferred;
            Boolean grandmasterIsBoundaryClock;
            Integer8 syncInterval;
            Integer16 localClockVariance;
            UInteger16 localStepsRemoved;
            UInteger8 localClockStratum;
            Octet  localClockIdentifier[PTP_CODE_STRING_LENGTH];
            UInteger8 parentCommunicationTechnology;
            Octet  parentUuid[PTP_UUID_LENGTH];
            UInteger16 parentPortField;
            Integer16 estimatedMasterVariance;
            Integer32 estimatedMasterDrift;
            Boolean utcReasonable;
};

ostream& operator<<(ostream& sit, const MsgSync& it);
#endif
