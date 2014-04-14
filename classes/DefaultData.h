#ifndef DEFAULTDATA_H
#define DEFAULTDATA_H
#include "constants.h"
#include "datatypes_dep.h"
#include <iostream>

using namespace std;

class DefaultData{

public:

	/*************Constructor************/
	DefaultData();

	/****************accessors***********/
	UInteger8 get_clockCommunicationTechnology() const;
	Octet get_clockUuidField() const;
	Octet get_clockUuidField(int position) const;
	UInteger16 get_clockPortField() const;
	UInteger8 get_clockStratum() const;
	Octet get_clockIdentifier() const;
	Octet get_clockIdentifier(int postition) const;
	Integer16 get_clockVariance() const;
	Boolean get_clockFollowupCapable() const;
	Boolean get_preferred() const;
	Boolean get_initializable() const;
	Boolean get_externalTiming() const;
	Boolean get_isBoundaryClock() const;
	Integer8 get_syncInterval() const;
	Octet get_subdomainName() const;
	Octet get_subdomainName(int x) const;
	UInteger16 get_numberPorts() const;
	UInteger16 get_numberForeignRecords() const;

	/****************mutators***********/
	void set_clockCommunicationTechnology(UInteger8 cct);
	void set_clockUuidField(const void *cuf, int length);
	void set_clockPortField(UInteger16 cpf);
	void set_clockStratum(UInteger8 cs);
	void set_clockIdentifier(const void *ci, int length);
	void set_clockVariance(Integer16 cv);
	void set_clockFollowupCapable(Boolean cfc);
	void set_preferred(Boolean p);
	void set_initializable(Boolean i);
	void set_externalTiming(Boolean et);
	void set_isBoundaryClock(Boolean ibc);
	void set_syncInterval(Integer8 si);
	void set_subdomainName(const void *sn, int length);
	void set_numberPorts(UInteger16 np);
	void set_numberForeignRecords(UInteger16 nfr);

	DefaultData &operator=(const DefaultData & other_t);

        friend ostream& operator<<(ostream& s, const DefaultData& it);


private:
	UInteger8 clockCommunicationTechnology;
	Octet	clockUuidField[PTP_UUID_LENGTH];
	UInteger16 clockPortField;
	UInteger8 clockStratum;
	Octet	clockIdentifier[PTP_CODE_STRING_LENGTH];
	Integer16 clockVariance;
	Boolean	clockFollowupCapable;
	Boolean	preferred;
	Boolean	initializable;
	Boolean	externalTiming;
	Boolean	isBoundaryClock;
	Integer8 syncInterval;
	Octet	subdomainName[PTP_SUBDOMAIN_NAME_LENGTH];
	UInteger16 numberPorts;
	UInteger16 numberForeignRecords;
};

ostream& operator<<(ostream& s, const DefaultData& it);

#endif
