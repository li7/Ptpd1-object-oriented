#include "Parent.h"
#include <string.h>
#include <iostream>

using namespace std;

/*****************Constructor****************/
Parent::Parent()
{
        parentCommunicationTechnology=0;
        memset(&parentUuid,0,PTP_UUID_LENGTH);
        parentPortId=0;
        parentLastSyncSequenceNumber=0;
        parentFollowupCapable=0;
        parentExternalTiming=0;
        parentVariance=0;
        parentStats=0;
        observedVariance=0;
        observedDrift=0;
        utcReasonable=0;
        grandmasterCommunicationTechnology=0;
        memset(&grandmasterUuidField,0,PTP_UUID_LENGTH);
        grandmasterPortIdField=0;
        grandmasterStratum=0;
        memset(&grandmasterIdentifier,0,PTP_CODE_STRING_LENGTH);
        grandmasterVariance=0;
        grandmasterPreferred=0;
        grandmasterIsBoundaryClock=0;
        grandmasterSequenceNumber=0;

}

/*****************accessors***************/
UInteger8 Parent::get_parentCommunicationTechnology() const
{return parentCommunicationTechnology;}

Octet Parent::get_parentUuid() const
{return *parentUuid;}

Octet Parent::get_parentUuid(int i) const
{return parentUuid[i];}

UInteger16 Parent::get_parentPortId() const
{return parentPortId;}

UInteger16 Parent::get_parentLastSyncSequenceNumber() const
{return parentLastSyncSequenceNumber;}

Boolean Parent::get_parentFollowupCapable() const
{return parentFollowupCapable;}

Boolean Parent::get_parentExternalTiming() const
{return parentExternalTiming;}

Integer16 Parent::get_parentVariance() const
{return parentVariance;}

Boolean Parent::get_parentStats() const
{return parentStats;}

Integer16 Parent::get_observedVariance() const
{return observedVariance;}

Integer32 Parent::get_observedDrift() const
{return observedDrift;}

Boolean Parent::get_utcReasonable() const
{return utcReasonable;}

UInteger8 Parent::get_grandmasterCommunicationTechnology() const
{return grandmasterCommunicationTechnology;}

Octet Parent::get_grandmasterUuidField(int i) const
{return grandmasterUuidField[i];}

UInteger16 Parent::get_grandmasterPortIdField() const
{return grandmasterPortIdField;}

UInteger8 Parent::get_grandmasterStratum() const
{return grandmasterStratum;}

Octet Parent::get_grandmasterIdentifier() const
{return *grandmasterIdentifier;}

Octet Parent::get_grandmasterIdentifier(int i) const
{return grandmasterIdentifier[i];}

Integer16 Parent::get_grandmasterVariance() const
{return grandmasterVariance;}

Boolean Parent::get_grandmasterPreferred() const
{return grandmasterPreferred;}

Boolean Parent::get_grandmasterIsBoundaryClock() const
{return grandmasterIsBoundaryClock;}

UInteger16 Parent::get_grandmasterSequenceNumber() const
{return grandmasterSequenceNumber;}

/****************mutators******************/
void Parent::set_parentCommunicationTechnology(UInteger8 pct)
{parentCommunicationTechnology = pct;}

void Parent::set_parentUuid(const void *pu, int length)
{memcpy(parentUuid,pu,length);}

void Parent::set_parentPortId(UInteger16 ppi)
{parentPortId = ppi;}

void Parent::set_parentLastSyncSequenceNumber(UInteger16 plss)
{parentLastSyncSequenceNumber = plss;}

void Parent::set_parentFollowupCapable(Boolean pfc)
{parentFollowupCapable = pfc;}

void Parent::set_parentExternalTiming(Boolean pet)
{parentExternalTiming = pet;}

void Parent::set_parentVariance(Integer16 pv)
{parentVariance = pv;}

void Parent::set_parentStats(Boolean ps)
{parentStats = ps;}

void Parent::set_observedVariance(Integer16 ov)
{observedVariance = ov;}

void Parent::set_observedDrift(Integer32 od)
{observedDrift = od;}

void Parent::set_utcReasonable(Boolean ur)
{utcReasonable = ur;}

void Parent::set_grandmasterCommunicationTechnology(UInteger8 gct)
{grandmasterCommunicationTechnology = gct;}

void Parent::set_grandmasterUuidField(const void *guf, int length)
{memcpy(grandmasterUuidField,guf,length);}

void Parent::set_grandmasterPortIdField(UInteger16 gpf)
{grandmasterPortIdField = gpf;}

void Parent::set_grandmasterStratum(UInteger8 gs)
{grandmasterStratum = gs;}

void Parent::set_grandmasterIdentifier(const void *gi, int length)
{memcpy(grandmasterIdentifier,gi,length);}

void Parent::set_grandmasterVariance(Integer16 gv)
{grandmasterVariance = gv;}

void Parent::set_grandmasterPreferred(Boolean gp)
{grandmasterPreferred = gp;}

void Parent::set_grandmasterIsBoundaryClock(Boolean gibc)
{grandmasterIsBoundaryClock = gibc;}

void Parent::set_grandmasterSequenceNumber(UInteger16 gsn)
{grandmasterSequenceNumber = gsn;}

Parent &Parent::operator=(const Parent & other_t)
{
	parentCommunicationTechnology = other_t.parentCommunicationTechnology;
	memcpy(parentUuid,other_t.parentUuid,strlen(parentUuid));
	parentPortId = other_t.parentPortId;
	parentLastSyncSequenceNumber = other_t.parentLastSyncSequenceNumber;
	parentFollowupCapable = other_t.parentFollowupCapable;
	parentExternalTiming = other_t.parentExternalTiming;
	parentVariance = other_t.parentVariance;
	parentStats = other_t.parentStats;
	observedVariance = other_t.observedVariance;
	observedDrift = other_t.observedDrift;
	utcReasonable = other_t.utcReasonable;
	grandmasterCommunicationTechnology = other_t.grandmasterCommunicationTechnology;
	memcpy(grandmasterUuidField,other_t.grandmasterUuidField,strlen(grandmasterUuidField));
	grandmasterPortIdField = other_t.grandmasterPortIdField;
	grandmasterStratum = other_t.grandmasterStratum;
	memcpy(grandmasterIdentifier,other_t.grandmasterIdentifier,strlen(grandmasterIdentifier));
	grandmasterVariance = other_t.grandmasterVariance;
	grandmasterPreferred = other_t.grandmasterPreferred;
	grandmasterIsBoundaryClock = other_t.grandmasterIsBoundaryClock;
	grandmasterSequenceNumber = other_t.grandmasterSequenceNumber;
	return *this;
}
ostream& operator<<(ostream& s, const Parent& it)
{
	cout << "observedDrift : " << it.observedDrift << endl;
        return s;
}

