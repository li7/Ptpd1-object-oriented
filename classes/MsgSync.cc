#include "MsgSync.h"
#include <iostream>
#include <string.h>

using namespace std;

MsgSync::MsgSync()
{
        epochNumber = 0;
        currentUTCOffset = 0;
        grandmasterCommunicationTechnology = 0;
        grandmasterPortId = 0;
        grandmasterSequenceId = 0;
        grandmasterClockStratum = 0;
        grandmasterClockVariance = 0;
        grandmasterPreferred = true;
        grandmasterIsBoundaryClock = true;
        syncInterval = 0;
        localClockVariance = 0;
        localStepsRemoved = 0;
        localClockStratum = 0;
        parentCommunicationTechnology = 0;
        parentPortField = 0;
        estimatedMasterVariance = 0;
        estimatedMasterDrift = 0;
        utcReasonable = false;
}

/********************* Accessors ********************/
TimeRepresentation& MsgSync::get_originTimestamp()
{	
	return originTimestamp;
}

UInteger32 MsgSync::get_originTimestamp_seconds() const
{return originTimestamp.get_seconds();}

Integer32 MsgSync::get_originTimestamp_nanoseconds() const
{return originTimestamp.get_nanoseconds();}

UInteger16 MsgSync::get_epochNumber() const 
{return epochNumber;}

Integer16 MsgSync::get_currentUTCOffset() const
{return currentUTCOffset;}

UInteger8 MsgSync::get_grandmasterCommunicationTechnology() const 
{return grandmasterCommunicationTechnology;}

Octet* MsgSync::get_grandmasterClockUuid()
{return grandmasterClockUuid;}

UInteger16 MsgSync::get_grandmasterPortId() const
{return grandmasterPortId;}

UInteger16 MsgSync::get_grandmasterSequenceId() const
{return grandmasterSequenceId;}

UInteger8 MsgSync::get_grandmasterClockStratum() const
{return grandmasterClockStratum;}

Octet* MsgSync::get_grandmasterClockIdentifier()
{return grandmasterClockIdentifier;}

Integer16 MsgSync::get_grandmasterClockVariance() const
{return grandmasterClockVariance;}

Boolean MsgSync::get_grandmasterPreferred() const
{return grandmasterPreferred;}

Boolean MsgSync::get_grandmasterIsBoundaryClock() const
{return grandmasterIsBoundaryClock;}

Integer8 MsgSync::get_syncInterval() const
{return syncInterval;}

Integer16 MsgSync::get_localClockVariance() const
{return localClockVariance;}

UInteger16 MsgSync::get_localStepsRemoved() const
{return localStepsRemoved;}

UInteger8 MsgSync::get_localClockStratum() const
{return localClockStratum;}

Octet MsgSync::get_localClockIdentifier() const
{return *localClockIdentifier;}

UInteger8 MsgSync::get_parentCommunicationTechnology() const
{return parentCommunicationTechnology;}

Octet MsgSync::get_parentUuid() const
{return *parentUuid;}

UInteger16 MsgSync::get_parentPortField() const
{return parentPortField;}

Integer16 MsgSync::get_estimatedMasterVariance() const
{return estimatedMasterVariance;}

Integer32 MsgSync::get_estimatedMasterDrift() const
{return estimatedMasterDrift;}

Boolean MsgSync::get_utcReasonable() const
{return utcReasonable;}

/******************* Mutators *******************/
void MsgSync::set_originTimestamp(TimeRepresentation ots)
{originTimestamp = ots;}

void MsgSync::set_originTimestamp_seconds(UInteger32 sec)
{originTimestamp.set_seconds(sec);}

void MsgSync::set_originTimestamp_nanoseconds(Integer32 nsec)
{originTimestamp.set_nanoseconds(nsec);}

void MsgSync::set_epochNumber(UInteger16 en)
{epochNumber = en;}

void MsgSync::set_currentUTCOffset(Integer16 cutco)
{currentUTCOffset = cutco;}

void MsgSync::set_grandmasterCommunicationTechnology(UInteger8 gmct)
{grandmasterCommunicationTechnology = gmct;}

