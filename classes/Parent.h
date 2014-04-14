#ifndef PARENT_H
#define PARENT_H
#include "constants.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class Parent{

public:

	/*************Constructor************/
	Parent();

	/****************accessors***********/
	UInteger8 get_parentCommunicationTechnology() const;
	Octet get_parentUuid() const;
	Octet get_parentUuid(int i) const;
	UInteger16 get_parentPortId() const;
	UInteger16 get_parentLastSyncSequenceNumber() const;
	Boolean get_parentFollowupCapable() const;
	Boolean get_parentExternalTiming() const;
	Integer16 get_parentVariance() const;
	Boolean get_parentStats() const;
	Integer16 get_observedVariance() const;
	Integer32 get_observedDrift() const;
	Boolean get_utcReasonable() const;
	UInteger8 get_grandmasterCommunicationTechnology() const;
	Octet get_grandmasterUuidField() const;
	Octet get_grandmasterUuidField(int i) const;
	UInteger16 get_grandmasterPortIdField() const;
	UInteger8 get_grandmasterStratum() const;
	Octet get_grandmasterIdentifier() const;
	Octet get_grandmasterIdentifier(int i) const;
	Integer16 get_grandmasterVariance() const;
	Boolean get_grandmasterPreferred() const;
	Boolean get_grandmasterIsBoundaryClock() const;
	UInteger16 get_grandmasterSequenceNumber() const;

	/****************mutators***********/
	void set_parentCommunicationTechnology(UInteger8 cct);
	void set_parentUuid(const void *pu, int length);
	void set_parentPortId(UInteger16 ppi);
	void set_parentLastSyncSequenceNumber(UInteger16 plss);
	void set_parentFollowupCapable(Boolean pfc);
	void set_parentExternalTiming(Boolean pet);
	void set_parentVariance(Integer16 pv);
	void set_parentStats(Boolean ps);
	void set_observedVariance(Integer16 ov);
	void set_observedDrift(Integer32 od);
	void set_utcReasonable(Boolean ur);
	void set_grandmasterCommunicationTechnology(UInteger8 gct);
	void set_grandmasterUuidField(const void *guf, int length);
	void set_grandmasterPortIdField(UInteger16 gpf);
	void set_grandmasterStratum(UInteger8 gs);
	void set_grandmasterIdentifier(const void *gi, int length);
	void set_grandmasterVariance(Integer16 gv);
	void set_grandmasterPreferred(Boolean gp);
	void set_grandmasterIsBoundaryClock(Boolean gibc);
	void set_grandmasterSequenceNumber(UInteger16 gsn);

	Parent &operator=(const Parent & other_t);

        friend ostream& operator<<(ostream& s, const Parent& it);


private:
        UInteger8 parentCommunicationTechnology;
        Octet   parentUuid[PTP_UUID_LENGTH];
        UInteger16 parentPortId;
        UInteger16 parentLastSyncSequenceNumber;
        Boolean parentFollowupCapable;
        Boolean parentExternalTiming;
        Integer16 parentVariance;
        Boolean parentStats;
        Integer16 observedVariance;
        Integer32 observedDrift;
        Boolean utcReasonable;
        UInteger8 grandmasterCommunicationTechnology;
        Octet   grandmasterUuidField[PTP_UUID_LENGTH];
        UInteger16 grandmasterPortIdField;
        UInteger8 grandmasterStratum;
        Octet   grandmasterIdentifier[PTP_CODE_STRING_LENGTH];
        Integer16 grandmasterVariance;
        Boolean grandmasterPreferred;
        Boolean grandmasterIsBoundaryClock;
	UInteger16 grandmasterSequenceNumber;
};

ostream& operator<<(ostream& s, const Parent& it);

#endif