void MsgSync::set_grandmasterClockUuid(const void *gmcu, int length)
{memcpy(grandmasterClockUuid,gmcu,length);}

void MsgSync::set_grandmasterPortId(UInteger16 gmpi)
{grandmasterPortId = gmpi;}

void MsgSync::set_grandmasterPreferred(Boolean gmp)
{grandmasterPreferred = gmp;}

void MsgSync::set_grandmasterSequenceId(UInteger16 gmsi)
{grandmasterSequenceId = gmsi;}

void MsgSync::set_grandmasterClockStratum(UInteger8 gmcs)
{grandmasterClockStratum = gmcs;}

void MsgSync::set_grandmasterClockIdentifier(const void *gmci, int length)
{memcpy(grandmasterClockIdentifier,gmci,length);}

void MsgSync::set_grandmasterClockVariance(Integer16 gmcv)
{grandmasterClockVariance = gmcv;}

void MsgSync::set_grandmasterIsBoundaryClock(Boolean gmbc)
{grandmasterIsBoundaryClock = gmbc;}

void MsgSync::set_syncInterval(Integer8 si)
{syncInterval = si;}

void MsgSync::set_localClockVariance(Integer16 lcv)
{localClockVariance = lcv;}

void MsgSync::set_localStepsRemoved(UInteger16 lsr)
{localStepsRemoved = lsr;}

void MsgSync::set_localClockStratum(UInteger8 lcs)
{localClockStratum = lcs;}

void MsgSync::set_localClockIdentifier(const void *lci, int length)
{memcpy(localClockIdentifier,lci,length);}

void MsgSync::set_parentCommunicationTechnology(UInteger8 pct)
{parentCommunicationTechnology = pct;}

void MsgSync::set_parentUuid(const void *pu, int length)
{memcpy(parentUuid,pu,length);}

void MsgSync::set_parentPortField(UInteger16 ppf)
{parentPortField = ppf;}

void MsgSync::set_estimatedMasterVariance(Integer16 emv)
{estimatedMasterVariance = emv;}

void MsgSync::set_estimatedMasterDrift(Integer32 emd)
{estimatedMasterDrift = emd;}

void MsgSync::set_utcReasonable(Boolean ur)
{utcReasonable = ur;}

MsgSync &MsgSync::operator=(const MsgSync & other)
{
	originTimestamp = other.originTimestamp;
	epochNumber = other.epochNumber;
	currentUTCOffset = other.currentUTCOffset;
	grandmasterCommunicationTechnology = other.grandmasterCommunicationTechnology;
	memcpy(grandmasterClockUuid,other.grandmasterClockUuid,PTP_UUID_LENGTH);
	grandmasterPortId = other.grandmasterPortId;
	grandmasterSequenceId = other.grandmasterSequenceId;
	grandmasterClockStratum = other.grandmasterClockStratum;
	memcpy(grandmasterClockIdentifier,other.grandmasterClockIdentifier,PTP_CODE_STRING_LENGTH);
	grandmasterClockVariance = other.grandmasterClockVariance;
	grandmasterPreferred = other.grandmasterPreferred;
	grandmasterIsBoundaryClock = other.grandmasterIsBoundaryClock;
	syncInterval = other.syncInterval;
	localClockVariance = other.localClockVariance;
	localStepsRemoved = other.localStepsRemoved;
	localClockStratum = other.localClockStratum;
	memcpy(localClockIdentifier,other.localClockIdentifier,PTP_CODE_STRING_LENGTH);
	parentCommunicationTechnology = other.parentCommunicationTechnology;
	memcpy(parentUuid,other.parentUuid,PTP_UUID_LENGTH);
	parentPortField = other.parentPortField;
	estimatedMasterVariance = other.estimatedMasterVariance;
	estimatedMasterDrift = other.estimatedMasterDrift;
	utcReasonable = other.utcReasonable;

	return *this;
}

ostream& operator<<(ostream& sit, const MsgSync& it)
{
	cout << "originTimestamp" << it.originTimestamp << endl;
	cout << "estimatedMasterDrift " << it.estimatedMasterDrift << endl;
	cout << "estimatedMasterVariance " << it.estimatedMasterVariance << endl;

	return sit;
}
